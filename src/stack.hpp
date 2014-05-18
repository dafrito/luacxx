#ifndef LUA_CXX_INDEX_HEADER
#define LUA_CXX_INDEX_HEADER

#include "type.hpp"
#include "error.hpp"
#include "config.hpp"

#include <memory>
#include <type_traits>
#include <new>
#include <memory>
#include <string>
#include <stdexcept>

class QObject;

namespace lua {

typedef lua_State state;

// Simulates a direct link to a named Lua value
template <class Source, class Name>
class link
{
    lua::state* const _state;
    Source _source;
    Name _name;

public:
    link(const Source& source, const Name& name) :
        _state(source.state()),
        _source(source),
        _name(name)
    {
    }

    lua::type_info type() const;

    lua::state* const state() const
    {
        return _state;
    }

    const Source& source() const
    {
        return _source;
    }

    const Name& name() const
    {
        return _name;
    }

    template <class T>
    lua::link<lua::link<Source, Name>, T> operator[](T name) const
    {
        return lua::link<lua::link<Source, Name>, T>(*this, name);
    }

    template <class T>
    const link& operator=(T value) const;

    template <class T>
    void operator>>(T& destination);

    template <class T>
    T get() const;

    template <class T>
    operator T() const
    {
        return get<T>();
    }
};

template <class Source, class Name>
lua::link<Source, Name> make_link(const Source& source, const Name& name)
{
    return lua::link<Source, Name>(source, name);
}

// Represents an absolute index in the Lua stack.
class index
{
    lua::state* _state;
    int _pos;

public:
    index(lua::state* const state, const int pos) :
        _state(state),
        _pos(lua_absindex(state, pos))
    {
    }

    index(const lua::index& other) :
        _state(other._state),
        _pos(other._pos)
    {
    }

    lua::state* const state() const
    {
        return _state;
    }

    int pos() const
    {
        return _pos;
    }

    void set(const int pos)
    {
        _pos = pos;
    }

    void set(const index& other)
    {
        _pos = other.pos();
    }

    lua::type_info type() const
    {
        return lua::type_info(
            static_cast<lua::type>(lua_type(state(), pos()))
        );
    }

    explicit operator bool() const
    {
        return _pos >= 1 && _pos <= lua_gettop(_state);
    }

    template <class T>
    const index& operator=(const T& source) const;

    template <class T>
    lua::link<lua::index, T> operator[](T name) const
    {
        return lua::link<lua::index, T>(*this, name);
    }

    template <class T>
    T get() const;

    // Postfix (e.g. i++)
    lua::index operator++(int)
    {
        lua::index rv(*this);
        ++(*this);
        return rv;
    }

    // Prefix (e.g. ++i)
    lua::index& operator++()
    {
        ++_pos;
        return *this;
    }

    // Postfix (e.g. i--)
    lua::index operator--(int)
    {
        lua::index rv(*this);
        --(*this);
        return rv;
    }

    // Prefix (e.g. --i)
    lua::index& operator--()
    {
        --_pos;
        return *this;
    }
};

//
// Pushing values and userdata
//

// Discriminant for how userdata is stored
enum class userdata_storage {
    value,
    pointer,
    shared_ptr
};

// Metadata that defines the Lua userdata
struct userdata_block {
    userdata_storage storage;

public:
    userdata_block(const lua::userdata_storage& storage) :
        storage(storage)
    {
    }
};

template <class T>
struct Metatable
{
    // The name for this type
    static constexpr const char* name = "";

    // Initialize the provided metatable for this type.
    //
    // Return true if the metatable can be cached for future values (requires
    // the name to be specified).
    static bool metatable(const lua::index& table, T* value)
    {
        #ifdef HAVE_QT_CORE
        // If it's a QObject, then use that metatable
        return Metatable<typename std::conditional<
            std::is_base_of<QObject, T>::value,
            QObject,
            void
        >::type>::metatable(table, value);
        #else
        return false;
        #endif
    }
};

template <>
struct Metatable<void>
{
    static constexpr const char* name = "";

    static bool metatable(const lua::index& table, void* const value)
    {
        return false;
    }
};

// Destroy the userdata's value, specified by the template parameter
template <class Stored>
int destroy(lua::state* const state)
{
    char* block = static_cast<char*>(lua_touserdata(state, 1));
    auto value = reinterpret_cast<Stored*>(block + sizeof(lua::userdata_block));
    if (value != nullptr) {
        value->~Stored();
    }
    return 0;
}

int __gc(lua::state* const state);

template <class T, class Stored = T>
void push_metatable(lua::state* const state, T* const value)
{
    // Check for a cached metatable first.
    auto class_name = Metatable<T>::name;
    if (std::char_traits<char>::length(class_name) > 0) {
        // Push whatever we find.
        lua_getfield(state, LUA_REGISTRYINDEX, class_name);
    } else {
        // It doesn't even have a name, so just use nil to fall through gracefully.
        lua_pushnil(state);
    }
    lua::index mt(state, -1);
    if (mt.type() != lua::type::nil) {
        // Use the cached value
        return;
    }

    // Otherwise, clean up and create a new metatable.
    lua_pop(state, 1);
    lua_newtable(state);

    // Setup how we destroy the object.
    lua_pushstring(state, "__gc");
    lua_pushcclosure(state, __gc, 0);
    lua_settable(state, mt.pos());

    lua_pushstring(state, "Destroy");
    lua_pushcfunction(state, destroy<Stored>);
    lua_settable(state, mt.pos());

    // Use this metatable as the default index and newindex.
    auto set_metatable_as_default_table_for = [&](const char* name) {
        lua_pushstring(state, name);
        lua_pushvalue(state, mt.pos());
        lua_settable(state, mt.pos());
    };
    set_metatable_as_default_table_for("__index");
    set_metatable_as_default_table_for("__newindex");

    // Let downstream set up their type-specific metatable.
    auto cacheable = Metatable<T>::metatable(mt, value);

    // Check if it's cacheable (and actually has a name):
    if (cacheable && std::char_traits<char>::length(class_name) > 0) {
        // Cache it for the future
        lua_pushvalue(state, mt.pos());
        lua_setfield(state, LUA_REGISTRYINDEX, class_name);
    }
}

template <class Stored>
char* construct_userdata(lua::state* const state, lua::userdata_storage storage)
{
    // Get and push a chunk of memory from Lua to hold our metadata, as well as
    // the underlying value.
    char* block = static_cast<char*>(lua_newuserdata(state,
        sizeof(lua::userdata_block) + sizeof(Stored)
    ));

    // Create the metadata
    new (block) lua::userdata_block(storage);

    // Return a pointer to the data block
    return block + sizeof(lua::userdata_block);
}

template <class Value, lua::userdata_storage storage = lua::userdata_storage::value>
struct Construct
{
    static void construct(lua::state* const state, const Value& original)
    {
        // Create a Lua userdata block
        auto block = construct_userdata<Value>(state, storage);

        // Create a value in-place
        auto value = new (block) Value(original);

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value, Value>(state, value);
        lua_setmetatable(state, -2);
    }
};

template <class Value>
struct Construct<Value, lua::userdata_storage::pointer>
{
    static void construct(lua::state* const state, Value* original)
    {
        // Create a Lua userdata block
        auto block = construct_userdata<Value*>(state, lua::userdata_storage::pointer);

        // Create a value in-place
        auto value = new (block) Value*(original);

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value, Value*>(state, *value);
        lua_setmetatable(state, -2);
    }
};

template <class Value>
struct Construct<Value, lua::userdata_storage::shared_ptr>
{
    static void construct(lua::state* const state, const std::shared_ptr<Value>& original)
    {
        // Create a Lua userdata block
        auto block = construct_userdata<std::shared_ptr<Value>>(state, lua::userdata_storage::shared_ptr);

        // Create a value in-place
        auto value = new (block) std::shared_ptr<Value>(original);

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value, std::shared_ptr<Value>>(state, value->get());
        lua_setmetatable(state, -2);
    }
};

/**
 * Pushes the specified C++ value onto the Lua stack.
 *
 * Specialize this template in order to have your types supported by Luacxx's
 * algorithms.
 */
template <class T>
struct Push
{
    static void push(lua::state* const state, T value)
    {
        // By default, "push" means "construct a userdata by value"
        Construct<T>::construct(state, value);
    }
};

template <class T>
struct Push<T*>
{
    static void push(lua::state* const state, T* value)
    {
        // Pointers are pushed by value, with their underlying type used as
        // the object exposed to Lua.
        Construct<T, lua::userdata_storage::pointer>::construct(state, value);
    }
};

template <class T>
struct Push<std::shared_ptr<T>>
{
    static void push(lua::state* const state, const std::shared_ptr<T>& value)
    {
        // Shared pointers are pushed by value, but their metatable is treated
        // the same as pointers.
        Construct<T, lua::userdata_storage::shared_ptr>::construct(state, value);
    }
};

template <class T>
lua::index push(lua::state* const state, T value)
{
    // Forward to the struct
    lua::Push<T>::push(state, value);
    return lua::index(state, -1);
}

// Allows noop invocations from variadic templates
lua::index push(lua::state* const state);

template <class T, class... Rest>
lua::index push(lua::state* const state, T value, Rest... values)
{
    // Forward everything to the struct
    lua::Push<T>::push(state, value);
    return push(state, values...);
}

template <class Value>
lua::index push(Value value)
{
    // Assume the value is some sort of Lua object.
    return lua::push(value.state(), value);
}

template <class Source, class Name>
template <class T>
const lua::link<Source, Name>& lua::link<Source, Name>::operator=(T value) const
{
    lua::push(state(), _source);
    lua::push(state(), _name);
    lua::push(state(), value);
    lua_settable(state(), -3);
    lua_pop(state(), 1);

    return *this;
}

template <class Source, class Name>
lua::type_info lua::link<Source, Name>::type() const
{
    auto rv = lua::push(state(), *this).type();
    lua_pop(state(), 1);
    return rv;
}

template <class T>
const lua::index& lua::index::operator=(const T& source) const
{
    lua::push(state(), source);
    lua_replace(state(), pos());
    return *this;
}

//
// Storing and retrieving values and userdata
//

template <lua::userdata_storage storage, class T,
    typename std::enable_if<storage == lua::userdata_storage::value, int>::type = 0>
static void inner_store_userdata(T& destination, lua::userdata_block* userdata, void* data)
{
    // Carefully retrieve the value from the userdata.
    switch (userdata->storage) {
    case lua::userdata_storage::value:
        destination = *static_cast<T*>(data);
        break;
    case lua::userdata_storage::pointer:
        destination = **static_cast<T**>(data);
        break;
    case lua::userdata_storage::shared_ptr:
        destination = **static_cast<std::shared_ptr<T>*>(data);
        break;
    }
}

template <lua::userdata_storage storage, class T,
    typename std::enable_if<storage == lua::userdata_storage::pointer, int>::type = 0>
static void inner_store_userdata(T*& destination, lua::userdata_block* userdata, void* data)
{
    // Get a pointer to the userdata's value.
    switch (userdata->storage) {
    case lua::userdata_storage::value:
        destination = static_cast<T*>(data);
        break;
    case lua::userdata_storage::pointer:
        destination = *static_cast<T**>(data);
        break;
    case lua::userdata_storage::shared_ptr:
        destination = static_cast<std::shared_ptr<T>*>(data)->get();
        break;
    }
}

template <lua::userdata_storage storage, class T,
    typename std::enable_if<storage == lua::userdata_storage::shared_ptr, int>::type = 0>
static void inner_store_userdata(T& destination, lua::userdata_block* userdata, void* data)
{
    // Assign to the shared pointer; fail otherwise.
    switch (userdata->storage) {
    case lua::userdata_storage::shared_ptr:
    {
        destination = *reinterpret_cast<T*>(data);
        break;
    }
    case lua::userdata_storage::pointer:
    case lua::userdata_storage::value:
        throw lua::error("The provided Lua userdata does not hold a shared_ptr");
    }
}

template <lua::userdata_storage storage, class T>
static void store_userdata(T& destination, const lua::index& source)
{
    // Get a userdata value and set up the parameters for the inner procedure.
    auto block = static_cast<char*>(lua_touserdata(source.state(), source.pos()));
    inner_store_userdata<storage>(
        destination,
        reinterpret_cast<lua::userdata_block*>(block),
        block + sizeof(lua::userdata_block)
    );
}

template <typename T>
struct Store
{
    static void store(T& destination, const lua::index& source)
    {
        // Retrieve the userdata as a value
        store_userdata<lua::userdata_storage::value>(destination, source);
    }
};

template <typename T>
struct Store<T*>
{
    static void store(T*& destination, const lua::index& source)
    {
        // Retrieve the userdata as a pointer
        store_userdata<lua::userdata_storage::pointer>(destination, source);
    }
};

template <typename T>
struct Store<std::shared_ptr<T>>
{
    static void store(std::shared_ptr<T>& destination, const lua::index& source)
    {
        // Retrieve the useredata as a shared pointer
        store_userdata<lua::userdata_storage::shared_ptr>(destination, source);
    }
};

template <class T>
void store(T& destination, const lua::index& source)
{
    // Forward to the struct (for convenience)
    lua::Store<T>::store(destination, source);
}

template <class Source, class Name>
template <class T>
void lua::link<Source, Name>::operator>>(T& destination)
{
    lua::store(destination, *this);
}

template <class T>
lua::index& operator>>(lua::index& source, T& destination)
{
    lua::store(destination, source);
    return ++source;
}

template <class T>
lua::index operator>>(const lua::index& source, T& destination)
{
    lua::store(destination, source);
    return ++lua::index(source);
}

template <typename T>
struct Get
{
    static T get(const lua::index& source)
    {
        T destination = T();
        lua::store(destination, source);
        return destination;
    }
};

template <typename T>
struct Get<const T&>
{
    static T& get(const lua::index& source)
    {
        return lua::Get<T&>::get(source);
    }
};

template <typename T>
struct Get<T&>
{
    static T& get(const lua::index& source)
    {
        T* destination = nullptr;
        lua::store(destination, source);
        return *destination;
    }
};

template <class T, class Source>
T get(Source source)
{
    T rv = lua::Get<T>::get(lua::push(source));
    lua_pop(source.state(), 1);
    return rv;
}

template <class T>
auto get(const lua::index& source) -> decltype(lua::Get<T>::get(source))
{
    return lua::Get<T>::get(source);
}

template <>
void get<void>(const lua::index& source);

template <class T>
T get(lua::state* const state, const int pos)
{
    return lua::get<T>(lua::index(state, pos));
}

template <class Source, class Name>
template <class T>
T lua::link<Source, Name>::get() const
{
    return lua::get<T>(*this);
};

template <class T>
T lua::index::get() const
{
    return lua::get<T>(*this);
};

} // namespace lua

#endif // LUA_CXX_INDEX_HEADER

#ifndef luacxx_stack_INCLUDED
#define luacxx_stack_INCLUDED

#include "type.hpp"
#include "error.hpp"
#include "log.hpp"

#include <memory>
#include <type_traits>
#include <new>
#include <memory>
#include <string>
#include <stdexcept>
#include <sstream>

#include <forward_list>
#include <utility>
#include <cassert>

// Core stack and userdata primitives.
// Extended documentation lives in docs/reference/stack-and-userdata.md and
// docs/guide/useful-lua-functions.md.

namespace lua {

void allow_debugging(bool allowed = true);
bool is_debugging_allowed();

bool is_debugging(lua_State* const state);
std::string traceback(lua_State* const state, const int toplevel);

} // namespace lua

// See docs/guide/useful-lua-functions.md for notes on the Lua C API functions
// that pair most often with these declarations.

namespace lua {

std::string dump(lua_State* const state);

} // namespace lua

// Additional notes on stack-indexing helpers and stack rearrangement primitives
// such as `lua_absindex`, `lua_gettop`, `lua_settop`, `lua_replace`,
// `lua_remove`, `lua_insert`, and `lua_pop` live in
// docs/guide/useful-lua-functions.md.
//
// The longer discussion of how Luacxx maps C++ object lifetimes onto Lua
// userdata storage now lives in docs/guide/understanding-userdata-memory.md.

namespace lua {

class userdata_block;

// `userdata_type` and `userdata_block` are the core of Luacxx's userdata type
// safety. They record runtime type information, valid casts, payload location,
// and destruction behavior so `lua::get<T*>()` can verify and adjust userdata
// pointers safely. See docs/guide/understanding-type-safety.md for the full
// explanation.
class userdata_type {
    std::string _name;
    std::forward_list<std::pair<const lua::userdata_type*, unsigned short>> _casts;

public:
    userdata_type() :
        _name()
    {
    }

    userdata_type(const char* name) :
        _name(name)
    {
    }

    ~userdata_type();

    bool has_name() const
    {
        return !_name.empty();
    }

    const std::string& name() const
    {
        return _name;
    }

    void set_name(const char* name)
    {
        _name = name;
    }

    void set_name(const std::string& name)
    {
        _name = name;
    }

    template <class Base, class Derived = Base>
    void add_cast();

    void add_cast(const lua::userdata_type* info, ptrdiff_t offset);

    template <class Expected>
    bool has_cast() const;

    bool has_cast(const lua::userdata_type* const info) const;

    template <class Type>
    ptrdiff_t pointer_offset() const;

    ptrdiff_t pointer_offset(const lua::userdata_type* const info) const;

    bool has_casts() const
    {
        return !_casts.empty();
    }

    bool operator==(const userdata_type& other) const
    {
        return this == &other;
    }

    bool operator!=(const userdata_type& other) const
    {
        return !(*this == other);
    }

private:
    template <class Value>
    Value* cast(lua_State* const state, const lua::userdata_block* const block) const;

    void* cast(lua_State* const state, const lua::userdata_block* const block, const lua::userdata_type* const requested) const;

    friend class userdata_block;
};

// Metadata stored alongside each Luacxx userdata instance.
class userdata_block {
    const userdata_type* _info;
    void* _value;
    std::function<void(lua::userdata_block*)> _destructor;

public:
    userdata_block(void* value) :
        _info(nullptr),
        _value(value),
        _destructor()
    {
    }

    userdata_block() :
        userdata_block(nullptr)
    {
    }

    void set_destructor(const std::function<void(lua::userdata_block*)>& destructor)
    {
        _destructor = destructor;
    }

    void set_type(const userdata_type& info)
    {
        _info = &info;
    }

    const userdata_type* type() const
    {
        return _info;
    }

    void* value() const
    {
        return _value;
    }

    bool has_value() const
    {
        return _value != nullptr;
    }

    void set_value(void* value)
    {
        _value = value;
    }

    template <class T>
    T* cast(lua_State* const state) const
    {
        return type()->cast<T>(state, this);
    }

    ~userdata_block()
    {
        if (_destructor) {
            _destructor(this);
            _destructor = nullptr;
        }
        // Clear these in case this destructor gets called again.
        _value = nullptr;
    }
};

} // namespace lua

// Returns the payload size for a Luacxx userdata, excluding the metadata block.

namespace lua {

size_t object_size(lua_State* const state, const int pos);

lua::userdata_block* get_userdata_block(lua_State* const state, const int pos);

} // namespace lua

// Metatable customization and userdata lifecycle notes are documented in
// docs/reference/stack-and-userdata.md.

namespace lua {

// Backward-compatible alias for the older policy macro name.
#if defined(LUACXX_AUTO_METATABLE) && !defined(LUACXX_ALLOW_MISSING_METATABLES)
#define LUACXX_ALLOW_MISSING_METATABLES
#endif

// By default, Luacxx does not provide a fallback `Metatable<T>` for arbitrary
// types. That strict behavior helps catch missing metatable headers at compile
// time instead of silently producing generic opaque userdata. Defining
// `LUACXX_ALLOW_MISSING_METATABLES` enables the fallback specialization below.
// See docs/guide/luacxx-allow-missing-metatables.md for the tradeoffs.
#ifndef LUACXX_ALLOW_MISSING_METATABLES
template <class T>
struct Metatable
{
    static_assert(sizeof(T) != sizeof(T),
        "No lua::Metatable<T> is defined for this type. "
        "Include the header that defines the metatable, use a LUACXX metatable macro, "
        "or write a lua::Metatable<T> specialization. "
        "If you intentionally want generic fallback userdata, define "
        "LUACXX_ALLOW_MISSING_METATABLES."
    );
};
#else

template <class T>
struct Metatable
{
    // Type information
    static const userdata_type& info()
    {
        static userdata_type _info("anonymous userdata");
        if (!_info.has_casts()) {
            _info.add_cast<T>();
        }
        return _info;
    }

    // Initialize the provided metatable for this type.
    //
    // Return true if the metatable can be cached for future values (requires
    // the name to be specified).
    static bool metatable(lua_State* const, const int, const T*)
    {
        return true;
    }
};
#endif

template <>
struct Metatable<void>
{
    static const userdata_type& info()
    {
        static userdata_type _info("void");
        if (!_info.has_casts()) {
            _info.add_cast<void>();
        }
        return _info;
    }

    static bool metatable(lua_State* const, const int, const void* const)
    {
        return true;
    }
};

void lua_error_metatable(lua_State* const state, const int pos);

template <>
struct Metatable<lua::error>
{
    static const userdata_type& info()
    {
        static userdata_type _info("lua::error");
        if (!_info.has_casts()) {
            _info.add_cast<lua::error>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int source, const lua::error* const)
    {
        lua_error_metatable(state, source);
        return true;
    }
};

template <class T>
struct Metatable<const T>
{
    static const userdata_type& info()
    {
        return Metatable<T>::info();
    }

    static bool metatable(lua_State* const state, const int source, const T* const value)
    {
        return Metatable<T>::metatable(state, source, value);
    }
};

template <class T>
struct Metatable<T*>
{
    static const userdata_type& info()
    {
        return Metatable<T>::info();
    }

    static bool metatable(lua_State* const state, const int source, const T** const value)
    {
        return Metatable<T>::metatable(state, source, *value);
    }
};

template <class T>
struct Metatable<const T&>
{
    static const userdata_type& info()
    {
        return Metatable<T>::info();
    }

    static bool metatable(lua_State* const state, const int source, const T** const value)
    {
        return Metatable<T>::metatable(state, source, *value);
    }
};

template <class T>
struct Metatable<T&>
{
    static const userdata_type& info()
    {
        return Metatable<T>::info();
    }

    static bool metatable(lua_State* const state, const int source, const T** const value)
    {
        return Metatable<T>::metatable(state, source, *value);
    }
};

} // namespace lua

// These macros are the canonical shortcuts for defining `lua::Metatable<T>`
// specializations for common cases. See docs/guide/metatable-macros.md for
// usage guidance and examples.

#define LUA_METATABLE_NAMED(name) \
template<> \
struct lua::Metatable<name> \
{ \
    static const lua::userdata_type& info() \
    { \
        static lua::userdata_type _info(#name); \
        if (!_info.has_casts()) { \
            _info.add_cast<name>(); \
        } \
        return _info; \
    } \
\
    static bool metatable(lua_State* const, const int, const void*) \
    { \
        return true; \
    } \
};

#define LUA_METATABLE_BUILT(name) \
namespace lua { \
\
void name ## _metatable(lua_State* const state, const int mt); \
\
template<> \
struct Metatable<name> \
{ \
    static const userdata_type& info() \
    { \
        static userdata_type _info(#name); \
        if (!_info.has_casts()) { \
            _info.add_cast<name>(); \
        } \
        return _info; \
    } \
\
    static bool metatable(lua_State* const state, const int mt, const void*) \
    { \
        name ## _metatable(state, mt); \
        return true; \
    } \
}; \
\
};

#define LUA_METATABLE_BUILT_WITH(name, builder) \
namespace lua { \
\
template<> \
struct Metatable<name> \
{ \
    static const userdata_type& info() \
    { \
        static userdata_type _info(#name); \
        if (!_info.has_casts()) { \
            _info.add_cast<name>(); \
        } \
        return _info; \
    } \
\
    static bool metatable(lua_State* const state, const int mt, const void*) \
    { \
        builder (state, mt); \
        return true; \
    } \
}; \
\
};

#define LUA_METATABLE_INHERIT(name, parent) \
namespace lua { \
\
void name ## _metatable(lua_State* const state, const int mt); \
\
template<> \
struct Metatable<name> \
{ \
    static const userdata_type& info() \
    { \
        static userdata_type _info(#name); \
        if (!_info.has_casts()) { \
            _info.add_cast<name>(); \
            _info.add_cast<parent, name>(); \
        } \
        return _info; \
    } \
\
    static bool metatable(lua_State* const state, const int mt, const void*) \
    { \
        name ## _metatable(state, mt); \
        return true; \
    } \
}; \
\
};

LUA_METATABLE_NAMED(lua_State)

// Create metatables for logging functions
LUA_METATABLE_BUILT_WITH(lua::LogMessage, lua::LogMessage_metatable);

namespace lua {

// Some builtin metamethods, used by all Luacxx metatables

int __tostring(lua_State* const state);

template <class T>
void push_metatable(lua_State* const state, T* const value)
{
    // Check for a cached metatable first.
    auto& info = Metatable<T>::info();
    lua_pushstring(state, info.name().c_str());
    lua_gettable(state, LUA_REGISTRYINDEX);

    if (lua_type(state, -1) != LUA_TNIL) {
        // Use the cached value
        if (is_debugging(state)) {
            lua::logcm(state, "Userdata metatable creations",
                "Using cached metatable for ", info.name(), "."
            );
        }
        return;
    }

    if (is_debugging(state)) {
        lua::logEntercm(state, "Userdata metatable creations",
            "Creating new metatable for ", info.name()
        );
    }

    // Otherwise, clean up and create a new metatable.
    lua_pop(state, 1);
    lua_newtable(state);
    auto mt = lua_absindex(state, -1);

    // Setup __gc for this instantiated type.
    lua_pushstring(state, "__gc");
    lua_pushcfunction(state, [](lua_State* const state) {
        auto userdata_block = lua::get_userdata_block(state, 1);
        if (!userdata_block->has_value()) {
            return 0;
        }

        // Finally, destroy the userdata header itself
        userdata_block->~userdata_block();

        return 0;
    });
    lua_settable(state, -3);

    // Use this metatable as the default index and newindex.
    auto set_metatable_as_default_table_for = [&](const char* name) {
        lua_pushstring(state, name);
        lua_pushvalue(state, mt);
        lua_settable(state, mt);
    };
    set_metatable_as_default_table_for("__index");
    set_metatable_as_default_table_for("__newindex");

    // Let the programmer set up their type-specific metatable.
    auto cacheable = Metatable<T>::metatable(state, mt, value);

    lua_pushstring(state, "__tostring");
    lua_rawget(state, mt);
    if (lua_type(state, -1) == LUA_TNIL) {
        lua_pop(state, 1);
        lua_pushstring(state, "__tostring");
        lua_pushcfunction(state, __tostring);
        lua_rawset(state, mt);
    } else {
        lua_pop(state, 1);
    }

    // Check if the metatable is cacheable and that the class actually has a name.
    if (cacheable) {
        // Cache it for the future
        if (is_debugging(state)) {
            lua::logm(state, "Caching metatable for ", info.name(), ".");
        }
        lua_pushstring(state, info.name().c_str());
        lua_pushvalue(state, mt);
        lua_settable(state, LUA_REGISTRYINDEX);
    }

    if (is_debugging(state)) {
        lua::logLeave(state);
    }
}

template <class Base, class Actual>
void userdata_type::add_cast()
{
    const lua::userdata_type* info;
    if (std::is_same<Base, Actual>::value) {
        info = this;
    } else {
        info = &lua::Metatable<Base>::info();
    }

    constexpr ptrdiff_t NON_NULL = 0xffff;

    // Get the offset from the actual class to the base class. For most
    // parents, this will have no effect. However, for objects with multiple
    // parents, the non-first parents will result in a positive offset when the
    // casts are applied.
    auto offset = reinterpret_cast<ptrdiff_t>(
        static_cast<Base*>(
            reinterpret_cast<Actual*>(NON_NULL)
        )
    );

    // A non-null value needs to be used for the cast to operate, but it will
    // need to be removed before use.
    offset -= static_cast<ptrdiff_t>(NON_NULL);

    return add_cast(info, offset);
}

template <class Value>
Value* userdata_type::cast(lua_State* const state, const lua::userdata_block* const block) const
{
    return static_cast<Value*>(cast(state, block, &lua::Metatable<Value>::info()));
}

template <class Type>
ptrdiff_t userdata_type::pointer_offset() const
{
    return pointer_offset(&lua::Metatable<Type>::info());
}

template <class Expected>
bool userdata_type::has_cast() const
{
    return has_cast(&lua::Metatable<Expected>::info());
}

// Allocate userdata storage with Luacxx metadata appended after the payload.

lua::userdata_block* malloc(lua_State* const state, size_t size=0);

template <class Value>
struct Construct
{
    template <class... Rest>
    static void construct(lua_State* const state, Rest&&... args)
    {
        if (is_debugging(state)) {
            lua::logEntercm(state, "Userdata construction", "Constructing ", lua::Metatable<Value>::info().name());
        }

        // Create a Lua userdata block
        auto block = lua::malloc(state, sizeof(Value));
        block->set_type(lua::Metatable<Value>::info());

        // Create a value in-place
        auto value = new (block->value()) Value(args...);
        block->set_destructor([=](lua::userdata_block* userdata_block) {
            auto value = userdata_block->cast<Value>(state);
            if (value) {
                value->~Value();
            }
        });

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value>(state, value);
        lua_setmetatable(state, -2);

        if (is_debugging(state)) {
            lua::logLeave(state);
        }
    }
};

template <class Value>
struct Construct<Value*>
{
    template <class... Rest>
    static void construct(lua_State* const state, Value* const value)
    {
        if (is_debugging(state)) {
            lua::logEntercm(state, "Userdata construction", "Constructing ", lua::Metatable<Value>::info().name());
        }

        // Create a Lua userdata block
        auto block = lua::malloc(state);
        block->set_type(lua::Metatable<Value>::info());
        block->set_value(value);

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value>(state, value);
        lua_setmetatable(state, -2);

        if (is_debugging(state)) {
            lua::logLeave(state);
        }
    }
};

template <class Value>
struct Construct<const Value*>
{
    template <class... Rest>
    static void construct(lua_State* const state, const Value* const value)
    {
        Construct<Value*>::construct(state, const_cast<Value* const>(value));
    }
};

template <class T>
struct Push
{
    static void push(lua_State* const state, T value)
    {
        // By default, "push" means "construct a userdata by value"
        Construct<T>::construct(state, value);
    }
};

template <class T>
struct Push<T*>
{
    static void push(lua_State* const state, T* value)
    {
        if (value == nullptr) {
            lua_pushnil(state);
            return;
        }
        // Pointers are pushed by value, with their underlying type used as
        // the object exposed to Lua.
        Construct<T*>::construct(state, value);
    }
};

//
// Storing and retrieving values and userdata
//

template <typename T>
struct Store
{
    static void store(T& destination, lua_State* const state, const int pos)
    {
        // Set to null explicitly, if source is nil
        if (lua_isnoneornil(state, pos)) {
            throw lua::error(state, std::string("lua::Store<") + lua::Metatable<T>::info().name() + ">::store: source must not be nil");
        }

        // Retrieve the userdata and populate the destination pointer with the cast value.
        auto block = lua::get_userdata_block(state, pos);
        destination = *block->cast<T>(state);
    }
};

template <typename T>
struct Store<T*>
{
    static void store(T*& destination, lua_State* const state, const int pos)
    {
        // Set to null explicitly, if source is nil
        if (lua_isnoneornil(state, pos)) {
            destination = nullptr;
            return;
        }

        // Retrieve the userdata and populate the destination pointer with the cast value.
        auto block = lua::get_userdata_block(state, pos);
        destination = block->cast<T>(state);
    }
};

template <>
struct Store<lua::userdata_block*>
{
    static void store(lua::userdata_block*& destination, lua_State* const state, const int source)
    {
        destination = lua::get_userdata_block(state, source);
    }
};

template <typename T>
struct Get
{
    static T get(lua_State* const state, const int source)
    {
        T destination = T();
        lua::Store<T>::store(destination, state, source);
        return destination;
    }
};

template <typename T>
struct Get<const T&>
{
    static T& get(lua_State* const state, const int source)
    {
        return lua::Get<T&>::get(state, source);
    }
};

template <typename T>
struct Get<T&>
{
    static T& get(lua_State* const state, const int source)
    {
        T* destination = nullptr;
        lua::Store<T*>::store(destination, state, source);
        return *destination;
    }
};

template <>
struct Get<void>
{
    static void get(lua_State* const, const int)
    {
    }
};

} // namespace lua

#endif // luacxx_stack_INCLUDED

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

/*

=head4 int lua_absindex(state, int index)

Returns the positive integer that represents the given index. Non-absolute
indices are given as negative numbers, with -1 representing the topmost value,
-2 representing the value underneath that, and so forth. Zero is never a valid
index.

Some indices are not absolute or relative. Such implements are called
pseudo-indices by Lua, but they behave like stack indices that are permanently
available. Use them in place of indices like they are enumeration constants.

=head4 LUA_REGISTRYINDEX

The pseudo-index that corresponds to the registry, a table reserved for use
solely by C. The registry is better explained along with lua::reference, so
I will omit further discussion here.

=head4 int lua_gettop(state)

Returns the number of values currently on the stack.

    // Assuming the state isn't empty
    assert(lua_absindex(state, -1) == lua_gettop(state));

=head4 void lua_settop(state, top)

Sets the index of the topmost value. This has the effect of quickly
clearing off unwanted values.

    // Blow away all stack values
    lua_settop(state, 0);

=head4 void lua_copy(state, int source, int dest)

Replace the stack value at dest with the stack value at source, without
affecting source.

    lua_pushstring(state, "A");
    lua_pushstring(state, "B");
    lua_pushstring(state, "C");
    // ["A", "B", "C"]

    // Copy "A" onto "C"
    lua_copy(state, 1, 3);

    // Stack is now ["A", "B", "C"]

=head4 void lua_replace(state, index)

Replaces the value at the given target index with the topmost value, removing the topmost value.

    lua_pushstring(state, "A");
    lua_pushstring(state, "B");
    lua_pushstring(state, "C");
    // ["A", "B", "C"]

    // Replace "A" with "C"
    lua_replace(state, 1);

    // Stack is now ["C", "B"]

=head4 void lua_remove(state, index)

Removes the value at the specified index, shifting all values above it downward.

    lua_pushstring(state, "A");
    lua_pushstring(state, "B");
    lua_pushstring(state, "C");
    // ["A", "B", "C"]

    // Remove "B"
    lua_replace(state, 2);

    // Stack is now ["A", "C"]

This function operates in linear time, which can be rather expensive when
handling a lot of arguments. Prefer the constant-time methods like
lua_settop(state, index), or merely incrementing an index, over this function.

If you want to return a single value from a stack of unknown size, the
following idiom works well to avoid lua_remove:

    // Add "No time" to the top of this state's stack
    lua_pushstring(state, "No time.");

    // Replace the first value with the topmost one, then clear all values above it.
    lua_replace(state, 1);
    lua_settop(state, 1);
    return 1;

=head4 void lua_insert(state, index)

Moves the topmost value to the specified index, shifting all values at and
above that index to make room.

    lua_pushstring(state, "A");
    lua_pushstring(state, "B");
    lua_pushstring(state, "C");
    // ["A", "B", "C"]

    // Move "C" to the bottom
    lua_insert(state, 1);

    // Stack is now ["C", "A", "B"]

=head4 void lua_pop(state, int n)

Removes n values from the top of the stack.

    // Remove one value
    lua_pop(state, 1);

=head2 MEMORY MODELS

C++'s memory model is largely dependent on reachability being determined at
compile-time. It turns out that this is sufficient for a large portion of
memory allocation needs, and C++'s designers were able to implement it
identically to how memory allocation works for its builtin types. This
affordance is not offered the C programmer, and it represents perhaps the
largest philosophical break between these two often interchangeable languages.

Lua's memory model is limited by its weak type information, which constrain it
to a more conservative strategy - garbage collection. This does have the
benefit of working even in the most pathological of cases, but at the cost of
worse performance relative to what a static compiler could do for common cases.

C++ objects are almost always created on the stack. This memory allocation
strategy allows for the possible lifetimes of the created object to be known
with certainty. As a result, its place in memory can vary without causing the
behavior of the program. The compiler can even omit allocating the full object
in memory altogether, as well as take advantage of the known locality of that
object by omitting synchronization.

However, it is common to not know the full lifetime of an object, as well as
preferring to work with memory without intervention from the compiler. In this
case, C provides malloc(), and C++ provides operator new.

Lua, being a weakly typed language, offers only its own form of malloc() called
lua_newuserdata(state, int size). The size is in bytes, so it's very easy to
create C++ objects on a Lua userdata:

    void* block = lua_newuserdata(state, sizeof(Point));
    new (block) Point();

By default, this object is opaque to Lua, but methods and access can be
provided through its metatable. At the very least, we can use a metatable
to call the object's destructor when that object is collected.

    // Assuming the userdata is at the top of the stack
    lua_getmetatable(state, -1);
    lua::index mt(state, -1);

    lua_pushcclosure(state, __gc, 0);
    lua_setfield(state, mt.pos(), "__gc");

    // __gc looks something like this. I use a template for clarity:

    template <class T>
    void call_destructor(T& value)
    {
        value.~T();
    }

    int __gc(lua_State* const state)
    {
        auto block = reinterpret_cast<Point*>(lua_touserdata(state, 1));
        call_destructor(*block);
    }


Lua-cxx uses this strategy as its default for values pushed on the stack. This
means that Lua can handle any C++ object out-of-the-box, without the need to
write any binding code.

    // Create a C++ Point on the Lua stack.

    Point p(2, 3);
    lua::push(state, p);

If the object has a non-zero-argument constructor, lua::make can be used to
pass the constructor arguments directly, as in the following example.

    // Create a C++ Point. This example behaves the same as the previous one.

    lua::make<Point>(state, 2, 3);

It's conventional to have the class be a table that uses itself as a metatable
for created objects. Userdata do not need to folow this convention, but I find
it nice to do so as it allows C++ objects to mesh well with Lua objects. Here's
how I'd do it:

    // Load with require "Point"
    int luaopen_Point(lua_State* const state)
    {
        lua::thread env(state);

        env["Point"] = lua::value::table;
        env["Point"]["new"] = Point_new;

        return 0;
    }

Point:new is the constructor, which we can write to accept either zero arguments
or an (x, y) pair. lua::make is used behind the scenes, as in the following
implementation:

    int Point_new(lua_State* const state)
    {
        // We could check for exactly 3, but I like to behave as Lua would.
        if (lua_gettop(state) > 1) {
            // Call Point::Point(x, y)
            lua::make<Point>(state,
                lua::get<int>(state, 2),
                lua::get<int>(state, 3)
            );
        } else {
            // Just call Point::Point()
            lua::make<Point>(state);
        }

        return 1;
    }

*/

namespace lua {

class userdata_block;

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

// Metadata that defines the Lua userdata
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

#ifndef LUACXX_AUTO_METATABLE
template <class T>
struct Metatable
{
    static_assert(sizeof(T) != sizeof(T), "Default metatables are not provided automatically."
        " Use -DLUACXX_AUTO_METATABLE to override."
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

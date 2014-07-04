#ifndef LUACXX_STACK_INCLUDED
#define LUACXX_STACK_INCLUDED

#include "type.hpp"
#include "error.hpp"
#include "config.hpp"

#include <memory>
#include <type_traits>
#include <new>
#include <memory>
#include <string>
#include <stdexcept>
#include <sstream>

/*

=head1 NAME

stack.hpp - core API

=head1 SYNOPSIS

    #include <luacxx/stack.hpp>

    struct Sum {
        int value;

        Sum(int value) :
            value(value)
        {
        }
    };

    // Create a new Sum for Lua
    int sum_new(lua_State* const state)
    {
        int initial = 0;
        if (lua_gettop(state) > 1) {
            initial = lua_tointeger(state, 2);
        } else if (lua_gettop(state) == 0) {
            throw lua::error("Sum metatable must be provided");
        }
        lua::make<Sum>(state, initial);

        // Use the Sum table as our metatable
        lua_pushvalue(state, 1);
        lua_setmetatable(state, -2);

        // Return the newly created Sum
        lua_replace(state, 1);
        lua_settop(state, 1);
        return 1;
    }

    // Add all numbers to the given sum
    int sum_add(lua_State* const state)
    {
        // lua::get<T> returns a T
        auto sum = lua::get<Sum*>(state, 1);

        // Add each value to the sum
        for (int i = 2; i <= lua_gettop(state); ++i) {
            sum->value += lua_tointeger(state, i);
        }

        return 0;
    }

    // Get the Sum's value
    int sum_get(lua_State* const state)
    {
        auto sum = lua::get<Sum*>(state, 1);
        lus_settop(state, 0);
        lua_pushinteger(state, sum->value);
        return 1;
    }

    // Export a module named "Sum" that Lua can require
    int luaopen_Sum(lua_State* const state)
    {
        lua::thread env(state);

        env["Sum"] = lua::value::table;

        // Attach methods
        env["Sum"]["New"] = sum_new;
        env["Sum"]["Get"] = sum_get;
        env["Sum"]["Add"] = sum_add;

        // Don't return anything
        return 0;
    }

    // Meanwhile, in Lua...

    require "Sum";

    local sum = Sum:New(2);
    sum:Add(3);
    assert(sum:Get() == 5);

=head1 DESCRIPTION

This document will detail both this headers's API as well as the relevant
Lua C API where necessary, as knowledge of both will better able you to
decide between their leaner, but less idiomatic, API or this library's
more powerful, but more complex, extensions.

=head1 Creating and initializing Lua environments

A Lua environment's state is accessed through a lua_State value, and all
Lua C API functions require you to give a valid pointer to one. However,
lua_State's member data is private: you must use the Lua C API to make
changes. Libraries like this one call into the Lua C API, merely
providing a diferent facade over this common subset of behavior.

*/

/*

The following methods deal with creating and initializing lua_State
objects:

=head4 lua_State* luaL_newstate();

Create a fresh new state.

This is the general-purpose function. Internally, it just calls lua_newstate
with a default allocator. It doesn't install the standard libraries, though -
you will need to use luaL_openlibs(state) for that.

=head4 lua_State* lua_newstate(lua_Alloc allocator, void* allocator_data);

Create a new lua_State* with a custom allocator (and associated pointer to
user-defined memory). The allocator is used for all runtime memory allocation.
The default allocator behaves like the following function:

    void* allocate(
        void* allocator_data,
        void* block,
        size_t orig_size,
        size_t size)
    {
        if (size == 0) {
            // Requested size is zero, so destroy
            free(block);
            return nullptr;
        }

        // Reallocate memory, or allocate anew if block == nullptr.
        return realloc(block, size);
    }

This function is called for all new allocations, all reallocations, and all
frees. An allocator is global across all threads for this state, so all Lua
threads share the same memory pool.

I feel compelled to warn you that creating a custom allocator is an advanced
topic, but the process is actually straight-forward.  The difficulty is finding
a need to do so.

=head4 lua_State* lua_newthread(lua_State*);

Creates and returns a new Lua thread that uses the same global environment as
the given thread. The thread is also pushed onto the stack, as it is owned by
the given state and therefore subject to garbage collection.

To appreciate the power and limitations of Lua threads, examine the coroutine
library, which offers ways to perform collaborative multithreading within Lua.
While the Lua facility is rather limited, it provides enough of a foundation
for real thread support written on the C side. As a result, it is worth
understanding if you're writing code that would benefit from multithreading.

=head4 void luaL_openlibs(lua_State*);

Load all standard libraries into the state's environment. The Lua 5.2 standard
library consists of the following modules:

=over 4

=item B<(base)> - globals like print, tonumber, setmetatable, error, assert, ...

=item B<package> - require, package.searchers, ...

=item B<coroutine> - coroutine.create, coroutine.yield, coroutine.resume, ...

=item B<string> - string.gsub, string.char, string.lower, ...

=item B<table> - table.insert, table.pack, table.unpack, ...

=item B<math> - math.sin, math.abs, math.floor, math.pi, ...

=item B<bit32> - bitwise operators like bit32.bor, bit32.lshift, ...

=item B<io> - io.open(filename), file:read, file:seek, ...

=item B<os> - os.date(strftime_pattern), os.execute(command), ...

=item B<debug> - debug.debug(), debug.traceback(), ...

=back

The package module can be used to require() the other libraries, except for
base, which is not accessible using require(). All of these modules correspond
to a luaopen_* function included with Lua (e.g. luaopen_io) which is
accessible as an exported C function.

=head4 void lua_close(state)

Gracefully terminate the Lua state, releasing all dynamic memory and calling
garbage collection metamethods. If this function is used on a Lua thread, that
thread's owning state (and all of its threads) will be destroyed. This
function does not appear to be safe to call from a C function called from Lua.

=head1 Accessing, modifying, and removing Lua stack values

Most of Lua's C API is concerned with pushing and retrieving values from the
Lua stack. The stack, which actually performs more like a vector, is the space
used by C to stage values for further manipulation by Lua. I must mention that
Lua itself uses the stack as well for common tasks, and only a much smaller
subset works with Lua's internal structures. As a result, this allows code
written in C to interact with Lua code as quickly as code written in Lua.

Due to C lacking function overloading, much of Lua's API is plainly inferior
to a version written specifically for C++ users. C++ templates can be used to
provide custom specializations for new types while retaining essentially all
of the performance of the C functions.

=head4 std::string lua::dump(state)

Returns a string that describes the current state of the stack. This can be
useful for debugging:

    #include <luacxx/algorithm.hpp>
    #include <iostream>

    // Print the stack to stderr
    std::cerr << lua::dump(state) << std::endl;

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

=head2 class lua::link<Source, Name>

Plumbing for representing symbolic paths to Lua values.

    // Get a symbolic link to package.searchers
    auto searchers = lua::make_link(lua::global(state, "package"), "searchers");
    assert(searchers.type().table());

lua::link is useful solely for its operator[] overloading, which allows
arbitrary nesting of Lua accesses to retrieve a value. Such nesting occurs
very naturally when calling Lua, so it's very convenient to have an object
that represents such addresses. You can use lua::make_link to quickly create a
link; this function allows the compiler to deduce template parameters.

lua::link's public API mimics that of lua::index, so refer to the
documentation for that class for more information.

*/

namespace lua {

template <class Source, class Name>
class link
{
    lua_State* const _state;
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

    lua_State* const state() const
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

}

/*

=head2 class lua::index

A reference to a stack position.

    #include <stack.hpp>

    // Concatenate all strings together
    int strict_concat(lua_State* const state)
    {
        std::stringstream full_string;
        lua::index value(state, 1);

        while (value) {
            if (value.type() != lua::type::string) {
                std::stringstream str;
                str << "Argument at index "<< value.pos();
                str << " must be a string, but a ";
                str << value.type().name() << " was given.";

                throw lua::error(str.str());
            }

            // Add this value to the working total
            full_string << lua_tostring(value.state(), value.pos());

            // Go to the next value
            ++value;
        }

        // Clear the stack and push the final string
        lua_settop(state, 0);
        lua_pushstring(state, full_string.str().c_str());
        return 1;
    }

lua::index is a simple class, designed to give a more object-oriented
approach to working with stack values. This is especially useful if
you're iterating over the stack or were given a stack value from an
external source.  The stack value's position is absolute, so external
changes will not cause the index's value to move. This inflexibilty
allows the index to optimize for speed.

=head4 lua_State* index.state(), int index.pos()

Return the underlying data for this index.

    lua_replace(index.state(), index.pos());

=head4 lua::type index.type();

Returns the type of the value at this index. Refer to lua::type for
more information.

    switch (index.type().get()) {
        case lua::type::nil:
            // Handle nil
            break;
        case lua::type::number:
        case lua::type::boolean:
        case lua::type::string:
            // Handle primitives
            break;
        case lua::type::function:
            // Handle functions
            break;
        default:
            // Handle tables, userdata, and special types
            break;
    }

=head4 operator bool(), operator++(), operator--(), ...

The index behaves as a smart pointer. operator bool() will return false
if the index is out of range of the underlying state. The index is always
positive, so increment and decrement work as expected.

    #include <luacxx/convert/numeric.hpp>

    int sum = 0;
    while (index) {
        sum += index.get<int>();
        ++index;
    }

=head4 operator=(const T& source);

Replace the value at this index's position with the given value, similar
to lua_replace.

    #include <luacxx/convert/numeric.hpp>

    lua_pushnil(state);
    lua::index index(state, -1);
    assert(0 == index.get<int>());

    // ... get other_index ...
    other_index = 42;
    index = other_index;
    assert(42 == index.get<int>());

=head4 operator[](T name);

    #include <luacxx/convert/numeric.hpp>

    auto id = index["id"];
    assert(2 == id.get<int>());

Creates a link using this index as a source, and the given value as the
name. This does not modify the stack.

=head4 T index.get<T>()

Returns the stack value as the specified type. This method uses
lua::get<T> internally, so refer to that method for more information.

*/

namespace lua {

class index
{
    lua_State* _state;
    int _pos;

public:
    index(lua_State* const state, const int pos) :
        _state(state),
        _pos(lua_absindex(state, pos))
    {
    }

    index(const lua::index& other) :
        _state(other._state),
        _pos(other._pos)
    {
    }

    lua_State* const state() const
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

/*

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

=head4 lua_pushlightuserdata(state, void* p), lua::push<void*>

Pushes a raw pointer onto the stack. The pointer has no metatable, so
it is only really useful to pass data between C functions, and to quickly
save C data as upvalues to a C function.

    #include <luacxx/convert/string.hpp>

    lua_pushvalue(state, LUA_REGISTRYINDEX);
    lua::push(state, lua::value::registry);

*/

// Discriminant for how userdata is stored
enum class userdata_storage {
    value,
    pointer,
    shared_ptr
};

// Metadata that defines the Lua userdata
class userdata_block {
    char _storage;

public:
    userdata_block(const lua::userdata_storage& storage) :
        _storage(static_cast<char>(storage))
    {
    }

    lua::userdata_storage storage()
    {
        return static_cast<lua::userdata_storage>(_storage);
    }
};

/*

=head3 METATABLES

Metatables enable operator overloading for Lua tables and userdata. Operator
overloading allows the programmer to redefine what an operator means for a
given object. In practice, it's rare to overload every operator on a given
object, but overloading a key few when appropriate can aid greatly in the
clarity of code.

To overload an operator, populate a table with the overloaded operations and
install it using setmetatable(object, metatable):

    local mt = {

        -- Equality
        __eq = function(a, b)
            return a.x == b.x and a.y == b.y;
        end,

        -- Unary minus
        __unm = function(self)
            a.x = -a.x;
            a.y = -a.y;
        end,

        -- Shows up on tostring(obj)
        __tostring = function(self)
            return "(" .. self.x .. ", " .. self.y .. ")";
        end
    };

    Point = {};
    function Point:New(x, y)
        local self = {x, y};
        setmetatable(self, mt);
    end;

It is allowed and reasonable to use a table as its own metatable, as well as to
have non-metatable functions intermixed with metatable functions:

    local obj = {
        __index = function(self, name)
            -- .. implement as needed ...
        end
    };
    setmetatable(obj, obj);

=over 4

=item Printable types

Objects that have a printable value should overload __tostring. Objects that
are purely opaque pointers should still overload __tostring, to provide some
indication of what that userdata contains:

    #include <sstream>

    std::string Point_tostring(Point* point)
    {
        std::stringstream str;
        str << "Point (" << point->x << ", " << point->y << ")";
        return str.str();
    }

=item Numeric types

Objects that represent a numeric type, or a vector of numeric types, can
overload the numeric operators where appropriate.

* __add(a, b) - a+b
* __sub(a, b) - a-b
* __mul(a, b) - a*b
* __div(a, b) - a/b
* __unm(a) - unary minus
* __mod - a % b
* __pow - a ^ b

=item Comparable types

Objects that have identity can implement the equality operations. Comparable
objects can also implement both the < and <= operators.

* __eq(a, b) a == b
* __lt(a, b) a < b
* __le(a, b) a <= b

There are no __gt or __ge overloads, nor is there a __cmp operator like Perl
would have.

=item Composite types

Lists, strings, and other countable data structures can implement contacenation
and length:

* __concat(self, append) self .. append
* __len(self) #a

=item Mapping types

Tables that provide a mapping, or support a fixed range of variations for
a given mapping, can use __index to provide that support.

    -- Make colors be case-insensitive!
    Colors = setmetatable({}, {
        __index = function(self, name)
            local canonical = tostring(name):lower();
            return rawget(self, canonical);
        end,

        __newindex = function(self, name, color)
            local canonical = tostring(name):lower();
            rawset(self, canonical, color);
        end
    });

    Colors.white = {1, 1, 1};
    Colors.black = {0, 0, 0};
    Colors.red   = {1, 0, 0};
    Colors.green = {0, 1, 0};
    Colors.blue  = {0, 0, 1};

    print(unpack(Colors.WHITE)) -- 1 1 1

=item Invokable types

Objects can behave as functions by overloading the __call operator. Much
of what can be done with __call can be done with closures, but it's possible
that __call may convey the meaning better for some esoteric use:

    function Adder(dx, dy)
        return setmetatable({}, {
            change_dx = function(self, value)
                dx = value;
            end,
            change_dy = function(self, value)
                dy = value;
            end,
            __call = function(self, point)
                point.x = point.x + dx;
                point.y = point.y + dy;
                return point;
            end
        });
    end;

    local adder = Adder(2, 3);

    print(adder(Point:New(1, 1)));
    -- 3 4

    adder:change_dx(10);
    adder:change_dy(10);
    print(adder(Point:New(1, 1)));
    -- 11 11

=item Userdata types

All C++ userdata, as well as C userdata that have non-trivial destruction,
should overload __gc to provide correct behavior when a Lua userdata has
become reclaimable.

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

A __gc method is guaranteed to be invoked for each object where it was set, but
an overload must be given before setmetatable is called:

    auto obj = lua::get<Point*>(state, -1);

    // Create the new table
    auto mt = lua::push(state, lua::value::table);

    // Set up the __gc method
    lua_pushcclosure(state, __gc, 0);
    lua_setfield(state, mt.pos(), "__gc");

    // And then set the metatable
    lua_setmetatable(state, -2);

A __gc method is guaranteed to be invoked once for each userdata that has one,
either when the object is reclaimed by garbage collection or when the Lua
environment is closed with lua_close. This is a weaker guarantee than what it
provided by C++ destructors.

=head2 lua::Metatable<T>

The default implementation of Lua-cxx pushes C++ objects by value. Its metatable
is manufactured initially by this fixed process, but the programmer can add
additional methods and overloads by providing a lua::Metatable<> specialization
for their type:

    namespace lua {

    template <>
    struct Metatable<Point>
    {
        // Set this object's name. Used by its value for caching.
        static constexpr const char* name = "Point";

        static bool metatable(const lua::index& mt, Point* value)
        {
            // Let Lua-cxx create these method bindings
            mt["x"] = &Point::x;
            mt["y"] = &Point::x;
            mt["set_x"] = &Point::set_x;
            mt["set_y"] = &Point::set_y;

            // Allow it to be cached. Return false if it shouldn't be cached.
            return true;
        }
    };

    } // namespace lua

If the Metatable<> specialization returns true, that metatable will be cached
and used for all subsequent objects with that metatable's name.

*/

template <class T>
struct Metatable
{
    // The name for this type
    static constexpr const char* name = "";

    // Initialize the provided metatable for this type.
    //
    // Return true if the metatable can be cached for future values (requires
    // the name to be specified).
    static bool metatable(const lua::index& mt, const T* value)
    {
        return true;
    }
};

template <>
struct Metatable<void>
{
    static constexpr const char* name = "void";

    static bool metatable(const lua::index& mt, const void* const value)
    {
        return true;
    }
};


template <class T>
inline void call_destructor(T& value)
{
    value.~T();
}

// Destroy the userdata's value, specified by the template parameter
template <class Stored>
int free_userdata(lua_State* const state)
{
    char* block = static_cast<char*>(lua_touserdata(state, 1));
    auto userdata_block = reinterpret_cast<lua::userdata_block*>(block + sizeof(Stored));

    switch (userdata_block->storage()) {
    case userdata_storage::pointer:
    {
        // Don't do anything for pointers; Lua does not own them, so Lua should not destroy them.
        break;
    }
    case userdata_storage::value:
    {
        auto value = reinterpret_cast<Stored*>(block);
        if (value != nullptr) {
            call_destructor(*value);
        }
        break;
    }
    case userdata_storage::shared_ptr:
        auto value = reinterpret_cast<std::shared_ptr<Stored>*>(block);
        if (value != nullptr) {
            call_destructor(*value);
        }
        break;
    }


    return 0;
}

int __gc(lua_State* const state);

template <class T, class Stored = T>
void push_metatable(lua_State* const state, T* const value)
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
    lua_pushcclosure(state, __gc, 0);
    lua_setfield(state, mt.pos(), "__gc");

    // Make the class name visible to callers
    lua_pushlightuserdata(state, const_cast<char*>(class_name));
    lua_setfield(state, mt.pos(), "__class");

    lua_pushstring(state, "free_userdata");
    lua_pushcfunction(state, free_userdata<Stored>);
    lua_settable(state, mt.pos());

    // Use this metatable as the default index and newindex.
    auto set_metatable_as_default_table_for = [&](const char* name) {
        lua_pushstring(state, name);
        lua_pushvalue(state, mt.pos());
        lua_settable(state, mt.pos());
    };
    set_metatable_as_default_table_for("__index");
    set_metatable_as_default_table_for("__newindex");

    // Let the programmer set up their type-specific metatable.
    auto cacheable = Metatable<T>::metatable(mt, value);

    // Check if it's cacheable (and actually has a name):
    if (cacheable && std::char_traits<char>::length(class_name) > 0) {
        // Cache it for the future
        lua_pushvalue(state, mt.pos());
        lua_setfield(state, LUA_REGISTRYINDEX, class_name);
    }
}

/*

=head2 char* lua::malloc(state, size_t size, (optional) lua::userdata_block)

Creates a new userdata of the given size. The userdata has a userdata_block
appended to the end of it, so lua_rawlen will not return the same size as
size was given.

*/

char* malloc(lua_State* const state, size_t size, const lua::userdata_block& userdata_block = lua::userdata_block(lua::userdata_storage::value));

template <class Stored>
char* construct_userdata(lua_State* const state, lua::userdata_storage storage)
{
    return lua::malloc(state,
        sizeof(Stored),
        lua::userdata_block(storage)
    );
}

template <class Value, lua::userdata_storage storage = lua::userdata_storage::value>
struct Construct
{
    template <class... Rest>
    static void construct(lua_State* const state, Rest&&... args)
    {
        // Create a Lua userdata block
        auto block = construct_userdata<Value>(state, storage);

        // Create a value in-place
        auto value = new (block) Value(args...);

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value, Value>(state, value);
        lua_setmetatable(state, -2);
    }
};

template <class Value>
struct Construct<Value, lua::userdata_storage::pointer>
{
    template <class... Rest>
    static void construct(lua_State* const state, Rest... args)
    {
        // Create a Lua userdata block
        auto block = construct_userdata<Value*>(state, lua::userdata_storage::pointer);

        // Create a value in-place
        auto value = new (block) Value*(args...);

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value, Value*>(state, *value);
        lua_setmetatable(state, -2);
    }
};

template <class Value>
struct Construct<Value, lua::userdata_storage::shared_ptr>
{
    template <class... Rest>
    static void construct(lua_State* const state, Rest... args)
    {
        // Create a Lua userdata block
        auto block = construct_userdata<std::shared_ptr<Value>>(state, lua::userdata_storage::shared_ptr);

        // Create a value in-place
        auto value = new (block) std::shared_ptr<Value>(args...);

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value, std::shared_ptr<Value>>(state, value->get());
        lua_setmetatable(state, -2);
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
        Construct<T, lua::userdata_storage::pointer>::construct(state, value);
    }
};

template <class T>
struct Push<std::shared_ptr<T>>
{
    static void push(lua_State* const state, const std::shared_ptr<T>& value)
    {
        if (!value) {
            lua_pushnil(state);
            return;
        }
        // Shared pointers are pushed by value, but their metatable is treated
        // the same as pointers.
        Construct<T, lua::userdata_storage::shared_ptr>::construct(state, value);
    }
};

/*

=head2 lua::index push(state, T value, Rest... values)

    #include <luacxx/convert/string.hpp>
    #include <luacxx/convert/numeric.hpp>

    auto table = lua::push(state, lua::value::table);
    table["Foo"] = 42;
    table["Bar"] = 24;
    assert(42 == table["Foo"].get<int>());

Pushes the specified values onto the stack, and returns an index referring to
the topmost value. Internally, lua::push just calls the Push struct, like so:

    lua::Push<T>::push(state, value);

Specialize the lua::Push struct if you wish for your type to be handled
specially. For instance, the struct for lua::index looks like this:

    template <>
    struct Push<lua::index>
    {
        static void push(lua_State* const state, const lua::index& source)
        {
            // Push a copy of the value stored at source.pos()
            lua_pushvalue(state, source.pos());
        }
    };

*/

template <class T>
lua::index push(lua_State* const state, T value)
{
    // Forward to the struct
    lua::Push<T>::push(state, value);
    return lua::index(state, -1);
}

// Allows noop invocations from variadic templates
lua::index push(lua_State* const state);

template <class T, class... Rest>
lua::index push(lua_State* const state, T value, Rest... values)
{
    // Forward everything to the struct
    lua::Push<T>::push(state, value);
    return push(state, values...);
}

/*

=head2 lua::index push(T value)

Push a Lua object, like a lua::index, lua::global, or lua::link, onto the stack. This
is defined as:

    return lua::push(value.state(), value);

*/

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
static void store_full_userdata(T& destination, lua::userdata_block* userdata, void* data)
{
    if (!userdata) {
        throw lua::error("The source userdata is nil, so it cannot be stored.");
        return;
    }
    // Carefully retrieve the value from the userdata.
    switch (userdata->storage()) {
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
static void store_full_userdata(T*& destination, lua::userdata_block* userdata, void* data)
{
    if (!userdata) {
        destination = nullptr;
        return;
    }
    // Get a pointer to the userdata's value.
    switch (userdata->storage()) {
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
static void store_full_userdata(T& destination, lua::userdata_block* userdata, void* data)
{
    if (!userdata) {
        destination.reset();
        return;
    }
    // Assign to the shared pointer; fail otherwise.
    switch (userdata->storage()) {
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

template <lua::userdata_storage storage, class T,
    typename std::enable_if<storage == lua::userdata_storage::pointer, int>::type = 0>
static void store_light_userdata(T*& destination, void* data)
{
    destination = static_cast<T*>(data);
}

template <lua::userdata_storage storage, class T,
    typename std::enable_if<storage == lua::userdata_storage::value, int>::type = 0>
static void store_light_userdata(T& destination, void* data)
{
    destination = *static_cast<T*>(data);
}

template <lua::userdata_storage storage, class T,
    typename std::enable_if<storage == lua::userdata_storage::shared_ptr, int>::type = 0>
static void store_light_userdata(std::shared_ptr<T>& destination, void* data)
{
    destination = *static_cast<std::shared_ptr<T>*>(data);
}

template <lua::userdata_storage storage, class T>
static void store_userdata(T& destination, const lua::index& source)
{
    if (lua_islightuserdata(source.state(), source.pos())) {
        store_light_userdata<storage>(
            destination,
            lua_touserdata(source.state(), source.pos())
        );
    } else {
        // Get a userdata value and set up the parameters for the inner procedure.
        auto block = static_cast<char*>(lua_touserdata(source.state(), source.pos()));
        if (!block) {
            std::stringstream str;
            str << "lua::store_userdata: Source at stack position " << source.pos()
                << " was a " << source.type().name() << ", not a userdata as required.";
            throw lua::error(str.str());
        }

        char* userdata_block = block + lua_rawlen(source.state(), source.pos()) - sizeof(lua::userdata_block);
        store_full_userdata<storage>(
            destination,
            reinterpret_cast<lua::userdata_block*>(userdata_block),
            block
        );
    }
}

template <typename T>
struct Store
{
    static void store(T& destination, const lua::index& source)
    {
        if (source.type().nil()) {
            throw lua::error("lua::Store<T>::store: source stack value must not be nil");
        }
        // Retrieve the userdata as a value
        store_userdata<lua::userdata_storage::value>(destination, source);
    }
};

template <typename T>
struct Store<T*>
{
    static void store(T*& destination, const lua::index& source)
    {
        if (source.type().nil()) {
            destination = nullptr;
            return;
        }
        // Retrieve the userdata as a pointer
        store_userdata<lua::userdata_storage::pointer>(destination, source);
    }
};

template <typename T>
struct Store<std::shared_ptr<T>>
{
    static void store(std::shared_ptr<T>& destination, const lua::index& source)
    {
        if (source.type().nil()) {
            destination.reset();
            return;
        }

        // Retrieve the userdata as a shared pointer
        store_userdata<lua::userdata_storage::shared_ptr>(destination, source);
    }
};

/*

=head2 lua::store(T& destination, const lua::index& source)

Store the value at the given index into the object specified by destination.

    lua::push(state, 42);

    int foo = 0;
    lua::store(foo, lua::index(state, -1));
    assert(foo == 42);

Internally, this refers to the lua::Store<T> struct, so behavior can be
specialized for new types. For instance, this is the definition for
lua::Store<std::string>:

    template <>
    struct Store<std::string>
    {
        static void store(std::string& destination, const lua::index& source)
        {
            destination = lua::get<const char*>(source);
        }
    };

*/

template <class T>
void store(T& destination, const lua::index& source)
{
    // Forward to the struct (for convenience)
    lua::Store<T>::store(destination, source);
}

template <class T>
void store(T& destination, lua_State* const state, const int pos)
{
    // Forward to the struct (for convenience)
    lua::Store<T>::store(destination, lua::index(state, pos));
}

template <class Source, class Name>
template <class T>
void lua::link<Source, Name>::operator>>(T& destination)
{
    lua::store(destination, *this);
}

/*

=head2 lua::index& operator>>(lua::index& source, T& destination)

Stores the value at source into the value at destination. This is
useful purely for its clarity of expression.

    lua::index value(state, 1);

    int foo;
    value >> foo;

*/

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

/*

=head2 T lua::get<T>(Source source)

Retrieves the value at the given source (typically just a lua::index) as
the specified type.

    int value = lua::get<int>(lua::index(state, 1));

*/

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
T get(lua_State* const state, const int pos)
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

/*

=head2 T* lua::make<T>(state, Args... args)

Create a userdata of type T on the Lua stack, calling T's constructor with the
specified arguments.

    Sum* sum = lua::make<Sum>(state, lua_tointeger(state, -1));

*/

template <class T, class... Args>
T* make(lua_State* const state, Args&&... args)
{
    Construct<T>::construct(state, args...);
    return lua::get<T*>(state, -1);
}

} // namespace lua

#endif // LUACXX_STACK_INCLUDED

#include "convert/builtin.hpp"
#include "convert/const_char_p.hpp"

#ifndef LUACXX_THREAD_INCLUDED
#define LUACXX_THREAD_INCLUDED

#include "stack.hpp"
#include "global.hpp"

/*

=head1 NAME

lua::thread - convenient wrappng for Lua states

=head1 SYNOPSIS

    #include <luacxx/thread.hpp>

    int luaopen_Foo(lua_State* const state)
    {
        // Set up the table using a lua::thread wrapper
        lua::thread env(state);
        env["Foo"] = lua::value::table;

        return 0;
    }

=head1 DESCRIPTION

lua::thread offers a few C++-specific semantic additions to a plain Lua state.
The biggest is global support: env["foo"] will return a reference to the global
named foo. This can be chained together to produce env["Device"]["Open"] and
so forth.

The thread can also own its Lua state, calling lua_close() on it when the
thread is being destroyed. Ownership is not enforced, but for quick demos, as
well as situations with many different states (like in a threading situation),
the ownership can be useful.

lua::thread converts to a lua_State automatically, so its usage does not
muddy up the rest of the API.

*/

namespace lua {

class thread {

lua_State* _state;
bool _owner;

public:

/*

=head2 lua::thread env(state)

Creates a new lua::thread that wraps the given state.

No ownership is transferred.

*/
thread(lua_State* const state) :
    _state(state),
    _owner(false)
{
}

/*

=head2 lua_State* lua::thread::state()

Returns the underlying state.

*/
lua_State* const state() const
{
    return _state;
}


/*

=head2 lua::global operator[](std::string)

Returns a reference to the lua::global with the given name.

*/
lua::global operator[](const std::string& name)
{
    return lua::global(_state, name);
}

thread& operator=(lua::thread& other)
{
    _state = other._state;
    other._owner = false;
    _owner = true;

    return *this;
}

thread& operator=(const lua::thread& other)
{
    _state = other._state;
    _owner = false;
    return *this;
}

/*

=head2 set_as_owner(), clear_owner(), is_owner()

Manages whether the lua::thread will close its lua_State upon destruction.
These will make no attempt to ensure exclusivity.

    // Create a new thread; note that ownership is transferred through assignment
    lua::thread env = lua::create();

    if (env.is_owner()) {
        // Clear it
        env.clear_owner();
    } else {
        assert(0 && "lua::create() should own its state");
    }

    // Set it once again.
    env.set_as_owner();
*/
void set_as_owner()
{
    _owner = true;
}

void clear_owner()
{
    _owner = false;
}

bool is_owner()
{
    return _owner;
}

operator lua_State*()
{
    return _state;
}

template <class T>
lua::thread& operator<<(T value)
{
    lua::push(_state, value);
    return *this;
}

template <class T>
lua::index operator>>(T& destination)
{
    return lua::index(_state, 1) >> destination;
}

~thread()
{
    if (_owner) {
        lua_close(_state);
    }
}
};

/*

=head4 lua::thread create();

Conveniently creates a new Lua state with standard libraries that is owned by
the returned lua::thread; when lua::thread is destroyed, its underlying state
will be closed. Use clear_owner() to opt-out of this automatic behavior.

*/

lua::thread create();

template <>
struct Push<lua::thread>
{
    static void push(lua_State* const state, lua::thread& env)=delete;
};

template <>
struct Store<lua::thread>
{
    static void store(lua::thread& destination, lua::index& index)=delete;
};

int size(const lua::thread& env);

} // namespace lua

#endif // LUACXX_THREAD_INCLUDED

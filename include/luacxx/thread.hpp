#ifndef LUACXX_THREAD_INCLUDED
#define LUACXX_THREAD_INCLUDED

#include "stack.hpp"
#include "global.hpp"

// Lightweight wrapper around lua_State* with global access and optional state
// ownership. See docs/reference/thread-and-algorithms.md for extended notes.

namespace lua {

class thread {

lua_State* _state;
bool _owner;

public:

thread(lua_State* const state) :
    _state(state),
    _owner(false)
{
}

lua_State* state() const
{
    return _state;
}

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

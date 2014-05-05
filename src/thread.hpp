#ifndef LUACXX_THREAD_HEADER
#define LUACXX_THREAD_HEADER

#include "stack.hpp"
#include "global.hpp"

namespace lua {

class thread
{
    lua::state* _state;
public:
    thread(lua::state* const state) :
        _state(state)
    {
    }

    thread() :
        thread(luaL_newstate())
    {
    }

    lua::state* const state()
    {
        return _state;
    }

    lua::index operator[](const int pos)
    {
        return lua::index(_state, pos);
    }

    global operator[](const std::string& name)
    {
        return lua::global(_state, name);
    }

    operator lua::state*()
    {
        return _state;
    }

    ~thread()
    {
        lua_close(_state);
    }
};

template <>
struct Push<lua::thread>
{
    static void push(lua::state* const state, lua::thread& env)=delete;
};

template <>
struct Store<lua::thread>
{
    static void store(lua::thread& destination, lua::index& index)=delete;
};

int size(lua::thread& env)
{
    return lua_gettop(env.state());
}

} // namespace lua

#endif // LUACXX_THREAD_HEADER

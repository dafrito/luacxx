#ifndef LUA_CXX_THREAD_HEADER
#define LUA_CXX_THREAD_HEADER

#include "stack.hpp"
#include "global.hpp"

namespace lua {

class thread
{
    lua::state* _state;
    bool _owner;

public:
    thread(lua::state* const state) :
        _state(state),
        _owner(false)
    {
    }

    lua::state* const state() const
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

    operator lua::state*()
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
    static void push(lua::state* const state, lua::thread& env)=delete;
};

template <>
struct Store<lua::thread>
{
    static void store(lua::thread& destination, lua::index& index)=delete;
};

int size(const lua::thread& env);

} // namespace lua

#endif // LUA_CXX_THREAD_HEADER

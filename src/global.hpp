#ifndef LUA_CXX_GLOBAL_HEADER
#define LUA_CXX_GLOBAL_HEADER

#include "stack.hpp"
#include <string>

namespace lua {

class global
{
    lua::state* const _state;
    std::string _name;

public:
    global(lua::state* const state, const std::string& name) :
        _state(state),
        _name(name)
    {
    }

    lua::state* const state() const
    {
        return _state;
    }

    const std::string& name() const
    {
        return _name;
    }

    lua::type type() const
    {
        auto rv = lua::push(_state, *this).type();
        lua_pop(_state, 1);
        return rv;
    }

    template <class T>
    global& operator=(T source)
    {
        lua::store(*this, lua::push(_state, source));
        lua_pop(_state, 1);
        return *this;
    }
};

template <>
struct Push<lua::global>
{
    static void push(lua::state* const state, const lua::global& source)
    {
        lua_getglobal(state, source.name().c_str());
    }
};

template <>
struct Store<lua::global>
{
    static void store(lua::global& global, const lua::index& source)
    {
        lua_pushvalue(source.state(), source.pos());
        lua_setglobal(global.state(), global.name().c_str());
    }
};

template <class T>
typename std::remove_const<typename std::remove_reference<T>::type>::type
get(const lua::global& source)
{
    typename std::remove_const<typename std::remove_reference<T>::type>::type destination;
    auto global_value = lua::push(source);
    lua::store(destination, global_value);
    return destination;
}

} // namespace lua

#endif // LUA_CXX_GLOBAL_HEADER

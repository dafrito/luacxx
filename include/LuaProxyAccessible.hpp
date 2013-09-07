#ifndef LUA_CXX_LUA_PROXY_ACCESSIBLE_HPP
#define LUA_CXX_LUA_PROXY_ACCESSIBLE_HPP

#include <memory>

#include "LuaAccessible.hpp"
#include "LuaStack.hpp"

class LuaProxyAccessible : public LuaAccessible
{
    std::shared_ptr<const LuaAccessible> _data;

public:
    LuaProxyAccessible(const LuaProxyAccessible& other) :
        _data(other._data)
    {
    }

    template <
        class T,
        typename std::enable_if<
            std::is_assignable<LuaAccessible, T>::value, int
        >::type = 0
    >
    LuaProxyAccessible(T& other) :
        _data(new T(other))
    {
    }

    void push(LuaStack& stack) const
    {
        _data->push(stack);
    }

    void store(LuaStack& stack) const
    {
        _data->store(stack);
    }
};

#endif // LUA_CXX_LUA_PROXY_ACCESSIBLE_HPP

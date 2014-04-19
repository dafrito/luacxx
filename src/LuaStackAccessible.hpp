#ifndef LUA_STACK_ACCESSIBLE_HPP
#define LUA_STACK_ACCESSIBLE_HPP

#include <lua.hpp>
#include "LuaStack.hpp"
#include "LuaAccessible.hpp"

class LuaStackAccessible : public LuaAccessible
{
    const int _pos;
public:
    LuaStackAccessible(LuaStack& stack, const int pos) :
        _pos(stack.absPos(pos))
    {
    }

    LuaStackAccessible(const int pos) :
        _pos(pos)
    {
        if (pos == 0) {
            throw std::out_of_range("Stack position must not be zero");
        }
    }

    int pos() const
    {
        return _pos;
    }

    int absPos(LuaStack& stack) const
    {
        auto index = pos();
        if (index < 0) {
            index += lua_gettop(stack.luaState()) + 1;
        }
        if (index <= 0) {
            throw std::out_of_range("Stack position must not underflow");
        }
        if (index > lua_gettop(stack.luaState())) {
            throw std::out_of_range("Stack position must not overflow");
        }
        return index;
    }

    void push(LuaStack& stack) const
    {
        // Use the Lua API since the position is treated as an absolute index
        lua_pushvalue(stack.luaState(), absPos(stack));
    }

    void store(LuaStack& stack) const
    {
        // Push a copy of the top value so that it's unaffected by this operation
        lua_pushvalue(stack.luaState(), -1);
        lua_replace(stack.luaState(), absPos(stack));
    }
};

typedef LuaValue<LuaStackAccessible> LuaStackValue;

#endif // LUA_STACK_ACCESSIBLE_HPP


#ifndef LUA_STACK_ACCESSIBLE_HPP
#define LUA_STACK_ACCESSIBLE_HPP

#include <lua.hpp>
#include "LuaEnvironment.hpp"
#include "LuaStack.hpp"

class LuaStackAccessible : public LuaAccessible
{
    const int _pos;
public:
    LuaStackAccessible(const int pos) :
        _pos(pos)
    {}

    int pos() const
    {
        return _pos;
    }

    void push(LuaStack& stack) const
    {
        stack.pushCopy(pos());
    }

    void store(LuaStack& stack) const
    {
        // Push a copy of the top value so that it's unaffected by this operation
        stack.pushCopy();
        stack.replace(pos());
    }
};

typedef LuaValue<LuaStackAccessible> LuaStackValue;

#endif // LUA_STACK_ACCESSIBLE_HPP


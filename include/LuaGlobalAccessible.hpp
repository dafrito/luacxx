#ifndef LUA_GLOBAL_ACCESSIBLE_HPP
#define LUA_GLOBAL_ACCESSIBLE_HPP

#include <lua.hpp>
#include "LuaAccessible.hpp"
#include "LuaEnvironment.hpp"
#include "LuaStack.hpp"

class LuaGlobalAccessible : public LuaAccessible
{
    const QString key;
public:
    LuaGlobalAccessible(Lua& lua, const QString& key) :
        LuaAccessible(lua),
        key(key)
    {}

    void push(LuaStack& stack) const
    {
        stack.global(key);
    }

    void store(LuaStack& stack) const
    {
        stack.setGlobal(key);
        push(stack);
    }
};

#endif // LUA_GLOBAL_ACCESSIBLE_HPP


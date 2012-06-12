#ifndef LUA_REFERENCE_ACCESSIBLE_HPP
#define LUA_REFERENCE_ACCESSIBLE_HPP

#include <lua.hpp>
#include "LuaAccessible.hpp"
#include "Lua.hpp"
#include "LuaStack.hpp"

class LuaReferenceAccessible : public LuaAccessible
{
    int ref;
public:
    LuaReferenceAccessible(Lua& lua) : LuaAccessible(lua)
    {
        ref = luaL_ref(luaState(), LUA_REGISTRYINDEX);
    }

    void push(LuaStack&)
    {
        lua_rawgeti(luaState(), LUA_REGISTRYINDEX, ref);
    }

    void store(LuaStack& stack)
    {
        lua_rawseti(luaState(), LUA_REGISTRYINDEX, ref);
        // Push it again to leave the stack unaffected by this
        // action.
        push(stack);
    }

    ~LuaReferenceAccessible()
    {
        luaL_unref(luaState(), LUA_REGISTRYINDEX, ref);
    }
};

#endif // LUA_REFERENCE_ACCESSIBLE_HPP

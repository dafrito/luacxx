#ifndef HEADER_LUA_ACCESSIBLE_HPP
#define HEADER_LUA_ACCESSIBLE_HPP

#include "LuaStack.hpp"
#include "types.hpp"

/**
 * Represents a method to access a value from Lua.
 *
 * There's currently three methods to reliably access
 * some value in Lua:
 *
 * 1. Global access
 * 2. Reference table access
 * 3. Indexed access
 *
 * Referenced access (through luaL_ref) is the safest
 * way to store and retrieve a value; the other methods
 * are publicly accessible, so the underlying value may
 * be changed between accesses.
 */
class LuaAccessible
{
	Lua& _lua;

protected:
    Lua& lua() const
    {
        return _lua;
    }

	lua_State* luaState() const
	{
		return lua().state;
	}
public:

	LuaAccessible(Lua& lua) : _lua(lua) {}

    /**
     * Pushes the value held by this accessible on
     * the specified stack.
     */
    virtual void push(LuaStack& stack)=0;

    /**
     * Sets this reference to the value on the top
     * of the specified stack.
     */
    virtual void store(LuaStack& stack)=0;

    virtual ~LuaAccessible() {}
};

#endif // HEADER_LUA_ACCESSIBLE_HPP


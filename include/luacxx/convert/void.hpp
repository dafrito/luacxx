#ifndef LUACXX_CONVERT_VOID_INCLUDED
#define LUACXX_CONVERT_VOID_INCLUDED

#include "../stack.hpp"

namespace lua {

template <>
struct Push<void*>
{
    static void push(lua_State* const state, void* const source)
    {
        lua_pushlightuserdata(state, source);
    }
};

template <>
struct Store<void*>
{
    static void store(void*& destination, lua_State* const state, const int source)
    {
        if (lua_islightuserdata(state, source)) {
            destination = lua_touserdata(state, source);
            return;
        }

        throw lua::error(state, "lua::Store<void*>::store: source must be light userdata");
    }
};
} // namespace lua

#endif // LUACXX_CONVERT_VOID_INCLUDED

#ifndef LUA_CXX_CHAR_HEADER
#define LUA_CXX_CHAR_HEADER

#include "../stack.hpp"

namespace lua {

template <>
struct Push<char>
{
    static void push(lua_State* const state, char& source)
    {
        lua_pushlstring(state, &source, 1);
    }
};

template <>
struct Store<char>
{
    static void store(char& destination, lua_State* const state, const int source)
    {
        if (lua_type(state, source) == LUA_TSTRING) {
            size_t len = 1;
            destination = *lua_tolstring(state, source, &len);
        } else {
            destination = lua_tonumber(state, source);
        }
    }
};

} // namespace lua

LUA_METATABLE_NAMED(char)
LUA_METATABLE_NAMED(char const)

#endif // LUA_CXX_CHAR_HEADER

#ifndef LUA_CXX_CHAR_HEADER
#define LUA_CXX_CHAR_HEADER

#include "../stack.hpp"

namespace lua {

template <>
struct Push<char>
{
    static void push(lua_State* const state, char source)
    {
        lua_pushlstring(state, &source, 1);
    }
};

template <>
struct Store<char>
{
    static void store(char& destination, lua_State* const state, const int source)
    {
        if (lua_type(state, source) != LUA_TSTRING) {
            throw lua::error(state, "lua::Store<char>::store: source must be a string of length 1");
        }

        size_t len = 0;
        auto str = lua_tolstring(state, source, &len);
        if (str == nullptr || len != 1) {
            throw lua::error(state, "lua::Store<char>::store: source must be a string of length 1");
        }

        destination = str[0];
    }
};

} // namespace lua

LUA_METATABLE_NAMED(char)
LUA_METATABLE_NAMED(char const)

#endif // LUA_CXX_CHAR_HEADER

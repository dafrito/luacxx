#ifndef LUA_CXX_CHAR_AS_LETTER_HEADER
#define LUA_CXX_CHAR_AS_LETTER_HEADER

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
    static void store(char& destination, const lua::index& source)
    {
        if (source.type().string()) {
            size_t len = 1;
            destination = *lua_tolstring(source.state(), source.pos(), &len);
        } else {
            destination = lua_tonumber(source.state(), source.pos());
        }
    }
};

} // namespace lua

#endif // LUA_CXX_CHAR_AS_LETTER_HEADER

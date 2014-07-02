#ifndef LUACXX_CONVERT_CONST_CHAR_P_INCLUDED
#define LUACXX_CONVERT_CONST_CHAR_P_INCLUDED

#include "../stack.hpp"

namespace lua {

template <>
struct Push<const char*>
{
    static void push(lua_State* const state, const char* const source)
    {
        lua_pushstring(state, source);
    }
};

template <>
struct Store<const char*>
{
    static void store(const char*& destination, const lua::index& source)
    {
        if (source.type().string()) {
            destination = lua_tostring(source.state(), source.pos());
        } else if (source.type().number()) {
            lua_pushvalue(source.state(), source.pos());
            destination = lua_tolstring(source.state(), -1, nullptr);
            lua_pop(source.state(), 1);
        }
        if (!destination) {
            destination = "";
        }
    }
};

} // namespace lua

#endif // LUACXX_CONVERT_CONST_CHAR_P_INCLUDED

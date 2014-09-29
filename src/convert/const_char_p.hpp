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
        destination = lua_tostring(source.state(), source.pos());
    }
};

template <>
struct Get<const char*>
{
    static const char* get(const lua::index& source)
    {
        return lua_tostring(source.state(), source.pos());
    }
};

} // namespace lua

#endif // LUACXX_CONVERT_CONST_CHAR_P_INCLUDED

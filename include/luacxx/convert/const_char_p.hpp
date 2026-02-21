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
struct Push<const char*&>
{
    static void push(lua_State* const state, const char*& source)
    {
        lua_pushstring(state, source);
    }
};

template <size_t N>
struct Push<const char (&)[N]>
{
    static void push(lua_State* const state, const char* source)
    {
        lua_pushstring(state, source);
    }
};

template <>
struct Store<const char*>
{
    static void store(const char*& destination, lua_State* const state, const int source)
    {
        destination = lua_tostring(state, source);
    }
};

template <>
struct Get<const char*>
{
    static const char* get(lua_State* const state, const int source)
    {
        return lua_tostring(state, source);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(const char*)

#endif // LUACXX_CONVERT_CONST_CHAR_P_INCLUDED

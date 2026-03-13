#ifndef LUACXX_CONVERT_CONST_CHAR_P_INCLUDED
#define LUACXX_CONVERT_CONST_CHAR_P_INCLUDED

#include "../stack.hpp"

#include <string_view>

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

template <>
struct Push<char*>
{
    static void push(lua_State* const state, const char* const source)
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

template <size_t N>
struct Push<char (&)[N]>
{
    static void push(lua_State* const state, const char* source)
    {
        lua_pushstring(state, source);
    }
};

template <>
struct Push<std::string_view>
{
    static void push(lua_State* const state, std::string_view source)
    {
        lua_pushlstring(state, source.data(), source.size());
    }
};

} // namespace lua

#endif // LUACXX_CONVERT_CONST_CHAR_P_INCLUDED

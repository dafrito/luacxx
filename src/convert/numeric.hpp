#ifndef luacxx_convert_numeric_INCLUDED
#define luacxx_convert_numeric_INCLUDED

#include "../stack.hpp"
#include "../algorithm.hpp"

/*

=head1 NAME

convert/numeric.hpp - support for C numeric types

=head1 SYNOPSIS

    #include <luacxx/convert/numeric.hpp>

=head1 DESCRIPTION

Most of these definitions are straight-forward.
Suffice it to say that if you want to push numeric
values onto Lua, you will almost certainly need to
have this header included.

=head4 lua_pushinteger(state, int), lua::push<int>

Pushes an integer onto the stack.

    #include <luacxx/convert/numeric.hpp>

    lua_pushinteger(state, 42);
    lua::push(state, 42);

=head4 lua_pushnumber(state, float), lua::push<float>

Pushes a floating-point value onto the stack.

    #include <luacxx/convert/numeric.hpp>

    lua_pushnumber(state, .5);
    lua::push(state, .5

*/

namespace lua {

template <>
struct Push<lua_Number>
{
    static void push(lua_State* const state, const lua_Number& value)
    {
        lua_pushnumber(state, value);
    }
};

template <>
struct Store<lua_Number>
{
    static void store(lua_Number& destination, lua_State* const state, const int source)
    {
        destination = lua_tonumber(state, source);
    }
};

LUA_METATABLE_NAMED(lua_Number);

template <>
struct Push<long>
{
    static void push(lua_State* const state, const long& source)
    {
        lua_pushinteger(state, source);
    }
};

void store_lua_Integer(long& destination, lua_State* const state, const int source);

template <>
struct Store<long>
{
    static void store(long& destination, lua_State* const state, const int source)
    {
        store_lua_Integer(destination, state, source);
    }
};

LUA_METATABLE_NAMED(lua_Integer);

template <>
struct Push<lua_Unsigned>
{
    static void push(lua_State* const state, const lua_Unsigned& source)
    {
        lua_pushinteger(state, source);
    }
};

void store_lua_Unsigned(lua_Unsigned& destination, lua_State* const state, const int source);

template <>
struct Store<lua_Unsigned>
{
    static void store(lua_Unsigned& destination, lua_State* const state, const int source)
    {
        store_lua_Unsigned(destination, state, source);
    }
};

LUA_METATABLE_NAMED(lua_Unsigned);

template <>
struct Push<bool>
{
    static void push(lua_State* const state, const bool& source)
    {
        lua_pushboolean(state, source);
    }
};

template <>
struct Store<bool>
{
    static void store(bool& destination, lua_State* const state, const int source)
    {
        destination = lua_toboolean(state, source);
    }
};

LUA_METATABLE_NAMED(bool)

template <>
struct Push<int>
{
    static void push(lua_State* const state, const int& value)
    {
        lua::push<lua_Integer>(state, value);
    }
};

template <>
struct Store<int>
{
    static void store(int& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::store(sink, state, source);
        destination = sink;
    }
};

LUA_METATABLE_NAMED(int)

template <>
struct Push<short>
{
    static void push(lua_State* const state, const short& value)
    {
        lua::push<lua_Integer>(state, value);
    }
};

template <>
struct Store<short>
{
    static void store(short& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::Store<lua_Integer>::store(sink, state, source);
        destination = sink;
    }
};

LUA_METATABLE_NAMED(short)

template <>
struct Push<unsigned short>
{
    static void push(lua_State* const state, const unsigned short& value)
    {
        lua::push<lua_Unsigned>(state, value);
    }
};

template <>
struct Store<unsigned short>
{
    static void store(unsigned short& destination, lua_State* const state, const int source)
    {
        lua_Unsigned sink;
        lua::Store<lua_Unsigned>::store(sink, state, source);
        destination = sink;
    }
};

LUA_METATABLE_NAMED(unsigned short)

template <>
struct Push<unsigned long>
{
    static void push(lua_State* const state, const unsigned long& value)
    {
        lua::push(state, static_cast<lua_Unsigned>(value));
    }
};

template <>
struct Store<unsigned long>
{
    static void store(unsigned long& destination, lua_State* const state, const int source)
    {
        destination = lua::Get<lua_Unsigned>::get(state, source);
    }
};

LUA_METATABLE_NAMED(unsigned long)

template <>
struct Push<long long>
{
    static void push(lua_State* const state, const long long& value)
    {
        lua::push(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<long long>
{
    static void store(long long& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::Store<lua_Integer>::store(sink, state, source);
        destination = sink;
    }
};

LUA_METATABLE_NAMED(long long)

template <>
struct Push<float>
{
    static void push(lua_State* const state, const float& value)
    {
        lua::Push<lua_Number>::push(state, value);
    }
};

template <>
struct Store<float>
{
    static void store(float& destination, lua_State* const state, const int source)
    {
        lua_Number sink;
        lua::Store<lua_Number>::store(sink, state, source);
        destination = static_cast<float>(sink);
    }
};

LUA_METATABLE_NAMED(float)

} // namespace lua

#endif // luacxx_convert_numeric_INCLUDED

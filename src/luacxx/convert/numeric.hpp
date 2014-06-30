#ifndef LUACXX_CONVERT_NUMERIC_INCLUDED
#define LUACXX_CONVERT_NUMERIC_INCLUDED

#include "../stack.hpp"

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
    static void store(lua_Number& destination, const lua::index& source)
    {
        destination = lua_tonumber(source.state(), source.pos());
    }
};

template <>
struct Push<lua_Integer>
{
    static void push(lua_State* const state, const lua_Integer& source)
    {
        lua_pushinteger(state, source);
    }
};

void store_lua_Integer(lua_Integer& destination, const lua::index& source);

template <>
struct Store<lua_Integer>
{
    static void store(lua_Integer& destination, const lua::index& source)
    {
        store_lua_Integer(destination, source);
    }
};

template <>
struct Push<lua_Unsigned>
{
    static void push(lua_State* const state, const lua_Unsigned& source)
    {
        lua_pushinteger(state, source);
    }
};

void store_lua_Unsigned(lua_Unsigned& destination, const lua::index& source);

template <>
struct Store<lua_Unsigned>
{
    static void store(lua_Unsigned& destination, const lua::index& source)
    {
        store_lua_Unsigned(destination, source);
    }
};

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
    static void store(bool& destination, const lua::index& source)
    {
        destination = lua_toboolean(source.state(), source.pos());
    }
};

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
    static void store(int& destination, const lua::index& source)
    {
        lua_Integer sink;
        lua::store(sink, source);
        destination = sink;
    }
};

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
    static void store(short& destination, const lua::index& source)
    {
        lua_Integer sink;
        lua::store(sink, source);
        destination = sink;
    }
};

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
    static void store(unsigned short& destination, const lua::index& source)
    {
        lua_Unsigned sink;
        lua::store(sink, source);
        destination = sink;
    }
};

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
    static void store(unsigned long& destination, const lua::index& source)
    {
        destination = lua::get<lua_Unsigned>(source);
    }
};

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
    static void store(long long& destination, const lua::index& source)
    {
        lua_Integer sink;
        lua::store(sink, source);
        destination = sink;
    }
};

template <>
struct Push<float>
{
    static void push(lua_State* const state, const float& value)
    {
        lua::push<lua_Number>(state, value);
    }
};

template <>
struct Store<float>
{
    static void store(float& destination, const lua::index& source)
    {
        lua_Number sink;
        lua::store(sink, source);
        destination = static_cast<float>(sink);
    }
};

} // namespace lua

#endif // LUACXX_CONVERT_NUMERIC_INCLUDED

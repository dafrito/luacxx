#ifndef LUA_CXX_TYPE_NUMERIC_HEADER
#define LUA_CXX_TYPE_NUMERIC_HEADER

#include "type/standard.hpp"

/*

=head1 NAME

type/numeric.hpp - support for C numeric types

=head1 SYNOPSIS

    #include <luacxx/type/numeric.hpp>

=head1 DESCRIPTION

Most of these definitions are straight-forward.
Suffice it to say that if you want to push numeric
values onto Lua, you will almost certainly need to
have this header included.

=head4 lua_pushinteger(state, int), lua::push<int>

Pushes an integer onto the stack.

    #include <luacxx/type/numeric.hpp>

    lua_pushinteger(state, 42);
    lua::push(state, 42);

=head4 lua_pushnumber(state, float), lua::push<float>

Pushes a floating-point value onto the stack.

    #include <luacxx/type/numeric.hpp>

    lua_pushnumber(state, .5);
    lua::push(state, .5

*/

namespace lua {

template <>
struct Push<int>
{
    static void push(lua::state* const state, const int& value)
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
struct Push<unsigned int>
{
    static void push(lua::state* const state, const unsigned int& value)
    {
        lua::push<lua_Integer>(state, value);
    }
};

template <>
struct Store<unsigned int>
{
    static void store(unsigned int& destination, const lua::index& source)
    {
        lua_Integer sink;
        lua::store(sink, source);
        destination = sink;
    }
};

template <>
struct Push<short>
{
    static void push(lua::state* const state, const short& value)
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
    static void push(lua::state* const state, const unsigned short& value)
    {
        lua::push<lua_Integer>(state, value);
    }
};

template <>
struct Store<unsigned short>
{
    static void store(unsigned short& destination, const lua::index& source)
    {
        lua_Integer sink;
        lua::store(sink, source);
        destination = sink;
    }
};

template <>
struct Push<long long>
{
    static void push(lua::state* const state, const long long& value)
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
    static void push(lua::state* const state, const float& value)
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

#endif // LUA_CXX_TYPE_NUMERIC_HEADER

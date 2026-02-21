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

/*
 * Stack bindings for floating-point types.
 */

template <>
struct Push<double>
{
    static void push(lua_State* const state, const double& value)
    {
        lua_pushnumber(state, static_cast<lua_Number>(value));
    }
};

template <>
struct Store<double>
{
    static void store(double& destination, lua_State* const state, const int source)
    {
        destination = static_cast<double>(lua_tonumber(state, source));
    }
};

} // namespace lua

LUA_METATABLE_NAMED(double);

namespace lua {

template <>
struct Push<float>
{
    static void push(lua_State* const state, const float& value)
    {
        lua_pushnumber(state, static_cast<lua_Number>(value));
    }
};

template <>
struct Store<float>
{
    static void store(float& destination, lua_State* const state, const int source)
    {
        destination = static_cast<float>(lua_tonumber(state, source));
    }
};

} // namespace lua

LUA_METATABLE_NAMED(float)

namespace lua {

/*
 * Stack bindings for integral types.
 */

/**
 * Store the value at the specified Lua stack position into the given destination.
 */
void store_lua_Integer(lua_Integer& destination, lua_State* const state, const int source_pos);

template <>
struct Push<long long>
{
    static void push(lua_State* const state, const long long& value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<long long>
{
    static void store(long long& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::store_lua_Integer(sink, state, source);
        destination = static_cast<long long>(sink);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(long long)

namespace lua {

template <>
struct Push<unsigned long long>
{
    static void push(lua_State* const state, const unsigned long long& value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<unsigned long long>
{
    static void store(unsigned long long& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::store_lua_Integer(sink, state, source);
        destination = static_cast<unsigned long long>(sink);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(unsigned long long)

namespace lua {

template <>
struct Push<long>
{
    static void push(lua_State* const state, const long& value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<long>
{
    static void store(long& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::store_lua_Integer(sink, state, source);
        destination = static_cast<long>(sink);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(long);

namespace lua {

template <>
struct Push<unsigned long>
{
    static void push(lua_State* const state, const unsigned long& value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<unsigned long>
{
    static void store(unsigned long& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::store_lua_Integer(sink, state, source);
        destination = static_cast<unsigned long>(sink);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(unsigned long)

/* Int */
namespace lua {

template <>
struct Push<int>
{
    static void push(lua_State* const state, const int& value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<int>
{
    static void store(int& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::store_lua_Integer(sink, state, source);
        destination = static_cast<int>(sink);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(int)

/* Unsigned int */
namespace lua {

template <>
struct Push<unsigned int>
{
    static void push(lua_State* const state, const unsigned int& value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<unsigned int>
{
    static void store(unsigned int& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::store_lua_Integer(sink, state, source);
        destination = static_cast<unsigned int>(sink);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(unsigned int)

/* Short */
namespace lua {

template <>
struct Push<short>
{
    static void push(lua_State* const state, const short& value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<short>
{
    static void store(short& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::store_lua_Integer(sink, state, source);
        destination = static_cast<short>(sink);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(short)

/* Unsigned short */
namespace lua {

template <>
struct Push<unsigned short>
{
    static void push(lua_State* const state, const short& value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<unsigned short>
{
    static void store(unsigned short& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::store_lua_Integer(sink, state, source);
        destination = static_cast<unsigned short>(sink);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(unsigned short)

namespace lua {

/* Unsigned char */

template <>
struct Push<unsigned char>
{
    static void push(lua_State* const state, const unsigned char& value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<unsigned char>
{
    static void store(unsigned char& destination, lua_State* const state, const int source)
    {
        lua_Integer sink;
        lua::store_lua_Integer(sink, state, source);
        destination = static_cast<unsigned char>(sink);
    }
};

} // namespace lua

LUA_METATABLE_NAMED(unsigned char)

namespace lua {

/* Boolean types */

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

} // namespace lua

LUA_METATABLE_NAMED(bool)

#endif // luacxx_convert_numeric_INCLUDED

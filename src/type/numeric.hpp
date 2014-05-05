#ifndef LUA_CXX_TYPE_NUMERIC_HEADER
#define LUA_CXX_TYPE_NUMERIC_HEADER

#include "type/standard.hpp"

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
        lua::store<lua_Integer>(sink, source);
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
        lua::store<lua_Integer>(sink, source);
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
        lua::store<lua_Integer>(sink, source);
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
        lua::store<lua_Integer>(sink, source);
        destination = sink;
    }
};

template <>
struct Push<long long>
{
    static void push(lua::state* const state, const long long& value)
    {
        lua::push<lua_Integer>(state, static_cast<lua_Integer>(value));
    }
};

template <>
struct Store<long long>
{
    static void store(long long& destination, const lua::index& source)
    {
        lua_Integer sink;
        lua::store<lua_Integer>(sink, source);
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
        lua::store<lua_Number>(sink, source);
        destination = static_cast<float>(sink);
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_NUMERIC_HEADER

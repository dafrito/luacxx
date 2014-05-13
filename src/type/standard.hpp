#ifndef LUA_CXX_TYPE_STANDARD_HEADER
#define LUA_CXX_TYPE_STANDARD_HEADER

#include "../push.hpp"
#include "../store.hpp"

#include <string>
#include <sstream>

namespace lua {

enum class value {
    nil = LUA_TNIL,
    table = LUA_TTABLE,
    globals = LUA_RIDX_MAINTHREAD,
    thread = LUA_TTHREAD,
    registry = LUA_REGISTRYINDEX
};

template <>
struct Push<lua::value>
{
    static void push(lua::state* const state, const lua::value& value)
    {
        switch (value) {
            case lua::value::table:
                lua_newtable(state);
                break;
            case lua::value::globals:
                lua_pushglobaltable(state);
                break;
            case lua::value::nil:
                lua_pushnil(state);
                break;
            case lua::value::thread:
                lua_newthread(state);
                break;
            case lua::value::registry:
                lua_pushvalue(state, LUA_REGISTRYINDEX);
                break;
        }
    }
};

template <>
struct Push<lua::index>
{
    static void push(lua::state* const state, const lua::index& source)
    {
        lua_pushvalue(state, source.pos());
    }
};

template <>
struct Store<const lua::index>
{
    static void store(const lua::index& destination, const lua::index& source)
    {
        lua_pushvalue(source.state(), source.pos());
        lua_replace(destination.state(), destination.pos());
    }
};

template <>
struct Push<lua_Number>
{
    static void push(lua::state* const state, const lua_Number& value)
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
    static void push(lua::state* const state, const lua_Integer& source)
    {
        lua_pushinteger(state, source);
    }
};

template <>
struct Store<lua_Integer>
{
    static void store(lua_Integer& destination, const lua::index& source)
    {
        int isnum;
        destination = lua_tointegerx(source.state(), source.pos(), &isnum);
        if (!isnum) {
            std::stringstream str;
            str << "lua::store<lua_Integer>: Numeric conversion failed for Lua stack value at index: ";
            str << source.type().name();
            throw lua::error(str.str());
        }
    }
};

template <>
struct Push<bool>
{
    static void push(lua::state* const state, const bool& source)
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
struct Push<char*>
{
    static void push(lua::state* const state, const char* const source)
    {
        lua::push(state, source);
    }
};

template <>
struct Push<const char*>
{
    static void push(lua::state* const state, const char* const source)
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

template <>
struct Push<std::string>
{
    static void push(lua::state* const state, std::string& source)
    {
        lua::push(state, source.c_str());
    }
};

template <>
struct Store<std::string>
{
    static void store(std::string& destination, const lua::index& source)
    {
        destination = lua::get<const char*>(source);
    }
};

template <>
struct Get<const std::string&>
{
    static std::string get(const lua::index& source)
    {
        return lua::Get<std::string>::get(source);
    }
};

template <>
struct Push<void*>
{
    static void push(lua::state* const state, void* const source)
    {
        lua_pushlightuserdata(state, source);
    }
};

template <>
struct Store<void*>
{
    static void store(void*& destination, const lua::index& source)
    {
        destination = lua_touserdata(source.state(), source.pos());
    }
};

template <>
struct Push<char>
{
    static void push(lua::state* const state, char& source)
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

#endif // LUA_CXX_TYPE_STANDARD_HEADER

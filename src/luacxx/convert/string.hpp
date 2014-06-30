#ifndef LUACXX_CONVERT_STRING_INCLUDED
#define LUACXX_CONVERT_STRING_INCLUDED

#include "../stack.hpp"

#include <string>

namespace lua {

template <>
struct Push<std::string>
{
    static void push(lua_State* const state, std::string& source)
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

#endif // LUACXX_CONVERT_STRING_INCLUDED

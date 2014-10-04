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
        lua::Push<const char*>::push(state, source.c_str());
    }
};

template <>
struct Store<std::string>
{
    static void store(std::string& destination, lua_State* const state, const int source)
    {
        destination = lua::Get<const char*>::get(state, source);
    }
};

template <>
struct Get<const std::string&>
{
    static std::string get(lua_State* const state, const int source)
    {
        return lua::Get<std::string>::get(state, source);
    }
};

} // namespace lua

#endif // LUACXX_CONVERT_STRING_INCLUDED

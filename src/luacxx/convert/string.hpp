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

} // namespace lua

#endif // LUACXX_CONVERT_STRING_INCLUDED

#ifndef luacxx_convert_string_INCLUDED
#define luacxx_convert_string_INCLUDED

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
        auto str = lua::Get<const char*>::get(state, source);
        if (str != nullptr) {
            destination = str;
        } else {
            destination.clear();
        }
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

LUA_METATABLE_NAMED(std::string);

#endif // luacxx_convert_string_INCLUDED

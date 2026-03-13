#ifndef luacxx_convert_string_INCLUDED
#define luacxx_convert_string_INCLUDED

#include "../stack.hpp"

#include <string>
#include <string_view>

namespace lua {

template <>
struct Push<std::string>
{
    static void push(lua_State* const state, std::string& source)
    {
        lua_pushlstring(state, source.data(), source.size());
    }

    static void push(lua_State* const state, const std::string& source)
    {
        lua_pushlstring(state, source.data(), source.size());
    }
};

template <>
struct Push<const std::string&>
{
    static void push(lua_State* const state, const std::string& source)
    {
        lua_pushlstring(state, source.data(), source.size());
    }
};

template <>
struct Store<std::string>
{
    static void store(std::string& destination, lua_State* const state, const int source)
    {
        size_t len = 0;
        auto str = lua_tolstring(state, source, &len);
        if (str != nullptr) {
            destination.assign(str, len);
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

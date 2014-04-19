#ifndef LUA_TYPES_HPP
#define LUA_TYPES_HPP

#include <lua.hpp>

namespace lua
{
    enum class type
    {
        invalid = LUA_TNONE, // For invalid stack indices
        nil = LUA_TNIL,
        boolean = LUA_TBOOLEAN,
        number = LUA_TNUMBER,
        string = LUA_TSTRING,
        table = LUA_TTABLE,
        function = LUA_TFUNCTION,
        thread = LUA_TTHREAD,
        userdata = LUA_TUSERDATA,
        lightuserdata = LUA_TLIGHTUSERDATA
    };

    lua::type convertType(const int& luaType);
}

#endif

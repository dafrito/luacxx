#include "types.hpp"

lua::type lua::convertType(const int& luaType)
{
    switch(luaType) {
    case LUA_TNIL:           return lua::type::nil;
    case LUA_TBOOLEAN:       return lua::type::boolean;
    case LUA_TNUMBER:        return lua::type::number;
    case LUA_TSTRING:        return lua::type::string;
    case LUA_TTABLE:         return lua::type::table;
    case LUA_TFUNCTION:      return lua::type::function;
    case LUA_TTHREAD:        return lua::type::thread;
    case LUA_TUSERDATA:      return lua::type::userdata;
    case LUA_TLIGHTUSERDATA: return lua::type::lightuserdata;
    default:                 return lua::type::invalid;
    }
}

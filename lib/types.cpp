#include "types.hpp"

lua::Type lua::convert_lua_type(const int& luaType)
{
    switch(luaType) {
    case LUA_TNIL:           return lua::Type::NIL;
    case LUA_TBOOLEAN:       return lua::Type::BOOLEAN;
    case LUA_TNUMBER:        return lua::Type::NUMBER;
    case LUA_TSTRING:        return lua::Type::STRING;
    case LUA_TTABLE:         return lua::Type::TABLE;
    case LUA_TFUNCTION:      return lua::Type::FUNCTION;
    case LUA_TTHREAD:        return lua::Type::THREAD;
    case LUA_TUSERDATA:      return lua::Type::USERDATA;
    case LUA_TLIGHTUSERDATA: return lua::Type::LIGHTUSERDATA;
    default:                 return lua::Type::INVALID;
    }
}

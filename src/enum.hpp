#ifndef luacxx_enum_INCLUDED
#define luacxx_enum_INCLUDED

#include "stack.hpp"

template <class T>
int enum_value(lua_State* const state)
{
    auto& self = lua::Get<const T&>::get(state, 1);
    lua_pushinteger(state, static_cast<lua_Integer>(self));
    return 1;
}

template <class T>
int enum_eq(lua_State* const state)
{
    auto& self = lua::Get<T&>::get(state, 1);
    auto& other = lua::Get<T&>::get(state, 2);

    if (lua::get_userdata_block(state, 1)->type() != lua::get_userdata_block(state, 2)->type()) {
        lua_pushboolean(state, false);
        return 1;
    }

    lua_pushboolean(state, self == other);
    return 1;
}

#define LUA_METATABLE_ENUM(name) \
namespace lua { \
\
template<> \
struct Metatable<name> \
{ \
    static const userdata_type& info() \
    { \
        static userdata_type _info(#name); \
        if (!_info.has_casts()) {\
            _info.add_cast<name>(); \
        } \
        return _info; \
    } \
\
    static bool metatable(lua_State* const state, const int pos, const void*) \
    { \
        lua_pushstring(state, "value"); \
        lua_pushcfunction(state, enum_value<name>); \
        lua_rawset(state, pos); \
        \
        lua_pushstring(state, "__eq"); \
        lua_pushcfunction(state, enum_eq<name>); \
        lua_rawset(state, pos); \
        return true; \
    } \
}; \
\
};

// Create metatable for logging enums
LUA_METATABLE_ENUM(lua::LogMessageType);

#endif // luacxx_enum_INCLUDED

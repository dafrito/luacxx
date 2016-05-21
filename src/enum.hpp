#ifndef luacxx_enum_INCLUDED
#define luacxx_enum_INCLUDED

#include "stack.hpp"

template <class T>
int enum_value(lua_State* const state)
{
    auto self = lua::Get<T>::get(state, 1);
    auto v = static_cast<lua_Integer>(self);
    lua_pushinteger(state, v);
    return 1;
}

template <class T>
int enum_eq(lua_State* const state)
{
    if (lua::get_userdata_block(state, 1)->type() != lua::get_userdata_block(state, 2)->type()) {
        lua_pushboolean(state, false);
        return 1;
    }

    // Perform a direct comparision.
    auto self = lua::Get<T>::get(state, 1);
    auto other = lua::Get<T>::get(state, 2);
    lua_pushboolean(state, self == other);

    return 1;
}

template <class T>
int enum_bor(lua_State* const state)
{
    auto self = lua::Get<T>::get(state, 1);
    auto other = lua::Get<T>::get(state, 2);

    lua::Push<T>::push(state, static_cast<T>(static_cast<int>(self) | static_cast<int>(other)));
    return 1;
}

template <class T>
int enum_band(lua_State* const state)
{
    auto self = lua::Get<T>::get(state, 1);
    auto other = lua::Get<T>::get(state, 2);

    lua::Push<T>::push(state, static_cast<T>(static_cast<int>(self) & static_cast<int>(other)));
    return 1;
}

template <class T>
int enum_bxor(lua_State* const state)
{
    auto self = lua::Get<T>::get(state, 1);
    auto other = lua::Get<T>::get(state, 2);

    lua::Push<T>::push(state, static_cast<T>(static_cast<int>(self) & static_cast<int>(other)));
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
        auto setfunc = [=]( \
            const char* funcname, \
            lua_CFunction func \
        ) { \
            lua_pushstring(state, funcname); \
            lua_pushcfunction(state, func); \
            lua_rawset(state, pos); \
        }; \
        setfunc("value", enum_value<name>); \
        setfunc("__eq", enum_eq<name>); \
        setfunc("__bor", enum_bor<name>); \
        setfunc("__band", enum_band<name>); \
        setfunc("__bxor", enum_bxor<name>); \
        return true; \
    } \
}; \
\
};

// Create metatable for logging enums
LUA_METATABLE_ENUM(lua::LogMessageType);

#endif // luacxx_enum_INCLUDED

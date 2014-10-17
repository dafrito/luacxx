#ifndef LUACXX_QOBJECT_INCLUDED
#define LUACXX_QOBJECT_INCLUDED

#include <QObject>

#include "Qt5Core.hpp"
#include "../algorithm.hpp"
#include "../convert/string.hpp"

LUA_METATABLE_BUILT(QObject);
LUA_METATABLE_BUILT(QMetaMethod);

#define LUA_METATABLE_QOBJECT(name) \
template <> \
struct lua::Metatable<name> \
{ \
    static const lua::userdata_type& info() \
    { \
        static lua::userdata_type _info("name"); \
        return _info; \
    } \
\
    static bool metatable(lua_State* const state, const int pos, const void* const) \
    { \
        lua::QObject_metatable(state, pos); \
        return true; \
    } \
};


#endif // LUACXX_QOBJECT_INCLUDED

#ifndef luacxx_QMetaClassInfo_INCLUDED
#define luacxx_QMetaClassInfo_INCLUDED

#include "../stack.hpp"

#include <QMetaClassInfo>

LUA_METATABLE_BUILT(QMetaClassInfo)

extern "C" int luaopen_Qt5Core_QMetaClassInfo(lua_State* const);

#endif // luacxx_QMetaClassInfo_INCLUDED

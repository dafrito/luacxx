#ifndef LUACXX_QMIMEDATA_INCLUDED
#define LUACXX_QMIMEDATA_INCLUDED

#include "Qt5Core.hpp"

#include <QMimeData>

LUA_METATABLE_BUILT(QMimeData)

extern "C" int luaopen_Qt5Core_QMimeData(lua_State* const);

#endif // LUACXX_QMIMEDATA_INCLUDED

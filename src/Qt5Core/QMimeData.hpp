#ifndef LUACXX_QMIMEDATA_INCLUDED
#define LUACXX_QMIMEDATA_INCLUDED

#include "../stack.hpp"
#include "QObject.hpp"

#include <QMimeData>

LUA_METATABLE_INHERIT(QMimeData, QObject)

extern "C" int luaopen_Qt5Core_QMimeData(lua_State* const);

#endif // LUACXX_QMIMEDATA_INCLUDED

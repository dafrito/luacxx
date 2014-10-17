#ifndef LUACXX_QQUATERNION_INCLUDED
#define LUACXX_QQUATERNION_INCLUDED

#include "Qt5Gui.hpp"
#include <QQuaternion>

LUA_METATABLE_BUILT(QQuaternion);

extern "C" int luaopen_Qt5Gui_QQuaternion(lua_State* const);

#endif // LUACXX_QQUATERNION_INCLUDED

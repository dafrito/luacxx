#ifndef LUACXX_QVector3D_INCLUDED
#define LUACXX_QVector3D_INCLUDED

#include "Qt5Gui.hpp"

class QVector3D;

LUA_METATABLE_BUILT(QVector3D)

extern "C" int luaopen_Qt5Gui_QVector3D(lua_State* const);

#endif // LUACXX_QVector3D_INCLUDED

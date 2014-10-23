#ifndef LUACXX_QOPENGLCONTEXTGROUP_INCLUDED
#define LUACXX_QOPENGLCONTEXTGROUP_INCLUDED

#include "Qt5Gui.hpp"

#include <QOpenGLContextGroup>

LUA_METATABLE_BUILT(QOpenGLContextGroup);

extern "C" int luaopen_Qt5Gui_QOpenGLContextGroup(lua_State* const);

#endif // LUACXX_QOPENGLCONTEXTGROUP_INCLUDED

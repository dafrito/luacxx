#ifndef LUACXX_QOPENGLFUNCTIONS_INCLUDED
#define LUACXX_QOPENGLFUNCTIONS_INCLUDED

#include "Qt5Gui.hpp"

class QOpenGLFunctions;

LUA_METATABLE_BUILT(QOpenGLFunctions);

extern "C" int luaopen_Qt5Gui_QOpenGLFunctions(lua_State* const);

#endif // LUACXX_QOPENGLFUNCTIONS_INCLUDED

#ifndef LUACXX_QOPENGLCONTEXT_INCLUDED
#define LUACXX_QOPENGLCONTEXT_INCLUDED

#include "Qt5Gui.hpp"

#include <QOpenGLContext>

LUA_METATABLE_BUILT(QOpenGLContext);

extern "C" int luaopen_Qt5Gui_QOpenGLContext(lua_State* const);

#endif // LUACXX_QOPENGLCONTEXT_INCLUDED

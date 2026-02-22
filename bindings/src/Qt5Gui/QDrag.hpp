#ifndef LUACXX_QDRAG_INCLUDED
#define LUACXX_QDRAG_INCLUDED

#include "Qt5Gui.hpp"

#include <QDrag>

// http://qt-project.org/doc/qt-5/qdrag.html

LUA_METATABLE_INHERIT(QDrag, QObject);

extern "C" int luaopen_Qt5Gui_QDrag(lua_State* const);

#endif // LUACXX_QDRAG_INCLUDED

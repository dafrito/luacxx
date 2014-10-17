#ifndef LUACXX_QPIXMAP_INCLUDED
#define LUACXX_QPIXMAP_INCLUDED

#include "Qt5Gui.hpp"
#include <QPixmap>

// https://qt-project.org/doc/qt-5/qpixmap.html

LUA_METATABLE_BUILT(QPixmap);

extern "C" int luaopen_Qt5Gui_QPixmap(lua_State* const);

#endif // LUACXX_QPIXMAP_INCLUDED

#ifndef LUACXX_QIMAGE_INCLUDED
#define LUACXX_QIMAGE_INCLUDED

#include "Qt5Gui.hpp"

#include <QImage>

LUA_METATABLE_BUILT(QImage);

extern "C" int luaopen_Qt5Gui_QImage(lua_State* const);

#endif // LUACXX_QIMAGE_INCLUDED

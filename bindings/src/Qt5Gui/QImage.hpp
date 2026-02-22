#ifndef LUACXX_QIMAGE_INCLUDED
#define LUACXX_QIMAGE_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QImage>

LUA_METATABLE_BUILT(QImage);
LUA_METATABLE_ENUM(QImage::Format);
LUA_METATABLE_ENUM(QImage::InvertMode);

extern "C" int luaopen_Qt5Gui_QImage(lua_State* const);

#endif // LUACXX_QIMAGE_INCLUDED

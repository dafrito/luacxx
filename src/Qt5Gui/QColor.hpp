#ifndef LUACXX_QCOLOR_INCLUDED
#define LUACXX_QCOLOR_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QColor>

LUA_METATABLE_BUILT(QColor);
LUA_METATABLE_ENUM(QColor::Spec);
LUA_METATABLE_ENUM(QColor::NameFormat);

extern "C" int luaopen_Qt5Gui_QColor(lua_State* const);

#endif // LUACXX_QCOLOR_INCLUDED

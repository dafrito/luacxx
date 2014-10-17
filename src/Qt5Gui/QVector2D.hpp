#ifndef luacxx_QVector2D_INCLUDED
#define luacxx_QVector2D_INCLUDED

#include "Qt5Gui.hpp"

#include <QVector2D>

LUA_METATABLE_BUILT(QVector2D);

extern "C" int luaopen_Qt5Gui_QVector2D(lua_State* const);

#endif // LUACXX_QVector2D_INCLUDED

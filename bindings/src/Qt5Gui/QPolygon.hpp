#ifndef luacxx_QPolygon_INCLUDED
#define luacxx_QPolygon_INCLUDED

#include "Qt5Gui.hpp"

#include <QPolygon>

LUA_METATABLE_BUILT(QPolygon);

extern "C" int luaopen_Qt5Gui_QPolygon(lua_State* const);

#endif // luacxx_QPolygon_INCLUDED

#ifndef LUACXX_QPAINTERPATH_INCLUDED
#define LUACXX_QPAINTERPATH_INCLUDED

#include "Qt5Gui.hpp"

#include <QPainterPath>

LUA_METATABLE_BUILT(QPainterPath);

namespace lua {

void QPainterPath_Element_metatable(lua_State* const state, const int mt);

};

LUA_METATABLE_BUILT_WITH(QPainterPath::Element, QPainterPath_Element_metatable);

extern "C" int luaopen_Qt5Gui_QPainterPath(lua_State* const);

#endif // LUACXX_QPAINTERPATH_INCLUDED

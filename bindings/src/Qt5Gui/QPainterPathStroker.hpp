#ifndef LUACXX_QPAINTERPATHSTROKER_INCLUDED
#define LUACXX_QPAINTERPATHSTROKER_INCLUDED

#include "Qt5Gui.hpp"

#include <QPainterPathStroker>

// http://qt-project.org/doc/qt-5/qpainterpathstroker.html

LUA_METATABLE_BUILT(QPainterPathStroker);

extern "C" int luaopen_Qt5Gui_QPainterPathStroker(lua_State* const);

#endif // LUACXX_QPAINTERPATHSTROKER_INCLUDED

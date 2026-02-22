#ifndef LUA_CXX_QMENUBAR_INCLUDED
#define LUA_CXX_QMENUBAR_INCLUDED

#include "Qt5Widgets.hpp"

class QMenuBar;

LUA_METATABLE_BUILT(QMenuBar);

extern "C" int luaopen_Qt5Widgets_QMenuBar(lua_State* const);

#endif // LUA_CXX_QMENUBAR_INCLUDED

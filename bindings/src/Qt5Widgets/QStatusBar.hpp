#ifndef LUA_CXX_QSTATUSBAR_INCLUDED
#define LUA_CXX_QSTATUSBAR_INCLUDED

#include "Qt5Widgets.hpp"

class QStatusBar;

LUA_METATABLE_BUILT(QStatusBar);

extern "C" int luaopen_Qt5Widgets_QStatusBar(lua_State* const);

#endif // LUA_CXX_QSTATUSBAR_INCLUDED

#ifndef luacxx_QToolBar_INCLUDED
#define luacxx_QToolBar_INCLUDED

#include "Qt5Widgets.hpp"

class QToolBar;

LUA_METATABLE_BUILT(QToolBar);

extern "C" int luaopen_Qt5Widgets_QToolBar(lua_State* const);

#endif // luacxx_QToolBar_INCLUDED

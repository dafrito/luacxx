#ifndef LUA_CXX_QSTYLE_INCLUDED
#define LUA_CXX_QSTYLE_INCLUDED

#include "Qt5Widgets.hpp"

class QStyle;

LUA_METATABLE_BUILT(QStyle);

extern "C" int luaopen_Qt5Widgets_QStyle(lua_State* const);

#endif // LUA_CXX_QSTYLE_INCLUDED

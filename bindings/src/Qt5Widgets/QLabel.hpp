#ifndef LUA_CXX_QLABEL_INCLUDED
#define LUA_CXX_QLABEL_INCLUDED

#include "Qt5Widgets.hpp"

class QLabel;

LUA_METATABLE_BUILT(QLabel);

extern "C" int luaopen_Qt5Widgets_QLabel(lua_State* const);

#endif // LUA_CXX_QLABEL_INCLUDED

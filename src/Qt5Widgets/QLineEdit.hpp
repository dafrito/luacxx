#ifndef LUA_CXX_QLINEEDIT_INCLUDED
#define LUA_CXX_QLINEEDIT_INCLUDED

#include "Qt5Widgets.hpp"

class QLineEdit;

LUA_METATABLE_BUILT(QLineEdit);

extern "C" int luaopen_Qt5Widgets_QLineEdit(lua_State* const);

#endif // LUA_CXX_QLINEEDIT_INCLUDED

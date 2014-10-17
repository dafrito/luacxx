#ifndef LUA_CXX_QFRAME_INCLUDED
#define LUA_CXX_QFRAME_INCLUDED

#include "Qt5Widgets.hpp"

class QFrame;

LUA_METATABLE_BUILT(QFrame);

extern "C" int luaopen_Qt5Widgets_QFrame(lua_State* const);

#endif // LUA_CXX_QFRAME_INCLUDED

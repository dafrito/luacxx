#ifndef LUA_CXX_QFRAME_INCLUDED
#define LUA_CXX_QFRAME_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QFrame>

#include "QWidget.hpp"

LUA_METATABLE_INHERIT(QFrame, QWidget);
LUA_METATABLE_ENUM(QFrame::Shadow);
LUA_METATABLE_ENUM(QFrame::Shape);
LUA_METATABLE_ENUM(QFrame::StyleMask);

extern "C" int luaopen_Qt5Widgets_QFrame(lua_State* const);

#endif // LUA_CXX_QFRAME_INCLUDED

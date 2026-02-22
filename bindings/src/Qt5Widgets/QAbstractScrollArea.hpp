#ifndef LUA_CXX_QABSTRACTSCROLLAREA_INCLUDED
#define LUA_CXX_QABSTRACTSCROLLAREA_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QAbstractScrollArea>

#include "QFrame.hpp"

// https://qt-project.org/doc/qt-5/qabstractscrollarea.html

LUA_METATABLE_INHERIT(QAbstractScrollArea, QFrame);
LUA_METATABLE_ENUM(QAbstractScrollArea::SizeAdjustPolicy);

extern "C" int luaopen_Qt5Widgets_QAbstractScrollArea(lua_State* const);

#endif // LUA_CXX_QABSTRACTSCROLLAREA_INCLUDED

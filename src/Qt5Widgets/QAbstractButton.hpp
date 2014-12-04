#ifndef luacxx_QAbstractButton_INCLUDED
#define luacxx_QAbstractButton_INCLUDED

#include "../stack.hpp"

#include <QAbstractButton>

#include "QWidget.hpp"

// http://qt-project.org/doc/qt-5/qabstractbutton.html

LUA_METATABLE_INHERIT(QAbstractButton, QWidget)

extern "C" int luaopen_Qt5Widgets_QAbstractButton(lua_State* const);

#endif // luacxx_QAbstractButton_INCLUDED

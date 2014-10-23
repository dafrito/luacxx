#ifndef LUA_CXX_QLINEEDIT_INCLUDED
#define LUA_CXX_QLINEEDIT_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include <QLineEdit>

LUA_METATABLE_BUILT(QLineEdit);
LUA_METATABLE_ENUM(QLineEdit::ActionPosition);
LUA_METATABLE_ENUM(QLineEdit::EchoMode);

extern "C" int luaopen_Qt5Widgets_QLineEdit(lua_State* const);

#endif // LUA_CXX_QLINEEDIT_INCLUDED

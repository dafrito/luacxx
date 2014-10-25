#ifndef luacxx_QTextEdit_INCLUDED
#define luacxx_QTextEdit_INCLUDED

#include "Qt5Widgets.hpp"

#include <QTextEdit>

LUA_METATABLE_BUILT(QTextEdit)

extern "C" int luaopen_Qt5Widgets_QTextEdit(lua_State* const);

#endif // luacxx_QTextEdit_INCLUDED

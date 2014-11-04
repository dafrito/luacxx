#ifndef luacxx_QTextEdit_INCLUDED
#define luacxx_QTextEdit_INCLUDED

#include "Qt5Widgets.hpp"
#include "../enum.hpp"

#include "QAbstractScrollArea.hpp"

#include <QTextEdit>

LUA_METATABLE_INHERIT(QTextEdit, QAbstractScrollArea);
LUA_METATABLE_NAMED(QTextEdit::ExtraSelection)
LUA_METATABLE_ENUM(QTextEdit::AutoFormattingFlag)
LUA_METATABLE_ENUM(QTextEdit::LineWrapMode)

extern "C" int luaopen_Qt5Widgets_QTextEdit(lua_State* const);

#endif // luacxx_QTextEdit_INCLUDED

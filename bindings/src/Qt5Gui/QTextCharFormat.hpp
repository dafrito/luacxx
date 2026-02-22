#ifndef luacxx_QTextCharFormat_INCLUDED
#define luacxx_QTextCharFormat_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QTextCharFormat>

LUA_METATABLE_BUILT(QTextCharFormat)
LUA_METATABLE_ENUM(QTextCharFormat::FontPropertiesInheritanceBehavior)
LUA_METATABLE_ENUM(QTextCharFormat::UnderlineStyle)
LUA_METATABLE_ENUM(QTextCharFormat::VerticalAlignment)

extern "C" int luaopen_Qt5Gui_QTextCharFormat(lua_State* const);

#endif // luacxx_QTextCharFormat_INCLUDED

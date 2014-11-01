#ifndef luacxx_QTextLine_INCLUDED
#define luacxx_QTextLine_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QTextLine>

LUA_METATABLE_BUILT(QTextLine)
LUA_METATABLE_ENUM(QTextLine::CursorPosition)
LUA_METATABLE_ENUM(QTextLine::Edge)

extern "C" int luaopen_Qt5Gui_QTextLine(lua_State* const);

#endif // luacxx_QTextLine_INCLUDED

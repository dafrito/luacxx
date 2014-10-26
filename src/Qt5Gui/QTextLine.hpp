#ifndef luacxx_QTextLine_INCLUDED
#define luacxx_QTextLine_INCLUDED

#include "../stack.hpp"

#include <QTextLine>

LUA_METATABLE_BUILT(QTextLine)
LUA_METATABLE_ENUM(QTextLine::CursorPosition)

extern "C" int luaopen_luacxx_QTextLine(lua_State* const);

#endif // luacxx_QTextLine_INCLUDED

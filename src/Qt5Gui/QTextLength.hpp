#ifndef luacxx_QTextLength_INCLUDED
#define luacxx_QTextLength_INCLUDED

#include "../stack.hpp"

#include <QTextLength>

LUA_METATABLE_BUILT(QTextLength)
LUA_METATABLE_ENUM(QTextLength::Type)

extern "C" int luaopen_Qt5Gui_QTextLength(lua_State* const);

#endif // luacxx_QTextLength_INCLUDED

#ifndef luacxx_QTextListFormat_INCLUDED
#define luacxx_QTextListFormat_INCLUDED

#include "../stack.hpp"

#include <QTextListFormat>

LUA_METATABLE_BUILT(QTextListFormat)
LUA_METATABLE_ENUM(QTextListFormat::Style)

extern "C" int luaopen_Qt5Gui_QTextListFormat(lua_State* const);

#endif // luacxx_QTextListFormat_INCLUDED

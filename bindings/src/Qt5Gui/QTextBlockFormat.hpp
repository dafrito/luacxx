#ifndef luacxx_QTextBlockFormat_INCLUDED
#define luacxx_QTextBlockFormat_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QTextBlockFormat>

LUA_METATABLE_BUILT(QTextBlockFormat)
LUA_METATABLE_ENUM(QTextBlockFormat::LineHeightTypes)

extern "C" int luaopen_Qt5Gui_QTextBlockFormat(lua_State* const);

#endif // luacxx_QTextBlockFormat_INCLUDED

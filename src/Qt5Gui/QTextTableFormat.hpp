#ifndef luacxx_QTextTableFormat_INCLUDED
#define luacxx_QTextTableFormat_INCLUDED

#include "../stack.hpp"

#include <QTextTableFormat>

LUA_METATABLE_BUILT(QTextTableFormat)

extern "C" int luaopen_luacxx_QTextTableFormat(lua_State* const);

#endif // luacxx_QTextTableFormat_INCLUDED

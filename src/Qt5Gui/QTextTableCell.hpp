#ifndef luacxx_QTextTableCell_INCLUDED
#define luacxx_QTextTableCell_INCLUDED

#include "../stack.hpp"

#include <QTextTableCell>

LUA_METATABLE_BUILT(QTextTableCell)

extern "C" int luaopen_luacxx_QTextTableCell(lua_State* const);

#endif // luacxx_QTextTableCell_INCLUDED

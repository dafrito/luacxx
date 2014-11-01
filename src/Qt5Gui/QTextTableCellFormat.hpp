#ifndef luacxx_QTextTableCellFormat_INCLUDED
#define luacxx_QTextTableCellFormat_INCLUDED

#include "../stack.hpp"

#include <QTextTableCellFormat>

LUA_METATABLE_BUILT(QTextTableCellFormat)

extern "C" int luaopen_luacxx_QTextTableCellFormat(lua_State* const);

#endif // luacxx_QTextTableCellFormat_INCLUDED

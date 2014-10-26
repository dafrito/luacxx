#ifndef luacxx_QTextTable_INCLUDED
#define luacxx_QTextTable_INCLUDED

#include "../stack.hpp"

#include <QTextTable>

LUA_METATABLE_BUILT(QTextTable)

extern "C" int luaopen_luacxx_QTextTable(lua_State* const);

#endif // luacxx_QTextTable_INCLUDED

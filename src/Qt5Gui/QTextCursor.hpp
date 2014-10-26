#ifndef luacxx_QTextCursor_INCLUDED
#define luacxx_QTextCursor_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QTextCursor>

LUA_METATABLE_BUILT(QTextCursor)
LUA_METATABLE_ENUM(QTextCursor::MoveMode)
LUA_METATABLE_ENUM(QTextCursor::MoveOperation)
LUA_METATABLE_ENUM(QTextCursor::SelectionType)

extern "C" int luaopen_luacxx_QTextCursor(lua_State* const);

#endif // luacxx_QTextCursor_INCLUDED

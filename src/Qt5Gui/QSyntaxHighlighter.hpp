#ifndef luacxx_QSyntaxHighlighter_INCLUDED
#define luacxx_QSyntaxHighlighter_INCLUDED

#include "../stack.hpp"

#include <QSyntaxHighlighter>

LUA_METATABLE_BUILT(QSyntaxHighlighter)

extern "C" int luaopen_luacxx_QSyntaxHighlighter(lua_State* const);

#endif // luacxx_QSyntaxHighlighter_INCLUDED

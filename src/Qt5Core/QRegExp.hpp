#ifndef luacxx_QRegExp_INCLUDED
#define luacxx_QRegExp_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QRegExp>

LUA_METATABLE_BUILT(QRegExp)
LUA_METATABLE_ENUM(QRegExp::CaretMode)
LUA_METATABLE_ENUM(QRegExp::PatternSyntax)

extern "C" int luaopen_Qt5Core_QRegExp(lua_State* const);

#endif // luacxx_QRegExp_INCLUDED

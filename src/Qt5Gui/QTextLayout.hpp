#ifndef luacxx_QTextLayout_INCLUDED
#define luacxx_QTextLayout_INCLUDED

#include "../stack.hpp"

#include <QTextLayout>

LUA_METATABLE_BUILT(QTextLayout)
LUA_METATABLE_ENUM(QTextLayout::CursorMode)

extern "C" int luaopen_luacxx_QTextLayout(lua_State* const);

#endif // luacxx_QTextLayout_INCLUDED

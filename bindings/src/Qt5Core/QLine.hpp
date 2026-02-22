#ifndef luacxx_QLine_INCLUDED
#define luacxx_QLine_INCLUDED

#include "../stack.hpp"

#include <QLine>

LUA_METATABLE_BUILT(QLine)

extern "C" int luaopen_Qt5Core_QLine(lua_State* const);

#endif // luacxx_QLine_INCLUDED

#ifndef luacxx_QFontMetricsF_INCLUDED
#define luacxx_QFontMetricsF_INCLUDED

#include "../stack.hpp"

#include <QFontMetricsF>

LUA_METATABLE_BUILT(QFontMetricsF)

extern "C" int luaopen_luacxx_QFontMetricsF(lua_State* const);

#endif // luacxx_QFontMetricsF_INCLUDED

#ifndef luacxx_QStaticText_INCLUDED
#define luacxx_QStaticText_INCLUDED

#include "../stack.hpp"

#include <QStaticText>

LUA_METATABLE_BUILT(QStaticText);

extern "C" int luaopen_luacxx_QStaticText(lua_State* const);

#endif // luacxx_QStaticText_INCLUDED

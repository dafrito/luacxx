#ifndef luacxx_QStaticText_INCLUDED
#define luacxx_QStaticText_INCLUDED

#include "../stack.hpp"

#include <QStaticText>

LUA_METATABLE_BUILT(QStaticText);
LUA_METATABLE_ENUM(QStaticText::PerformanceHint)

extern "C" int luaopen_Qt5Gui_QStaticText(lua_State* const);

#endif // luacxx_QStaticText_INCLUDED

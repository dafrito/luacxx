#ifndef luacxx_QScrollBar_INCLUDED
#define luacxx_QScrollBar_INCLUDED

#include "../stack.hpp"

#include <QScrollBar>

LUA_METATABLE_BUILT(QScrollBar)

extern "C" int luaopen_Qt5Widgets_QScrollBar(lua_State* const);

#endif // luacxx_QScrollBar_INCLUDED

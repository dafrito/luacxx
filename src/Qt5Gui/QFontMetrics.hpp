#ifndef LUACXX_QFONTMETRICS_INCLUDED
#define LUACXX_QFONTMETRICS_INCLUDED

#include "Qt5Gui.hpp"

class QFontMetrics;

LUA_METATABLE_BUILT(QFontMetrics);

extern "C" int luaopen_Qt5Gui_QFontMetrics(lua_State* const);

#endif // LUACXX_QFONTMETRICS_INCLUDED

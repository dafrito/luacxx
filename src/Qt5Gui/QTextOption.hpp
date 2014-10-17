#ifndef LUACXX_QTEXTOPTION_INCLUDED
#define LUACXX_QTEXTOPTION_INCLUDED

#include "Qt5Gui.hpp"

class QTextOption;

LUA_METATABLE_BUILT(QTextOption);

extern "C" int luaopen_Qt5Gui_QTextOption(lua_State* const);

#endif // LUACXX_QTEXTOPTION_INCLUDED

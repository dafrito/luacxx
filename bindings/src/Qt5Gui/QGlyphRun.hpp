#ifndef LUACXX_QGLYPHRUN_INCLUDED
#define LUACXX_QGLYPHRUN_INCLUDED

#include "Qt5Gui.hpp"

class QGlyphRun;

LUA_METATABLE_BUILT(QGlyphRun);

extern "C" int luaopen_Qt5Gui_QGlyphRun(lua_State* const);

#endif // LUACXX_QGLYPHRUN_INCLUDED

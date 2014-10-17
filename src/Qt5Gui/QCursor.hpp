#ifndef LUACXX_QCURSOR_INCLUDED
#define LUACXX_QCURSOR_INCLUDED

#include "Qt5Gui.hpp"

class QCursor;

LUA_METATABLE_BUILT(QCursor);

extern "C" int luaopen_Qt5Gui_QCursor(lua_State* const);

#endif // LUACXX_QCURSOR_INCLUDED

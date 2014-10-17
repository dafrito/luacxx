#ifndef LUACXX_QDRAG_INCLUDED
#define LUACXX_QDRAG_INCLUDED

#include "Qt5Gui.hpp"

class QDrag;

LUA_METATABLE_BUILT(QDrag);

extern "C" int luaopen_Qt5Gui_QDrag(lua_State* const);

#endif // LUACXX_QDRAG_INCLUDED

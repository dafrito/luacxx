#ifndef luacxx_QKeySequence_INCLUDED
#define luacxx_QKeySequence_INCLUDED

#include "Qt5Gui.hpp"

class QKeySequence;

LUA_METATABLE_BUILT(QKeySequence);

extern "C" int luaopen_Qt5Gui_QKeySequence(lua_State* const);

#endif // luacxx_QKeySequence_INCLUDED

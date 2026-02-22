#ifndef LUACXX_QMATRIX_INCLUDED
#define LUACXX_QMATRIX_INCLUDED

#include "Qt5Gui.hpp"

class QMatrix;

LUA_METATABLE_BUILT(QMatrix);

extern "C" int luaopen_Qt5Gui_QMatrix(lua_State* const);

#endif // LUACXX_QMATRIX_INCLUDED

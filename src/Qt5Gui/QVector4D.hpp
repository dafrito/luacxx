#ifndef luacxx_QVector4D_INCLUDED
#define luacxx_QVector4D_INCLUDED

#include "Qt5Gui.hpp"

#include <QVector4D>

LUA_METATABLE_BUILT(QVector4D);

extern "C" int luaopen_Qt5Gui_QVector4D(lua_State* const state);

#endif // luacxx_QVector4D_INCLUDED

#ifndef LUA_CXX_QMOVIE_INCLUDED
#define LUA_CXX_QMOVIE_INCLUDED

#include "Qt5Gui.hpp"

class QMovie;

LUA_METATABLE_BUILT(QMovie);

extern "C" int luaopen_Qt5Gui_QMovie(lua_State* const);

#endif // LUA_CXX_QMOVIE_INCLUDED

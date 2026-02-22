#ifndef LUA_CXX_QMOVIE_INCLUDED
#define LUA_CXX_QMOVIE_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QMovie>

LUA_METATABLE_BUILT(QMovie);
LUA_METATABLE_ENUM(QMovie::CacheMode);
LUA_METATABLE_ENUM(QMovie::MovieState);

extern "C" int luaopen_Qt5Gui_QMovie(lua_State* const);

#endif // LUA_CXX_QMOVIE_INCLUDED

#ifndef LUACXX_QSURFACE_INCLUDED
#define LUACXX_QSURFACE_INCLUDED

#include "Qt5Gui.hpp"
#include "../enum.hpp"

#include <QSurface>

/*

=head1 NAME

QSurface - https://qt-project.org/doc/qt-5/qsurface.html

*/

LUA_METATABLE_BUILT(QSurface);
LUA_METATABLE_ENUM(QSurface::SurfaceClass);
LUA_METATABLE_ENUM(QSurface::SurfaceType);

extern "C" int luaopen_Qt5Gui_QSurface(lua_State* const state);

#endif // LUACXX_QSURFACE_INCLUDED

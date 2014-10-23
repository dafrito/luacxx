#ifndef LUACXX_QWINDOW_INCLUDED
#define LUACXX_QWINDOW_INCLUDED

#include "Qt5Gui.hpp"
#include "../convert/string.hpp"
#include "../enum.hpp"

#include <QWindow>

/*

=head1 NAME

QWindow - http://qt-project.org/doc/qt-5/qwindow.html

*/

LUA_METATABLE_BUILT(QWindow);
LUA_METATABLE_ENUM(QWindow::AncestorMode);
LUA_METATABLE_ENUM(QWindow::Visibility);

extern "C" int luaopen_Qt5Gui_QWindow(lua_State* const);

#endif // LUACXX_QWINDOW_INCLUDED

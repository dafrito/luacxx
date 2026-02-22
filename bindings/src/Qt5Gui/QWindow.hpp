#ifndef LUACXX_QWINDOW_INCLUDED
#define LUACXX_QWINDOW_INCLUDED

#include "Qt5Gui.hpp"
#include "../convert/string.hpp"
#include "../enum.hpp"

#include <QWindow>

#include "QSurface.hpp"
#include "../Qt5Core/QObject.hpp"

/*

=head1 NAME

QWindow - http://qt-project.org/doc/qt-5/qwindow.html

*/

namespace lua {

void QWindow_metatable(lua_State* const state, const int mt);

template <>
struct Metatable<QWindow>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            _info.set_name("QWindow");
            _info.add_cast<QWindow>();
            _info.add_cast<QSurface, QWindow>();
            _info.add_cast<QObject, QWindow>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, void* const)
    {
        lua::QWindow_metatable(state, mt);
        return true;
    }
};

}; // namespace lua

LUA_METATABLE_ENUM(QWindow::AncestorMode);
LUA_METATABLE_ENUM(QWindow::Visibility);

extern "C" int luaopen_Qt5Gui_QWindow(lua_State* const);

#endif // LUACXX_QWINDOW_INCLUDED

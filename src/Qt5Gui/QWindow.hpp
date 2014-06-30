#ifndef LUACXX_QWINDOW_INCLUDED
#define LUACXX_QWINDOW_INCLUDED

#include "../luacxx/stack.hpp"
#include "../luacxx/convert/string.hpp"
#include "../luacxx/convert/callable.hpp"

#include <QWindow>

/*

=head1 NAME

QWindow - http://qt-project.org/doc/qt-5/qwindow.html

*/

namespace lua {

void QWindow_metatable(const lua::index& mt);

template <>
struct Metatable<QWindow>
{
    static constexpr const char* name = "QWindow";

    static bool metatable(const lua::index& mt, QWindow* const)
    {
        lua::QWindow_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Gui_QWindow(lua_State* const);

#endif // LUACXX_QWINDOW_INCLUDED

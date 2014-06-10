#ifndef LUA_CXX_QWINDOW_INCLUDED
#define LUA_CXX_QWINDOW_INCLUDED

#include "../stack.hpp"
#include "../type/standard.hpp"
#include "../type/function.hpp"

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

extern "C" int luaopen_luacxx_QWindow(lua_State* const);

#endif // LUA_CXX_QWINDOW_INCLUDED

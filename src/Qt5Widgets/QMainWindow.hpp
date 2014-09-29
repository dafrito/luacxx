#ifndef LUA_CXX_QMAINWINDOW_INCLUDED
#define LUA_CXX_QMAINWINDOW_INCLUDED

#include "../stack.hpp"

class QMainWindow;

namespace lua {

void QMainWindow_metatable(const lua::index& mt);

template <>
struct Metatable<QMainWindow>
{
    static constexpr const char* name = "QMainWindow";

    static bool metatable(const lua::index& mt, QMainWindow* const)
    {
        lua::QMainWindow_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QMainWindow(lua_State* const);

#endif // LUA_CXX_QMAINWINDOW_INCLUDED

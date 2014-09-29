#ifndef LUA_CXX_QTABWIDGET_INCLUDED
#define LUA_CXX_QTABWIDGET_INCLUDED

#include "../stack.hpp"

class QTabWidget;

namespace lua {

void QTabWidget_metatable(const lua::index& mt);

template <>
struct Metatable<QTabWidget>
{
    static constexpr const char* name = "QTabWidget";

    static bool metatable(const lua::index& mt, QTabWidget* const)
    {
        lua::QTabWidget_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QTabWidget(lua_State* const);

#endif // LUA_CXX_QTABWIDGET_INCLUDED

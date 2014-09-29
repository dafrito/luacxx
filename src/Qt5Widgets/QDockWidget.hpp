#ifndef LUA_CXX_QDOCKWIDGET_INCLUDED
#define LUA_CXX_QDOCKWIDGET_INCLUDED

#include "../stack.hpp"

class QDockWidget;

namespace lua {

void QDockWidget_metatable(const lua::index& mt);

template <>
struct Metatable<QDockWidget>
{
    static constexpr const char* name = "QDockWidget";

    static bool metatable(const lua::index& mt, QDockWidget* const)
    {
        lua::QDockWidget_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QDockWidget(lua_State* const);

#endif // LUA_CXX_QDOCKWIDGET_INCLUDED

#ifndef LUA_CXX_QGRAPHICSWIDGET_INCLUDED
#define LUA_CXX_QGRAPHICSWIDGET_INCLUDED

#include "../stack.hpp"

class QGraphicsWidget;

namespace lua {

void QGraphicsWidget_metatable(const lua::index& mt);

template <>
struct Metatable<QGraphicsWidget>
{
    static constexpr const char* name = "QGraphicsWidget";

    static bool metatable(const lua::index& mt, QGraphicsWidget* const)
    {
        lua::QGraphicsWidget_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsWidget(lua_State* const);

#endif // LUA_CXX_QGRAPHICSWIDGET_INCLUDED

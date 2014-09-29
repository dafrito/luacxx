#ifndef LUA_CXX_QGRAPHICSVIEW_INCLUDED
#define LUA_CXX_QGRAPHICSVIEW_INCLUDED

#include "../stack.hpp"

class QGraphicsView;

namespace lua {

void QGraphicsView_metatable(const lua::index& mt);

template <>
struct Metatable<QGraphicsView>
{
    static constexpr const char* name = "QGraphicsView";

    static bool metatable(const lua::index& mt, QGraphicsView* const)
    {
        lua::QGraphicsView_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsView(lua_State* const);

#endif // LUA_CXX_QGRAPHICSVIEW_INCLUDED

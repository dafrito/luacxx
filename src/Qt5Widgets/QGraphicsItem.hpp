#ifndef LUA_CXX_QGRAPHICSITEM_INCLUDED
#define LUA_CXX_QGRAPHICSITEM_INCLUDED

#include "../stack.hpp"

class QGraphicsItem;

namespace lua {

void QGraphicsItem_metatable(const lua::index& mt);

template <>
struct Metatable<QGraphicsItem>
{
    static constexpr const char* name = "QGraphicsItem";

    static bool metatable(const lua::index& mt, QGraphicsItem* const)
    {
        lua::QGraphicsItem_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsItem(lua_State* const);

#endif // LUA_CXX_QGRAPHICSITEM_INCLUDED

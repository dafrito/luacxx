#ifndef LUA_CXX_QGRAPHICSSCENE_INCLUDED
#define LUA_CXX_QGRAPHICSSCENE_INCLUDED

#include "../stack.hpp"

class QGraphicsScene;

namespace lua {

void QGraphicsScene_metatable(const lua::index& mt);

template <>
struct Metatable<QGraphicsScene>
{
    static constexpr const char* name = "QGraphicsScene";

    static bool metatable(const lua::index& mt, QGraphicsScene* const)
    {
        lua::QGraphicsScene_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsScene(lua_State* const);

#endif // LUA_CXX_QGRAPHICSSCENE_INCLUDED

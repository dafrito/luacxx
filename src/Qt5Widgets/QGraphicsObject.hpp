#ifndef LUA_CXX_QGRAPHICSOBJECT_INCLUDED
#define LUA_CXX_QGRAPHICSOBJECT_INCLUDED

#include "../stack.hpp"

class QGraphicsObject;

namespace lua {

void QGraphicsObject_metatable(const lua::index& mt);

template <>
struct Metatable<QGraphicsObject>
{
    static constexpr const char* name = "QGraphicsObject";

    static bool metatable(const lua::index& mt, QGraphicsObject* const)
    {
        lua::QGraphicsObject_metatable(mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsObject(lua_State* const);

#endif // LUA_CXX_QGRAPHICSOBJECT_INCLUDED

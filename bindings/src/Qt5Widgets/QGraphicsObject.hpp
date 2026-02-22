#ifndef LUA_CXX_QGRAPHICSOBJECT_INCLUDED
#define LUA_CXX_QGRAPHICSOBJECT_INCLUDED

#include "Qt5Widgets.hpp"

#include <QGraphicsObject>
#include "QGraphicsItem.hpp"
#include "../Qt5Core/QObject.hpp"

namespace lua {

void QGraphicsObject_metatable(lua_State* const state, const int mt);

template <>
struct Metatable<QGraphicsObject>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            _info.set_name("QGraphicsObject");
            _info.add_cast<QGraphicsObject>();
            _info.add_cast<QGraphicsItem, QGraphicsObject>();
            _info.add_cast<QObject, QGraphicsObject>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, void* const)
    {
        lua::QGraphicsObject_metatable(state, mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsObject(lua_State* const);

#endif // LUA_CXX_QGRAPHICSOBJECT_INCLUDED

#ifndef LUA_CXX_QGRAPHICSWIDGET_INCLUDED
#define LUA_CXX_QGRAPHICSWIDGET_INCLUDED

#include "Qt5Widgets.hpp"

#include <QGraphicsWidget>

#include "QGraphicsObject.hpp"
#include "QGraphicsLayoutItem.hpp"

namespace lua {

void QGraphicsWidget_metatable(lua_State* const state, const int mt);

template <>
struct Metatable<QGraphicsWidget>
{
    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            _info.set_name("QGraphicsWidget");
            _info.add_cast<QGraphicsWidget>();
            _info.add_cast<QGraphicsObject, QGraphicsWidget>();
            _info.add_cast<QGraphicsLayoutItem, QGraphicsWidget>();
        }
        return _info;
    }

    static bool metatable(lua_State* const state, const int mt, void* const)
    {
        lua::QGraphicsWidget_metatable(state, mt);
        return true;
    }
};

}; // namespace lua

extern "C" int luaopen_Qt5Widgets_QGraphicsWidget(lua_State* const);

#endif // LUA_CXX_QGRAPHICSWIDGET_INCLUDED

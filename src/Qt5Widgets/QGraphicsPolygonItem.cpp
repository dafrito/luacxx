#include "QGraphicsPolygonItem.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Gui/QPolygonF.hpp"
#include "../Qt5Core/Qt.hpp"

// https://qt-project.org/doc/qt-5/qgraphicspolygonitem.html

namespace lua {

void QGraphicsPolygonItem_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractGraphicsShapeItem_metatable(state, pos);

    lua::index mt(state, pos);
     mt["fillRule"] = &QGraphicsPolygonItem::fillRule;
     mt["polygon"] = &QGraphicsPolygonItem::polygon;
     mt["setFillRule"] = &QGraphicsPolygonItem::setFillRule;
     mt["setPolygon"] = &QGraphicsPolygonItem::setPolygon;
}

} // namespace lua

int QGraphicsPolygonItem_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QGraphicsPolygonItem()
        lua::make<QGraphicsPolygonItem>(state);
        break;
    case 1:
        if (lua::is_type<QPolygonF>(state, 1)) {
            // QGraphicsPolygonItem(const QPolygonF & polygon)
            lua::make<QGraphicsPolygonItem>(state,
                lua::get<const QPolygonF&>(state, 1)
            );
        } else {
            // QGraphicsPolygonItem(QGraphicsItem * parent)
            lua::make<QGraphicsPolygonItem>(state,
                lua::get<QGraphicsItem*>(state, 1)
            );
        }
        break;
    case 2:
        // QGraphicsPolygonItem(const QPolygonF & polygon, QGraphicsItem * parent)
        lua::make<QGraphicsPolygonItem>(state,
            lua::get<const QPolygonF&>(state, 1),
            lua::get<QGraphicsItem*>(state, 2)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsPolygonItem(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsPolygonItem"] = lua::value::table;
    env["QGraphicsPolygonItem"]["new"] = QGraphicsPolygonItem_new;
    auto t = env["QGraphicsPolygonItem"];

    return 0;
}

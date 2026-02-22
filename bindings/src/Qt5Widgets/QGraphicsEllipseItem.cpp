#include "QGraphicsEllipseItem.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QRectF.hpp"

// https://qt-project.org/doc/qt-5/qgraphicsellipseitem.html

int QGraphicsEllipseItem_setRect(lua_State* const state)
{
    auto self = lua::get<QGraphicsEllipseItem*>(state, 1);

    if (lua_gettop(state) == 2) {
        self->setRect(
            lua::get<const QRectF&>(state, 2)
        );
    } else {
        self->setRect(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        );
    }

    return 0;
}

namespace lua {

void QGraphicsEllipseItem_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractGraphicsShapeItem_metatable(state, pos);

    lua::index mt(state, pos);
    mt["rect"] = &QGraphicsEllipseItem::rect;
    mt["setRect"] = QGraphicsEllipseItem_setRect;
    mt["setSpanAngle"] = &QGraphicsEllipseItem::setSpanAngle;
    mt["setStartAngle"] = &QGraphicsEllipseItem::setStartAngle;
    mt["spanAngle"] = &QGraphicsEllipseItem::spanAngle;
    mt["startAngle"] = &QGraphicsEllipseItem::startAngle;
}

} // namespace lua

int QGraphicsEllipseItem_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QGraphicsEllipseItem()
        lua::make<QGraphicsEllipseItem>(state);
        break;
    case 1:
        if (lua::is_type<QRectF>(state, 1)) {
            // QGraphicsEllipseItem(const QRectF & rect)
            lua::make<QGraphicsEllipseItem>(state,
                lua::get<const QRectF&>(state, 1)
            );
        } else {
            // QGraphicsEllipseItem(QGraphicsItem * parent)
            lua::make<QGraphicsEllipseItem>(state,
                lua::get<QGraphicsItem*>(state, 1)
            );
        }
        break;
    case 2:
        // QGraphicsEllipseItem(const QRectF & rect, QGraphicsItem * parent)
        lua::make<QGraphicsEllipseItem>(state,
            lua::get<const QRectF&>(state, 1),
            lua::get<QGraphicsItem*>(state, 2)
        );
        break;
    case 4:
        // QGraphicsEllipseItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0)
        lua::make<QGraphicsEllipseItem>(state,
            lua::get<qreal>(state, 1),
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        );
        break;
    case 5:
        // QGraphicsEllipseItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0)
        lua::make<QGraphicsEllipseItem>(state,
            lua::get<qreal>(state, 1),
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<QGraphicsItem*>(state, 5)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsEllipseItem(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsEllipseItem"] = lua::value::table;
    env["QGraphicsEllipseItem"]["new"] = QGraphicsEllipseItem_new;
    auto t = env["QGraphicsEllipseItem"];

    return 0;
}

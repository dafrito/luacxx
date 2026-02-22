#include "QGraphicsRectItem.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QRectF.hpp"

int QGraphicsRectItem_setRect(lua_State* const state)
{
    auto self = lua::get<QGraphicsRectItem*>(state, 1);

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

void QGraphicsRectItem_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractGraphicsShapeItem_metatable(state, pos);

    lua::index mt(state, pos);
    mt["rect"] = &QGraphicsRectItem::rect;
    mt["setRect"] = QGraphicsRectItem_setRect;
}

} // namespace lua

int QGraphicsRectItem_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QGraphicsRectItem()
        lua::make<QGraphicsRectItem>(state);
        break;
    case 1:
        if (lua::is_type<QRectF>(state, 1)) {
            // QGraphicsRectItem(const QRectF & rect)
            lua::make<QGraphicsRectItem>(state,
                lua::get<const QRectF&>(state, 1)
            );
        } else {
            // QGraphicsRectItem(QGraphicsItem * parent)
            lua::make<QGraphicsRectItem>(state,
                lua::get<QGraphicsItem*>(state, 1)
            );
        }
        break;
    case 2:
        // QGraphicsRectItem(const QRectF & rect, QGraphicsItem * parent)
        lua::make<QGraphicsRectItem>(state,
            lua::get<const QRectF&>(state, 1),
            lua::get<QGraphicsItem*>(state, 2)
        );
        break;
    case 4:
        // QGraphicsRectItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0)
        lua::make<QGraphicsRectItem>(state,
            lua::get<qreal>(state, 1),
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        );
        break;
    case 5:
        // QGraphicsRectItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0)
        lua::make<QGraphicsRectItem>(state,
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

int luaopen_Qt5Widgets_QGraphicsRectItem(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsRectItem"] = lua::value::table;
    env["QGraphicsRectItem"]["new"] = QGraphicsRectItem_new;
    auto t = env["QGraphicsRectItem"];

    return 0;
}

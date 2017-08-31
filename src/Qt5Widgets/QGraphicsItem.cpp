#include "QGraphicsItem.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Gui/QPolygonF.hpp"
#include "../Qt5Gui/QPainter.hpp"
#include "../Qt5Gui/QPainterPath.hpp"
#include "../Qt5Gui/QCursor.hpp"
#include "../Qt5Gui/QTransform.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Gui/QRegion.hpp"
#include "QGraphicsEffect.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "QWidget.hpp"
#include "QGraphicsWidget.hpp"
#include "QGraphicsObject.hpp"
#include "QGraphicsScene.hpp"
#include "QGraphicsTransform.hpp"
#include "QGraphicsItemGroup.hpp"
#include "QStyleOptionGraphicsItem.hpp"
#include "../Qt5Core/QVariant.hpp"

#include <iostream>

int QGraphicsItem_collidesWithItem(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // virtual bool     collidesWithItem(const QGraphicsItem * other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const
    switch (lua_gettop(state)) {
    case 2:
        lua::push(state, self->collidesWithItem(
            lua::get<QGraphicsItem*>(state, 2)
        ));
        break;
    case 3:
    default:
        lua::push(state, self->collidesWithItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<Qt::ItemSelectionMode>(state, 3)
        ));
        break;
    }
    return 1;
}

int QGraphicsItem_collidesWithPath(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // virtual bool     collidesWithPath(const QPainterPath & path, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const
    switch (lua_gettop(state)) {
    case 2:
        lua::push(state, self->collidesWithPath(
            lua::get<const QPainterPath&>(state, 2)
        ));
        break;
    case 3:
    default:
        lua::push(state, self->collidesWithPath(
            lua::get<const QPainterPath&>(state, 2),
            lua::get<Qt::ItemSelectionMode>(state, 3)
        ));
        break;
    }
    return 1;
}

int QGraphicsItem_collidingItems(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // QList<QGraphicsItem *>   collidingItems(Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const
    switch (lua_gettop(state)) {
    case 1:
        lua::push(state, self->collidingItems());
        break;
    case 2:
    default:
        lua::push(state, self->collidingItems(
            lua::get<Qt::ItemSelectionMode>(state, 2)
        ));
    }
    return 1;
}

int QGraphicsItem_ensureVisible(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua_isnumber(state, 2)) {
        //  void    ensureVisible(qreal x, qreal y, qreal w, qreal h, int xmargin = 50, int ymargin = 50)
        switch (lua_gettop(state)) {
        case 5:
            self->ensureVisible(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5)
            );
            break;
        case 6:
            self->ensureVisible(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5),
                lua::get<int>(state, 6)
            );
            break;
        case 7:
        default:
            self->ensureVisible(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5),
                lua::get<int>(state, 6),
                lua::get<int>(state, 7)
            );
            break;
        }
    } else {
        //  void    ensureVisible(const QRectF & rect = QRectF(), int xmargin = 50, int ymargin = 50)
        switch (lua_gettop(state)) {
        case 1:
            self->ensureVisible();
            break;
        case 2:
            self->ensureVisible(
                lua::get<const QRectF&>(state, 2)
            );
            break;
        case 3:
            self->ensureVisible(
                lua::get<const QRectF&>(state, 2),
                lua::get<int>(state, 3)
            );
            break;
        case 4:
        default:
            self->ensureVisible(
                lua::get<const QRectF&>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4)
            );
            break;
        }
    }
    return 0;
}

int QGraphicsItem_isObscured(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua_isnumber(state, 2)) {
        // bool     isObscured(qreal x, qreal y, qreal w, qreal h) const
        lua::push(state, self->isObscured(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
    } else {
        // bool     isObscured(const QRectF & rect = QRectF()) const
        if (lua_gettop(state) == 1) {
            lua::push(state, self->isObscured());
        } else {
            lua::push(state, self->isObscured(
                lua::get<const QRectF&>(state, 2)
            ));
        }
    }
    return 1;
}

int QGraphicsItem_itemTransform(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // QTransform   itemTransform(const QGraphicsItem * other, bool * ok = 0) const
    switch (lua_gettop(state)) {
    case 2:
        bool ok;
        lua::push(state, self->itemTransform(
            lua::get<QGraphicsItem*>(state, 2),
            &ok
        ));
        lua::push(state, ok);
        return 2;
    case 3:
    default:
        lua::push(state, self->itemTransform(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<bool*>(state, 3)
        ));
        return 1;
    }
}

int QGraphicsItem_mapFromItem(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua::is_type<QPointF>(state, 3)) {
        // QPointF  mapFromItem(const QGraphicsItem * item, const QPointF & point) const
        lua::push(state, self->mapFromItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<const QPointF&>(state, 3)
        ));
    } else if (lua::is_type<QRectF>(state, 3)) {
        // QPolygonF    mapFromItem(const QGraphicsItem * item, const QRectF & rect) const
        lua::push(state, self->mapFromItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<const QRectF&>(state, 3)
        ));
    } else if (lua::is_type<QPolygonF>(state, 3)) {
        // QPolygonF    mapFromItem(const QGraphicsItem * item, const QPolygonF & polygon) const
        lua::push(state, self->mapFromItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<const QPolygonF&>(state, 3)
        ));
    } else if (lua::is_type<QPainterPath>(state, 3)) {
        // QPainterPath     mapFromItem(const QGraphicsItem * item, const QPainterPath & path) const
        lua::push(state, self->mapFromItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<const QPainterPath&>(state, 3)
        ));
    } else if (lua_gettop(state) > 4) {
        // QPolygonF    mapFromItem(const QGraphicsItem * item, qreal x, qreal y, qreal w, qreal h) const
        lua::push(state, self->mapFromItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5),
            lua::get<qreal>(state, 6)
        ));
    } else {
        // QPointF  mapFromItem(const QGraphicsItem * item, qreal x, qreal y) const
        lua::push(state, self->mapFromItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        ));
    }
    return 1;
}

int QGraphicsItem_mapFromParent(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua::is_type<QPointF>(state, 2)) {
        // QPointF  mapFromParent(const QPointF & point) const
        lua::push(state, self->mapFromParent(
            lua::get<const QPointF&>(state, 2)
        ));
    } else if (lua::is_type<QRectF>(state, 2)) {
        // QPolygonF    mapFromParent(const QRectF & rect) const
        lua::push(state, self->mapFromParent(
            lua::get<const QRectF&>(state, 2)
        ));
    } else if (lua::is_type<QPolygonF>(state, 2)) {
        // QPolygonF    mapFromParent(const QPolygonF & polygon) const
        lua::push(state, self->mapFromParent(
            lua::get<const QPolygonF&>(state, 2)
        ));
    } else if (lua::is_type<QPainterPath>(state, 2)) {
        // QPainterPath     mapFromParent(const QPainterPath & path) const
        lua::push(state, self->mapFromParent(
            lua::get<const QPainterPath&>(state, 2)
        ));
    } else if (lua_gettop(state) > 3) {
        // QPolygonF    mapFromParent(qreal x, qreal y, qreal w, qreal h) const
        lua::push(state, self->mapFromParent(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
    } else {
        // QPointF  mapFromParent(qreal x, qreal y) const
        lua::push(state, self->mapFromParent(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        ));
    }
    return 1;
}

int QGraphicsItem_mapFromScene(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua::is_type<QPointF>(state, 2)) {
        // QPointF  mapFromScene(const QPointF & point) const
        lua::push(state, self->mapFromScene(
            lua::get<const QPointF&>(state, 2)
        ));
    } else if (lua::is_type<QRectF>(state, 2)) {
        // QPolygonF    mapFromScene(const QRectF & rect) const
        lua::push(state, self->mapFromScene(
            lua::get<const QRectF&>(state, 2)
        ));
    } else if (lua::is_type<QPolygonF>(state, 2)) {
        // QPolygonF    mapFromScene(const QPolygonF & polygon) const
        lua::push(state, self->mapFromScene(
            lua::get<const QPolygonF&>(state, 2)
        ));
    } else if (lua::is_type<QPainterPath>(state, 2)) {
        // QPainterPath     mapFromScene(const QPainterPath & path) const
        lua::push(state, self->mapFromScene(
            lua::get<const QPainterPath&>(state, 2)
        ));
    } else if (lua_gettop(state) > 3) {
        // QPolygonF    mapFromScene(qreal x, qreal y, qreal w, qreal h) const
        lua::push(state, self->mapFromScene(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
    } else {
        // QPointF  mapFromScene(qreal x, qreal y) const
        lua::push(state, self->mapFromScene(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        ));
    }
    return 1;
}

int QGraphicsItem_mapRectFromItem(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // QRectF   mapRectFromItem(const QGraphicsItem * item, const QRectF & rect) const
    // QRectF   mapRectFromItem(const QGraphicsItem * item, qreal x, qreal y, qreal w, qreal h) const
    if (lua::is_type<QRectF>(state, 3)) {
        lua::push(state, self->mapRectFromItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<const QRectF&>(state, 3)
        ));
    } else {
        lua::push(state, self->mapRectFromItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5),
            lua::get<qreal>(state, 6)
        ));
    }
    return 1;
}

int QGraphicsItem_mapRectFromParent(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // QRectF   mapRectFromParent(const QRectF & rect) const
    // QRectF   mapRectFromParent(qreal x, qreal y, qreal w, qreal h) const
    if (lua::is_type<QRectF>(state, 2)) {
        lua::push(state, self->mapRectFromParent(
            lua::get<const QRectF&>(state, 2)
        ));
    } else {
        lua::push(state, self->mapRectFromParent(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
    }
    return 1;
}

int QGraphicsItem_mapRectFromScene(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // QRectF   mapRectFromScene(const QRectF & rect) const
    // QRectF   mapRectFromScene(qreal x, qreal y, qreal w, qreal h) const
    if (lua::is_type<QRectF>(state, 2)) {
        lua::push(state, self->mapRectFromScene(
            lua::get<const QRectF&>(state, 2)
        ));
    } else {
        lua::push(state, self->mapRectFromScene(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
    }
    return 1;
}

int QGraphicsItem_mapRectToItem(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // QRectF   mapRectToItem(const QGraphicsItem * item, const QRectF & rect) const
    // QRectF   mapRectToItem(const QGraphicsItem * item, qreal x, qreal y, qreal w, qreal h) const
    if (lua::is_type<QRectF>(state, 3)) {
        lua::push(state, self->mapRectToItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<const QRectF&>(state, 3)
        ));
    } else {
        lua::push(state, self->mapRectToItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5),
            lua::get<qreal>(state, 6)
        ));
    }
    return 1;
}

int QGraphicsItem_mapRectToParent(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // QRectF   mapRectToParent(const QRectF & rect) const
    // QRectF   mapRectToParent(qreal x, qreal y, qreal w, qreal h) const
    if (lua::is_type<QRectF>(state, 2)) {
        lua::push(state, self->mapRectToParent(
            lua::get<const QRectF&>(state, 2)
        ));
    } else {
        lua::push(state, self->mapRectToParent(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
    }
    return 1;
}

int QGraphicsItem_mapRectToScene(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // QRectF   mapRectToScene(const QRectF & rect) const
    // QRectF   mapRectToScene(qreal x, qreal y, qreal w, qreal h) const
    if (lua::is_type<QRectF>(state, 2)) {
        lua::push(state, self->mapRectToScene(
            lua::get<const QRectF&>(state, 2)
        ));
    } else {
        lua::push(state, self->mapRectToScene(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
    }
    return 1;
}

int QGraphicsItem_mapToItem(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua::is_type<QPointF>(state, 3)) {
        // QPointF  mapToItem(const QGraphicsItem * item, const QPointF & point) const
        lua::push(state, self->mapToItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<const QPointF&>(state, 3)
        ));
    } else if (lua::is_type<QRectF>(state, 3)) {
        // QPolygonF    mapToItem(const QGraphicsItem * item, const QRectF & rect) const
        lua::push(state, self->mapToItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<const QRectF&>(state, 3)
        ));
    } else if (lua::is_type<QPolygonF>(state, 3)) {
        // QPolygonF    mapToItem(const QGraphicsItem * item, const QPolygonF & polygon) const
        lua::push(state, self->mapToItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<const QPolygonF&>(state, 3)
        ));
    } else if (lua::is_type<QPainterPath>(state, 3)) {
        // QPainterPath     mapToItem(const QGraphicsItem * item, const QPainterPath & path) const
        lua::push(state, self->mapToItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<const QPainterPath&>(state, 3)
        ));
    } else if (lua_gettop(state) > 4) {
        // QPolygonF    mapToItem(const QGraphicsItem * item, qreal x, qreal y, qreal w, qreal h) const
        lua::push(state, self->mapToItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5),
            lua::get<qreal>(state, 6)
        ));
    } else {
        // QPointF  mapToItem(const QGraphicsItem * item, qreal x, qreal y) const
        lua::push(state, self->mapToItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        ));
    }
    return 1;
}

int QGraphicsItem_mapToParent(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua::is_type<QPointF>(state, 2)) {
        // QPointF  mapToParent(const QPointF & point) const
        lua::push(state, self->mapToParent(
            lua::get<const QPointF&>(state, 2)
        ));
    } else if (lua::is_type<QRectF>(state, 2)) {
        // QPolygonF    mapToParent(const QRectF & rect) const
        lua::push(state, self->mapToParent(
            lua::get<const QRectF&>(state, 2)
        ));
    } else if (lua::is_type<QPolygonF>(state, 2)) {
        // QPolygonF    mapToParent(const QPolygonF & polygon) const
        lua::push(state, self->mapToParent(
            lua::get<const QPolygonF&>(state, 2)
        ));
    } else if (lua::is_type<QPainterPath>(state, 2)) {
        // QPainterPath     mapToParent(const QPainterPath & path) const
        lua::push(state, self->mapToParent(
            lua::get<const QPainterPath&>(state, 2)
        ));
    } else if (lua_gettop(state) > 3) {
        // QPolygonF    mapToParent(qreal x, qreal y, qreal w, qreal h) const
        lua::push(state, self->mapToParent(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
    } else {
        // QPointF  mapToParent(qreal x, qreal y) const
        lua::push(state, self->mapToParent(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        ));
    }
    return 1;
}

int QGraphicsItem_mapToScene(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua::is_type<QPointF>(state, 2)) {
        // QPointF  mapToScene(const QPointF & point) const
        lua::push(state, self->mapToScene(
            lua::get<const QPointF&>(state, 2)
        ));
    } else if (lua::is_type<QRectF>(state, 2)) {
        // QPolygonF    mapToScene(const QRectF & rect) const
        lua::push(state, self->mapToScene(
            lua::get<const QRectF&>(state, 2)
        ));
    } else if (lua::is_type<QPolygonF>(state, 2)) {
        // QPolygonF    mapToScene(const QPolygonF & polygon) const
        lua::push(state, self->mapToScene(
            lua::get<const QPolygonF&>(state, 2)
        ));
    } else if (lua::is_type<QPainterPath>(state, 2)) {
        // QPainterPath     mapToScene(const QPainterPath & path) const
        lua::push(state, self->mapToScene(
            lua::get<const QPainterPath&>(state, 2)
        ));
    } else if (lua_gettop(state) > 3) {
        // QPolygonF    mapToScene(qreal x, qreal y, qreal w, qreal h) const
        lua::push(state, self->mapToScene(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
    } else {
        // QPointF  mapToScene(qreal x, qreal y) const
        lua::push(state, self->mapToScene(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        ));
    }
    return 1;
}

int QGraphicsItem_paint(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // virtual void     paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) = 0
    switch (lua_gettop(state)) {
    case 3:
        self->paint(
            lua::get<QPainter*>(state, 2),
            lua::get<QStyleOptionGraphicsItem*>(state, 3)
        );
        break;
    case 4:
    default:
        self->paint(
            lua::get<QPainter*>(state, 2),
            lua::get<QStyleOptionGraphicsItem*>(state, 3),
            lua::get<QWidget*>(state, 4)
        );
        break;
    }

    return 0;
}

int QGraphicsItem_scroll(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // void     scroll(qreal dx, qreal dy, const QRectF & rect = QRectF())
    switch (lua_gettop(state)) {
    case 3:
        self->scroll(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        );
        break;
    case 4:
    default:
        self->scroll(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<const QRectF&>(state, 4)
        );
        break;
    }
    return 0;
}

int QGraphicsItem_setCacheMode(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // void     setCacheMode(CacheMode mode, const QSize & logicalCacheSize = QSize())
    switch (lua_gettop(state)) {
    case 2:
        self->setCacheMode(
            lua::get<QGraphicsItem::CacheMode>(state, 2)
        );
        break;
    case 3:
    default:
        self->setCacheMode(
            lua::get<QGraphicsItem::CacheMode>(state, 2),
            lua::get<const QSize&>(state, 3)
        );
        break;
    }
    return 0;
}

int QGraphicsItem_setFlag(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // void     setFlag(GraphicsItemFlag flag, bool enabled = true)
    switch (lua_gettop(state)) {
    case 2:
        self->setFlag(
            lua::get<QGraphicsItem::GraphicsItemFlag>(state, 2)
        );
        break;
    case 3:
    default:
        self->setFlag(
            lua::get<QGraphicsItem::GraphicsItemFlag>(state, 2),
            lua::get<bool>(state, 3)
        );
        break;
    }
    return 0;
}

int QGraphicsItem_setFocus(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // void     setFocus(Qt::FocusReason focusReason = Qt::OtherFocusReason)
    switch (lua_gettop(state)) {
    case 1:
        self->setFocus();
        break;
    case 2:
    default:
        self->setFocus(
            lua::get<Qt::FocusReason>(state, 2)
        );
        break;
    }
    return 0;
}

int QGraphicsItem_setPos(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua_gettop(state) == 2) {
        self->setPos(
            lua::get<QPointF>(state, 2)
        );
    } else {
        self->setPos(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        );
    }
    return 0;
}

int QGraphicsItem_setTransform(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    // void     setTransform(const QTransform & matrix, bool combine = false)
    switch (lua_gettop(state)) {
    case 2:
        self->setTransform(
            lua::get<const QTransform&>(state, 2)
        );
        break;
    case 3:
    default:
        self->setTransform(
            lua::get<const QTransform&>(state, 2),
            lua::get<bool>(state, 3)
        );
        break;
    }
    return 0;
}

int QGraphicsItem_setTransformOriginPoint(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua::is_type<QPointF>(state, 2)) {
        // void setTransformOriginPoint(const QPointF & origin)
        self->setTransformOriginPoint(
            lua::get<const QPointF&>(state, 2)
        );
    } else {
        // void setTransformOriginPoint(qreal x, qreal y)
        self->setTransformOriginPoint(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        );
    }
    return 0;
}

int QGraphicsItem_toGraphicsObject(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    lua::push(state, self->toGraphicsObject());
    return 1;
}

int QGraphicsItem_update(lua_State* const state)
{
    auto self = lua::get<QGraphicsItem*>(state, 1);

    if (lua_gettop(state) > 2) {
        // void   update(qreal x, qreal y, qreal width, qreal height)
        self->update(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        );
    } else if (lua_gettop(state) == 1) {
        // void   update()
        self->update();
    } else {
        // void   update(const QRectF & rect = QRectF())
        self->update(lua::get<const QRectF&>(state, 2));
    }
    return 0;
}

void lua::QGraphicsItem_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["acceptDrops"] = &QGraphicsItem::acceptDrops;
    mt["acceptHoverEvents"] = &QGraphicsItem::acceptHoverEvents;
    mt["acceptTouchEvents"] = &QGraphicsItem::acceptTouchEvents;
    mt["acceptedMouseButtons"] = &QGraphicsItem::acceptedMouseButtons;
    mt["advance"] = &QGraphicsItem::advance;
    mt["boundingRect"] = &QGraphicsItem::boundingRect;
    mt["boundingRegion"] = &QGraphicsItem::boundingRegion;
    mt["boundingRegionGranularity"] = &QGraphicsItem::boundingRegionGranularity;
    mt["cacheMode"] = &QGraphicsItem::cacheMode;
    mt["childItems"] = &QGraphicsItem::childItems;
    mt["childrenBoundingRect"] = &QGraphicsItem::childrenBoundingRect;
    mt["clearFocus"] = &QGraphicsItem::clearFocus;
    mt["clipPath"] = &QGraphicsItem::clipPath;
    mt["collidesWithItem"] = QGraphicsItem_collidesWithItem;
    mt["collidesWithPath"] = QGraphicsItem_collidesWithPath;
    mt["collidingItems"] = QGraphicsItem_collidingItems;
    mt["commonAncestorItem"] = &QGraphicsItem::commonAncestorItem;
    mt["contains"] = &QGraphicsItem::contains;
    mt["cursor"] = &QGraphicsItem::cursor;
    mt["data"] = &QGraphicsItem::data;
    mt["deviceTransform"] = &QGraphicsItem::deviceTransform;
    mt["effectiveOpacity"] = &QGraphicsItem::effectiveOpacity;
    mt["ensureVisible"] = QGraphicsItem_ensureVisible;
    mt["filtersChildEvents"] = &QGraphicsItem::filtersChildEvents;
    mt["flags"] = &QGraphicsItem::flags;
    mt["focusItem"] = &QGraphicsItem::focusItem;
    mt["focusProxy"] = &QGraphicsItem::focusProxy;
    mt["grabKeyboard"] = &QGraphicsItem::grabKeyboard;
    mt["grabMouse"] = &QGraphicsItem::grabMouse;
    mt["graphicsEffect"] = &QGraphicsItem::graphicsEffect;
    mt["group"] = &QGraphicsItem::group;
    mt["hasCursor"] = &QGraphicsItem::hasCursor;
    mt["hasFocus"] = &QGraphicsItem::hasFocus;
    mt["hide"] = &QGraphicsItem::hide;
    mt["inputMethodHints"] = &QGraphicsItem::inputMethodHints;
    mt["installSceneEventFilter"] = &QGraphicsItem::installSceneEventFilter;
    mt["isActive"] = &QGraphicsItem::isActive;
    mt["isAncestorOf"] = &QGraphicsItem::isAncestorOf;
    // TODO bool    isBlockedByModalPanel(QGraphicsItem ** blockingPanel = 0) const
    mt["isClipped"] = &QGraphicsItem::isClipped;
    mt["isEnabled"] = &QGraphicsItem::isEnabled;
    mt["isObscured"] = QGraphicsItem_isObscured;
    mt["isObscuredBy"] = &QGraphicsItem::isObscuredBy;
    mt["isPanel"] = &QGraphicsItem::isPanel;
    mt["isSelected"] = &QGraphicsItem::isSelected;
    mt["isUnderMouse"] = &QGraphicsItem::isUnderMouse;
    mt["isVisible"] = &QGraphicsItem::isVisible;
    mt["isVisibleTo"] = &QGraphicsItem::isVisibleTo;
    mt["isWidget"] = &QGraphicsItem::isWidget;
    mt["isWindow"] = &QGraphicsItem::isWindow;
    mt["itemTransform"] = QGraphicsItem_itemTransform;
    mt["mapFromItem"] = QGraphicsItem_mapFromItem;
    mt["mapFromParent"] = QGraphicsItem_mapFromParent;
    mt["mapFromScene"] = QGraphicsItem_mapFromScene;
    mt["mapRectFromItem"] = QGraphicsItem_mapRectFromItem;
    mt["mapRectFromParent"] = QGraphicsItem_mapRectFromParent;
    mt["mapRectFromScene"] = QGraphicsItem_mapRectFromScene;
    mt["mapRectToItem"] = QGraphicsItem_mapRectToItem;
    mt["mapRectToParent"] = QGraphicsItem_mapRectToParent;
    mt["mapRectToScene"] = QGraphicsItem_mapRectToScene;
    mt["mapToItem"] = QGraphicsItem_mapToItem;
    mt["mapToParent"] = QGraphicsItem_mapToParent;
    mt["mapToScene"] = QGraphicsItem_mapToScene;
    mt["moveBy"] = &QGraphicsItem::moveBy;
    mt["opacity"] = &QGraphicsItem::opacity;
    mt["opaqueArea"] = &QGraphicsItem::opaqueArea;
    mt["paint"] = QGraphicsItem_paint;
    mt["panel"] = &QGraphicsItem::panel;
    mt["panelModality"] = &QGraphicsItem::panelModality;
    mt["parentItem"] = &QGraphicsItem::parentItem;
    mt["parentObject"] = &QGraphicsItem::parentObject;
    mt["parentWidget"] = &QGraphicsItem::parentWidget;
    mt["pos"] = &QGraphicsItem::pos;
    mt["removeSceneEventFilter"] = &QGraphicsItem::removeSceneEventFilter;
    mt["resetTransform"] = &QGraphicsItem::resetTransform;
    mt["rotation"] = &QGraphicsItem::rotation;
    mt["scale"] = &QGraphicsItem::scale;
    mt["scene"] = &QGraphicsItem::scene;
    mt["sceneBoundingRect"] = &QGraphicsItem::sceneBoundingRect;
    mt["scenePos"] = &QGraphicsItem::scenePos;
    mt["sceneTransform"] = &QGraphicsItem::sceneTransform;
    mt["scroll"] = QGraphicsItem_scroll;
    mt["setAcceptDrops"] = &QGraphicsItem::setAcceptDrops;
    mt["setAcceptHoverEvents"] = &QGraphicsItem::setAcceptHoverEvents;
    mt["setAcceptTouchEvents"] = &QGraphicsItem::setAcceptTouchEvents;
    mt["setAcceptedMouseButtons"] = &QGraphicsItem::setAcceptedMouseButtons;
    mt["setActive"] = &QGraphicsItem::setActive;
    mt["setBoundingRegionGranularity"] = &QGraphicsItem::setBoundingRegionGranularity;
    mt["setCacheMode"] = QGraphicsItem_setCacheMode;
    mt["setCursor"] = &QGraphicsItem::setCursor;
    mt["setData"] = &QGraphicsItem::setData;
    mt["setEnabled"] = &QGraphicsItem::setEnabled;
    mt["setFiltersChildEvents"] = &QGraphicsItem::setFiltersChildEvents;
    mt["setFlag"] = QGraphicsItem_setFlag;
    mt["setFlags"] = &QGraphicsItem::setFlags;
    mt["setFocus"] = QGraphicsItem_setFocus;
    mt["setFocusProxy"] = &QGraphicsItem::setFocusProxy;
    mt["setGraphicsEffect"] = &QGraphicsItem::setGraphicsEffect;
    mt["setGroup"] = &QGraphicsItem::setGroup;
    mt["setInputMethodHints"] = &QGraphicsItem::setInputMethodHints;
    mt["setOpacity"] = &QGraphicsItem::setOpacity;
    mt["setPanelModality"] = &QGraphicsItem::setPanelModality;
    mt["setParentItem"] = &QGraphicsItem::setParentItem;
    mt["setPos"] = QGraphicsItem_setPos;
    mt["setRotation"] = &QGraphicsItem::setRotation;
    mt["setScale"] = &QGraphicsItem::setScale;
    mt["setSelected"] = &QGraphicsItem::setSelected;
    mt["setToolTip"] = &QGraphicsItem::setToolTip;
    mt["setTransform"] = QGraphicsItem_setTransform;
    mt["setTransformOriginPoint"] = QGraphicsItem_setTransformOriginPoint;
    mt["setTransformations"] = &QGraphicsItem::setTransformations;
    mt["setVisible"] = &QGraphicsItem::setVisible;
    mt["setX"] = &QGraphicsItem::setX;
    mt["setY"] = &QGraphicsItem::setY;
    mt["setZValue"] = &QGraphicsItem::setZValue;
    mt["shape"] = &QGraphicsItem::shape;
    mt["show"] = &QGraphicsItem::show;
    mt["stackBefore"] = &QGraphicsItem::stackBefore;
    mt["toGraphicsObject"] = QGraphicsItem_toGraphicsObject;
    mt["toolTip"] = &QGraphicsItem::toolTip;
    mt["topLevelItem"] = &QGraphicsItem::topLevelItem;
    mt["topLevelWidget"] = &QGraphicsItem::topLevelWidget;
    mt["transform"] = &QGraphicsItem::transform;
    mt["transformOriginPoint"] = &QGraphicsItem::transformOriginPoint;
    mt["transformations"] = &QGraphicsItem::transformations;
    mt["type"] = &QGraphicsItem::type;
    mt["ungrabKeyboard"] = &QGraphicsItem::ungrabKeyboard;
    mt["ungrabMouse"] = &QGraphicsItem::ungrabMouse;
    mt["unsetCursor"] = &QGraphicsItem::unsetCursor;
    mt["update"] = QGraphicsItem_update;
    mt["window"] = &QGraphicsItem::window;
    mt["x"] = &QGraphicsItem::x;
    mt["y"] = &QGraphicsItem::y;
    mt["zValue"] = &QGraphicsItem::zValue;
}

int luaopen_Qt5Widgets_QGraphicsItem(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsItem"] = lua::value::table;
    auto t = env["QGraphicsItem"];

    // enum QGraphicsItem::CacheMode
    t["NoCache"] = QGraphicsItem::NoCache;
    t["ItemCoordinateCache"] = QGraphicsItem::ItemCoordinateCache;
    t["DeviceCoordinateCache"] = QGraphicsItem::DeviceCoordinateCache;

    // enum QGraphicsItem::GraphicsItemChange
    t["ItemEnabledChange"] = QGraphicsItem::ItemEnabledChange;
    t["ItemEnabledHasChanged"] = QGraphicsItem::ItemEnabledHasChanged;
    t["ItemMatrixChange"] = QGraphicsItem::ItemMatrixChange;
    t["ItemPositionChange"] = QGraphicsItem::ItemPositionChange;
    t["ItemPositionHasChanged"] = QGraphicsItem::ItemPositionHasChanged;
    t["ItemTransformChange"] = QGraphicsItem::ItemTransformChange;
    t["ItemTransformHasChanged"] = QGraphicsItem::ItemTransformHasChanged;
    t["ItemRotationChange"] = QGraphicsItem::ItemRotationChange;
    t["ItemRotationHasChanged"] = QGraphicsItem::ItemRotationHasChanged;
    t["ItemScaleChange"] = QGraphicsItem::ItemScaleChange;
    t["ItemScaleHasChanged"] = QGraphicsItem::ItemScaleHasChanged;
    t["ItemTransformOriginPointChange"] = QGraphicsItem::ItemTransformOriginPointChange;
    t["ItemTransformOriginPointHasChanged"] = QGraphicsItem::ItemTransformOriginPointHasChanged;
    t["ItemSelectedChange"] = QGraphicsItem::ItemSelectedChange;
    t["ItemSelectedHasChanged"] = QGraphicsItem::ItemSelectedHasChanged;
    t["ItemVisibleChange"] = QGraphicsItem::ItemVisibleChange;
    t["ItemVisibleHasChanged"] = QGraphicsItem::ItemVisibleHasChanged;
    t["ItemParentChange"] = QGraphicsItem::ItemParentChange;
    t["ItemParentHasChanged"] = QGraphicsItem::ItemParentHasChanged;
    t["ItemChildAddedChange"] = QGraphicsItem::ItemChildAddedChange;
    t["ItemChildRemovedChange"] = QGraphicsItem::ItemChildRemovedChange;
    t["ItemSceneChange"] = QGraphicsItem::ItemSceneChange;
    t["ItemSceneHasChanged"] = QGraphicsItem::ItemSceneHasChanged;
    t["ItemCursorChange"] = QGraphicsItem::ItemCursorChange;
    t["ItemCursorHasChanged"] = QGraphicsItem::ItemCursorHasChanged;
    t["ItemToolTipChange"] = QGraphicsItem::ItemToolTipChange;
    t["ItemToolTipHasChanged"] = QGraphicsItem::ItemToolTipHasChanged;
    t["ItemFlagsChange"] = QGraphicsItem::ItemFlagsChange;
    t["ItemFlagsHaveChanged"] = QGraphicsItem::ItemFlagsHaveChanged;
    t["ItemZValueChange"] = QGraphicsItem::ItemZValueChange;
    t["ItemZValueHasChanged"] = QGraphicsItem::ItemZValueHasChanged;
    t["ItemOpacityChange"] = QGraphicsItem::ItemOpacityChange;
    t["ItemOpacityHasChanged"] = QGraphicsItem::ItemOpacityHasChanged;
    t["ItemScenePositionHasChanged"] = QGraphicsItem::ItemScenePositionHasChanged;

    // enum QGraphicsItem::GraphicsItemFlag
    t["ItemIsMovable"] = QGraphicsItem::ItemIsMovable;
    t["ItemIsSelectable"] = QGraphicsItem::ItemIsSelectable;
    t["ItemIsFocusable"] = QGraphicsItem::ItemIsFocusable;
    t["ItemClipsToShape"] = QGraphicsItem::ItemClipsToShape;
    t["ItemClipsChildrenToShape"] = QGraphicsItem::ItemClipsChildrenToShape;
    t["ItemIgnoresTransformations"] = QGraphicsItem::ItemIgnoresTransformations;
    t["ItemIgnoresParentOpacity"] = QGraphicsItem::ItemIgnoresParentOpacity;
    t["ItemDoesntPropagateOpacityToChildren"] = QGraphicsItem::ItemDoesntPropagateOpacityToChildren;
    t["ItemStacksBehindParent"] = QGraphicsItem::ItemStacksBehindParent;
    t["ItemUsesExtendedStyleOption"] = QGraphicsItem::ItemUsesExtendedStyleOption;
    t["ItemHasNoContents"] = QGraphicsItem::ItemHasNoContents;
    t["ItemSendsGeometryChanges"] = QGraphicsItem::ItemSendsGeometryChanges;
    t["ItemAcceptsInputMethod"] = QGraphicsItem::ItemAcceptsInputMethod;
    t["ItemNegativeZStacksBehindParent"] = QGraphicsItem::ItemNegativeZStacksBehindParent;
    t["ItemIsPanel"] = QGraphicsItem::ItemIsPanel;
    t["ItemSendsScenePositionChanges"] = QGraphicsItem::ItemSendsScenePositionChanges;

    // enum QGraphicsItem::PanelModality
    t["NonModal"] = QGraphicsItem::NonModal;
    t["PanelModal"] = QGraphicsItem::PanelModal;
    t["SceneModal"] = QGraphicsItem::SceneModal;

    return 0;
}

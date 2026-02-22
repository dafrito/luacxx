#include "QGraphicsScene.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QGraphicsScene>

#include "QGraphicsWidget.hpp"
#include "../Qt5Gui/QBrush.hpp"
#include "../Qt5Gui/QFont.hpp"
#include "QGraphicsItem.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "QGraphicsItemGroup.hpp"
#include "../Qt5Gui/QPalette.hpp"
#include "../Qt5Gui/QTransform.hpp"
#include "../Qt5Gui/QPainter.hpp"
#include "../Qt5Gui/QPolygonF.hpp"
#include "../Qt5Gui/QPen.hpp"
#include "../Qt5Core/QLineF.hpp"
#include "QStyle.hpp"
#include "../Qt5Core/QEvent.hpp"
#include "../Qt5Gui/QPainterPath.hpp"
#include "QGraphicsView.hpp"
#include "../Qt5Gui/QPixmap.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/Qt.hpp"
#include "QGraphicsLineItem.hpp"
#include "QGraphicsEllipseItem.hpp"
#include "QGraphicsPathItem.hpp"
#include "QGraphicsPixmapItem.hpp"
#include "QGraphicsPolygonItem.hpp"
#include "QGraphicsRectItem.hpp"
#include "QGraphicsSimpleTextItem.hpp"
#include "QGraphicsTextItem.hpp"
#include "QGraphicsProxyWidget.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/Qt.hpp"
#include "QWidget.hpp"

// https://qt-project.org/doc/qt-5/qgraphicsscene.html

int QGraphicsScene_addEllipse(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    if (lua::is_type<QRectF>(state, 2)) {
        // QGraphicsEllipseItem *  addEllipse(const QRectF & rect, const QPen & pen = QPen(), const QBrush & brush = QBrush())
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->addEllipse(
                lua::get<const QRectF&>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->addEllipse(
                lua::get<const QRectF&>(state, 2),
                lua::get<const QPen&>(state, 3)
            ));
            break;
        case 4:
        default:
            lua::push(state, self->addEllipse(
                lua::get<const QRectF&>(state, 2),
                lua::get<const QPen&>(state, 3),
                lua::get<const QBrush&>(state, 4)
            ));
            break;
        }
    } else {
        // QGraphicsEllipseItem *  addEllipse(qreal x, qreal y, qreal w, qreal h, const QPen & pen = QPen(), const QBrush & brush = QBrush())
        switch (lua_gettop(state)) {
        case 5:
            lua::push(state, self->addEllipse(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5)
            ));
            break;
        case 6:
            lua::push(state, self->addEllipse(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5),
                lua::get<const QPen&>(state, 6)
            ));
            break;
        case 7:
        default:
            lua::push(state, self->addEllipse(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5),
                lua::get<const QPen&>(state, 6),
                lua::get<const QBrush&>(state, 7)
            ));
            break;
        }
    }

    return 1;
}

int QGraphicsScene_addLine(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    switch (lua_gettop(state)) {
    case 2:
        // QGraphicsLineItem *  addLine(const QLineF & line)
        lua::push(state, self->addLine(
            lua::get<const QLineF&>(state, 2)
        ));
        break;
    case 3:
        // QGraphicsLineItem *  addLine(const QLineF & line, const QPen & pen = QPen())
        lua::push(state, self->addLine(
            lua::get<const QLineF&>(state, 2),
            lua::get<const QPen&>(state, 3)
        ));
        break;
    case 5:
        // QGraphicsLineItem *  addLine(qreal x1, qreal y1, qreal x2, qreal y2)
        lua::push(state, self->addLine(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
        break;
    case 6:
    default:
        // QGraphicsLineItem *  addLine(qreal x1, qreal y1, qreal x2, qreal y2, const QPen & pen = QPen())
        lua::push(state, self->addLine(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5),
            lua::get<const QPen&>(state, 6)
        ));
        break;
    }

    return 1;
}

int QGraphicsScene_addPath(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    // QGraphicsPathItem *  addPath(const QPainterPath & path, const QPen & pen = QPen(), const QBrush & brush = QBrush())
    switch (lua_gettop(state)) {
    case 2:
        lua::push(state, self->addPath(
            lua::get<const QPainterPath&>(state, 2)
        ));
        break;
    case 3:
        lua::push(state, self->addPath(
            lua::get<const QPainterPath&>(state, 2),
            lua::get<const QPen&>(state, 3)
        ));
        break;
    case 4:
    default:
        lua::push(state, self->addPath(
            lua::get<const QPainterPath&>(state, 2),
            lua::get<const QPen&>(state, 3),
            lua::get<const QBrush&>(state, 4)
        ));
        break;
    }

    return 1;
}

int QGraphicsScene_addPolygon(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    // QGraphicsPolygonItem *  addPolygon(const QPolygonF & polygon, const QPen & pen = QPen(), const QBrush & brush = QBrush())
    switch (lua_gettop(state)) {
    case 2:
        lua::push(state, self->addPolygon(
            lua::get<const QPolygonF&>(state, 2)
        ));
        break;
    case 3:
        lua::push(state, self->addPolygon(
            lua::get<const QPolygonF&>(state, 2),
            lua::get<const QPen&>(state, 3)
        ));
        break;
    case 4:
    default:
        lua::push(state, self->addPolygon(
            lua::get<const QPolygonF&>(state, 2),
            lua::get<const QPen&>(state, 3),
            lua::get<const QBrush&>(state, 4)
        ));
        break;
    }

    return 1;
}

int QGraphicsScene_addRect(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    // QGraphicsRectItem *  addRect(const QRectF & rect, const QPen & pen = QPen(), const QBrush & brush = QBrush())
    // QGraphicsRectItem *  addRect(qreal x, qreal y, qreal w, qreal h, const QPen & pen = QPen(), const QBrush & brush = QBrush())
    if (lua::is_type<QRectF>(state, 2)) {
        // QGraphicsEllipseItem *  addRect(const QRectF & rect, const QPen & pen = QPen(), const QBrush & brush = QBrush())
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->addRect(
                lua::get<const QRectF&>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->addRect(
                lua::get<const QRectF&>(state, 2),
                lua::get<const QPen&>(state, 3)
            ));
            break;
        case 4:
        default:
            lua::push(state, self->addRect(
                lua::get<const QRectF&>(state, 2),
                lua::get<const QPen&>(state, 3),
                lua::get<const QBrush&>(state, 4)
            ));
            break;
        }
    } else {
        // QGraphicsEllipseItem *  addRect(qreal x, qreal y, qreal w, qreal h, const QPen & pen = QPen(), const QBrush & brush = QBrush())
        switch (lua_gettop(state)) {
        case 5:
            lua::push(state, self->addRect(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5)
            ));
            break;
        case 6:
            lua::push(state, self->addRect(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5),
                lua::get<const QPen&>(state, 6)
            ));
            break;
        case 7:
        default:
            lua::push(state, self->addRect(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5),
                lua::get<const QPen&>(state, 6),
                lua::get<const QBrush&>(state, 7)
            ));
            break;
        }
    }

    return 1;
}

int QGraphicsScene_addSimpleText(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    // QGraphicsSimpleTextItem *   addSimpleText(const QString & text, const QFont & font = QFont())
    if (lua_gettop(state) == 2) {
        lua::push(state, self->addSimpleText(
            lua::get<QString>(state, 2)
        ));
    } else {
        lua::push(state, self->addSimpleText(
            lua::get<QString>(state, 2),
            lua::get<const QFont&>(state, 3)
        ));
    }

    return 1;
}

int QGraphicsScene_addText(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    // QGraphicsTextItem *  addText(const QString & text, const QFont & font = QFont())
    if (lua_gettop(state) == 2) {
        lua::push(state, self->addText(
            lua::get<QString>(state, 2)
        ));
    } else {
        lua::push(state, self->addText(
            lua::get<QString>(state, 2),
            lua::get<const QFont&>(state, 3)
        ));
    }

    return 1;
}

int QGraphicsScene_addWidget(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    // QGraphicsProxyWidget *  addWidget(QWidget * widget, Qt::WindowFlags wFlags = 0)
    if (lua_gettop(state) == 2) {
        lua::push(state, self->addWidget(
            lua::get<QWidget*>(state, 2)
        ));
    } else {
        lua::push(state, self->addWidget(
            lua::get<QWidget*>(state, 2),
            lua::get<Qt::WindowFlags>(state, 3)
        ));
    }

    return 1;
}

int QGraphicsScene_collidingItems(lua_State* const state)
{
    // QList<QGraphicsItem *>   collidingItems(const QGraphicsItem * item, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const
    auto self = lua::get<QGraphicsScene*>(state, 1);

    if (lua_gettop(state) == 2) {
        lua::push(state, self->collidingItems(
            lua::get<const QGraphicsItem*>(state, 2)
        ));
    } else {
        lua::push(state, self->collidingItems(
            lua::get<const QGraphicsItem*>(state, 2),
            lua::get<Qt::ItemSelectionMode>(state, 3)
        ));

    }

    return 1;
}

int QGraphicsScene_invalidate(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    // void    invalidate(qreal x, qreal y, qreal w, qreal h, SceneLayers layers = AllLayers)
    if (lua_gettop(state) == 5) {
        self->invalidate(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        );
    } else {
        self->invalidate(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5),
            lua::get<QGraphicsScene::SceneLayers>(state, 6)
        );
    }

    return 0;
}

int QGraphicsScene_itemAt(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    if (lua::is_type<QPointF>(state, 2)) {
        //  QGraphicsItem *     itemAt(const QPointF & position, const QTransform & deviceTransform) const
        lua::push(state, self->itemAt(
            lua::get<const QPointF&>(state, 2),
            lua::get<const QTransform&>(state, 3)
        ));
    } else {
        //  QGraphicsItem *     itemAt(qreal x, qreal y, const QTransform & deviceTransform) const
        lua::push(state, self->itemAt(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<const QTransform&>(state, 4)
        ));
    }

    return 1;
}

int QGraphicsScene_items(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    if (lua_gettop(state) == 1) {
        lua::push(state, self->items());
    } else if (lua::is_type<QRectF>(state, 2)) {
        // QList<QGraphicsItem *>   items(const QRectF & rect, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder, const QTransform & deviceTransform = QTransform()) const
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->items(
                lua::get<const QRectF&>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->items(
                lua::get<const QRectF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3)
            ));
            break;
        case 4:
            lua::push(state, self->items(
                lua::get<const QRectF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4)
            ));
            break;
        case 5:
        default:
            lua::push(state, self->items(
                lua::get<const QRectF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4),
                lua::get<const QTransform&>(state, 5)
            ));
            break;
        }
    } else if (lua::is_type<QPointF>(state, 2)) {
        // QList<QGraphicsItem *>   items(const QPointF & pos, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder, const QTransform & deviceTransform = QTransform()) const
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->items(
                lua::get<const QPointF&>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->items(
                lua::get<const QPointF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3)
            ));
            break;
        case 4:
            lua::push(state, self->items(
                lua::get<const QPointF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4)
            ));
            break;
        case 5:
        default:
            lua::push(state, self->items(
                lua::get<const QPointF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4),
                lua::get<const QTransform&>(state, 5)
            ));
            break;
        }
    } else if (lua::is_type<QPainterPath>(state, 2)) {
        // QList<QGraphicsItem *>   items(const QPainterPath & path, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder, const QTransform & deviceTransform = QTransform()) const
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->items(
                lua::get<const QPainterPath&>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->items(
                lua::get<const QPainterPath&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3)
            ));
            break;
        case 4:
            lua::push(state, self->items(
                lua::get<const QPainterPath&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4)
            ));
            break;
        case 5:
        default:
            lua::push(state, self->items(
                lua::get<const QPainterPath&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4),
                lua::get<const QTransform&>(state, 5)
            ));
            break;
        }
    } else if (lua::is_type<QPolygonF>(state, 2)) {
        // QList<QGraphicsItem *>   items(const QPolygonF & polygon, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder, const QTransform & deviceTransform = QTransform()) const
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->items(
                lua::get<const QPolygonF&>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->items(
                lua::get<const QPolygonF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3)
            ));
            break;
        case 4:
            lua::push(state, self->items(
                lua::get<const QPolygonF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4)
            ));
            break;
        case 5:
        default:
            lua::push(state, self->items(
                lua::get<const QPolygonF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4),
                lua::get<const QTransform&>(state, 5)
            ));
            break;
        }
    } else if (lua::is_type<Qt::SortOrder>(state, 2)) {
        // QList<QGraphicsItem *>   items(Qt::SortOrder order = Qt::DescendingOrder) const
        lua::push(state, self->items(lua::get<Qt::SortOrder>(state, 2)));
    } else if (lua::is_type<QPainterPath>(state, 2)) {
        // QList<QGraphicsItem *>   items(const QPainterPath & path, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder, const QTransform & deviceTransform = QTransform()) const
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->items(
                lua::get<const QPainterPath&>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->items(
                lua::get<const QPainterPath&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3)
            ));
            break;
        case 4:
            lua::push(state, self->items(
                lua::get<const QPainterPath&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4)
            ));
            break;
        case 5:
        default:
            lua::push(state, self->items(
                lua::get<const QPainterPath&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4),
                lua::get<const QTransform&>(state, 5)
            ));
            break;
        }
    } else if (lua::is_type<QPolygonF>(state, 2)) {
        // QList<QGraphicsItem *>   items(const QPolygonF & polygon, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, Qt::SortOrder order = Qt::DescendingOrder, const QTransform & deviceTransform = QTransform()) const
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->items(
                lua::get<const QPolygonF&>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->items(
                lua::get<const QPolygonF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3)
            ));
            break;
        case 4:
            lua::push(state, self->items(
                lua::get<const QPolygonF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4)
            ));
            break;
        case 5:
        default:
            lua::push(state, self->items(
                lua::get<const QPolygonF&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<Qt::SortOrder>(state, 4),
                lua::get<const QTransform&>(state, 5)
            ));
            break;
        }
    } else {
        // QList<QGraphicsItem *>   items(qreal x, qreal y, qreal w, qreal h, Qt::ItemSelectionMode mode, Qt::SortOrder order, const QTransform & deviceTransform = QTransform()) const
        switch (lua_gettop(state)) {
        case 7:
            lua::push(state, self->items(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5),
                lua::get<Qt::ItemSelectionMode>(state, 6),
                lua::get<Qt::SortOrder>(state, 7)
            ));
            break;
        case 8:
        default:
            lua::push(state, self->items(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5),
                lua::get<Qt::ItemSelectionMode>(state, 6),
                lua::get<Qt::SortOrder>(state, 7),
                lua::get<const QTransform&>(state, 8)
            ));
            break;
        }
    }

    return 1;
}

int QGraphicsScene_render(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    // void render(QPainter * painter, const QRectF & target = QRectF(), const QRectF & source = QRectF(), Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio)
    switch (lua_gettop(state)) {
    case 2:
        self->render(
            lua::get<QPainter*>(state, 2)
        );
        break;
    case 3:
        self->render(
            lua::get<QPainter*>(state, 2),
            lua::get<const QRectF&>(state, 3)
        );
        break;
    case 4:
        self->render(
            lua::get<QPainter*>(state, 2),
            lua::get<const QRectF&>(state, 3),
            lua::get<const QRectF&>(state, 4)
        );
        break;
    case 5:
    default:
        self->render(
            lua::get<QPainter*>(state, 2),
            lua::get<const QRectF&>(state, 3),
            lua::get<const QRectF&>(state, 4),
            lua::get<Qt::AspectRatioMode>(state, 5)
        );
        break;
    }

    return 0;
}

int QGraphicsScene_setFocus(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    // void   setFocus(Qt::FocusReason focusReason = Qt::OtherFocusReason)
    if (lua_gettop(state) == 1) {
        self->setFocus();
    } else {
        self->setFocus(
            lua::get<Qt::FocusReason>(state, 2)
        );
    }

    return 0;
}

int QGraphicsScene_setFocusItem(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    // void   setFocusItem(QGraphicsItem * item, Qt::FocusReason focusReason = Qt::OtherFocusReason)
    if (lua_gettop(state) == 2) {
        self->setFocusItem(
            lua::get<QGraphicsItem*>(state, 2)
        );
    } else {
        self->setFocusItem(
            lua::get<QGraphicsItem*>(state, 2),
            lua::get<Qt::FocusReason>(state, 3)
        );
    }

    return 0;
}

int QGraphicsScene_setSceneRect(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);
    if (lua_gettop(state) > 2) {
        // void     setSceneRect(qreal x, qreal y, qreal w, qreal h)
        self->setSceneRect(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        );
    } else {
        // void     setSceneRect(const QRectF & rect)
        self->setSceneRect(
            lua::get<const QRectF&>(state, 2)
        );
    }

    return 0;
}

int QGraphicsScene_setSelectionArea(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);

    if (lua_gettop(state) == 2) {
        self->setSelectionArea(
            lua::get<const QPainterPath&>(state, 2)
        );
    } else {
        if (lua::is_type<QTransform>(state, 3)) {
            // void    setSelectionArea(const QPainterPath & path, const QTransform & deviceTransform)
            self->setSelectionArea(
                lua::get<const QPainterPath&>(state, 2),
                lua::get<const QTransform&>(state, 3)
            );
        } else if (lua_gettop(state) == 3) {
            self->setSelectionArea(
                lua::get<const QPainterPath&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3)
            );
        } else {
            // void    setSelectionArea(const QPainterPath & path, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape, const QTransform & deviceTransform = QTransform())
            self->setSelectionArea(
                lua::get<const QPainterPath&>(state, 2),
                lua::get<Qt::ItemSelectionMode>(state, 3),
                lua::get<const QTransform&>(state, 4)
            );
        }
    }

    return 0;
}

int QGraphicsScene_update(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);
    if (lua::size(state) == 2) {
        self->update(lua::get<const QRectF&>(state, 2));
    } else if (lua::size(state) == 1) {
        self->update();
    } else {
        self->update(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        );
    }
    return 0;
}

int QGraphicsScene_addItem(lua_State* const state)
{
    auto self = lua::get<QGraphicsScene*>(state, 1);
    self->addItem(lua::get<QGraphicsItem*>(state, 2));
    return 0;
}

void lua::QGraphicsScene_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["activePanel"] = &QGraphicsScene::activePanel;
    mt["activeWindow"] = &QGraphicsScene::activeWindow;
    mt["addEllipse"] = QGraphicsScene_addEllipse;
    mt["addItem"] = QGraphicsScene_addItem;
    mt["addLine"] = QGraphicsScene_addLine;
    mt["addPath"] = QGraphicsScene_addPath;
    mt["addPixmap"] = &QGraphicsScene::addPixmap;
    mt["addPolygon"] = QGraphicsScene_addPolygon;
    mt["addRect"] = QGraphicsScene_addRect;
    mt["addSimpleText"] = QGraphicsScene_addSimpleText;
    mt["addText"] = QGraphicsScene_addText;
    mt["addWidget"] = QGraphicsScene_addWidget;
    mt["backgroundBrush"] = &QGraphicsScene::backgroundBrush;
    mt["bspTreeDepth"] = &QGraphicsScene::bspTreeDepth;
    mt["clearFocus"] = &QGraphicsScene::clearFocus;
    mt["collidingItems"] = QGraphicsScene_collidingItems;
    mt["createItemGroup"] = &QGraphicsScene::createItemGroup;
    mt["destroyItemGroup"] = &QGraphicsScene::destroyItemGroup;
    mt["focusItem"] = &QGraphicsScene::focusItem;
    mt["font"] = &QGraphicsScene::font;
    mt["foregroundBrush"] = &QGraphicsScene::foregroundBrush;
    mt["hasFocus"] = &QGraphicsScene::hasFocus;
    mt["height"] = &QGraphicsScene::height;
    mt["inputMethodQuery"] = &QGraphicsScene::inputMethodQuery;
    mt["invalidate"] = QGraphicsScene_invalidate;
    mt["isActive"] = &QGraphicsScene::isActive;
    mt["itemAt"] = QGraphicsScene_itemAt;
    mt["itemIndexMethod"] = &QGraphicsScene::itemIndexMethod;
    mt["items"] = QGraphicsScene_items;
    mt["itemsBoundingRect"] = &QGraphicsScene::itemsBoundingRect;
    mt["mouseGrabberItem"] = &QGraphicsScene::mouseGrabberItem;
    mt["palette"] = &QGraphicsScene::palette;
    mt["removeItem"] = &QGraphicsScene::removeItem;
    mt["render"] = QGraphicsScene_render;
    mt["sceneRect"] = &QGraphicsScene::sceneRect;
    mt["selectedItems"] = &QGraphicsScene::selectedItems;
    mt["selectionArea"] = &QGraphicsScene::selectionArea;
    mt["sendEvent"] = &QGraphicsScene::sendEvent;
    mt["setActivePanel"] = &QGraphicsScene::setActivePanel;
    mt["setActiveWindow"] = &QGraphicsScene::setActiveWindow;
    mt["setBackgroundBrush"] = &QGraphicsScene::setBackgroundBrush;
    mt["setBspTreeDepth"] = &QGraphicsScene::setBspTreeDepth;
    mt["setFocus"] = QGraphicsScene_setFocus;
    mt["setFocusItem"] = QGraphicsScene_setFocusItem;
    mt["setFont"] = &QGraphicsScene::setFont;
    mt["setForegroundBrush"] = &QGraphicsScene::setForegroundBrush;
    mt["setItemIndexMethod"] = &QGraphicsScene::setItemIndexMethod;
    mt["setPalette"] = &QGraphicsScene::setPalette;
    mt["setSceneRect"] = QGraphicsScene_setSceneRect;
    mt["setSelectionArea"] = QGraphicsScene_setSelectionArea;
    mt["setStickyFocus"] = &QGraphicsScene::setStickyFocus;
    mt["setStyle"] = &QGraphicsScene::setStyle;
    mt["stickyFocus"] = &QGraphicsScene::stickyFocus;
    mt["style"] = &QGraphicsScene::style;
    mt["update"] = QGraphicsScene_update;
    mt["views"] = &QGraphicsScene::views;
    mt["width"] = &QGraphicsScene::width;
}

int QGraphicsScene_new(lua_State* const state)
{
    // QGraphicsScene(QObject * parent = 0)
    // QGraphicsScene(const QRectF & sceneRect, QObject * parent = 0)
    // QGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0)
    lua::make<QGraphicsScene>(state);

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsScene(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsScene"] = lua::value::table;
    env["QGraphicsScene"]["new"] = QGraphicsScene_new;
    auto t = env["QGraphicsScene"];

    // enum QGraphicsScene::ItemIndexMethod
    t["BspTreeIndex"] = QGraphicsScene::BspTreeIndex;
    t["NoIndex"] = QGraphicsScene::NoIndex;

    // enum QGraphicsScene::SceneLayer
    t["ItemLayer"] = QGraphicsScene::ItemLayer;
    t["BackgroundLayer"] = QGraphicsScene::BackgroundLayer;
    t["ForegroundLayer"] = QGraphicsScene::ForegroundLayer;
    t["AllLayers"] = QGraphicsScene::AllLayers;

    return 0;
}

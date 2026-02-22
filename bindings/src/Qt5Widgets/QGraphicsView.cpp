#include "QGraphicsView.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Gui/QBrush.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Gui/QPainterPath.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Gui/QPolygonF.hpp"
#include "../Qt5Gui/QMatrix.hpp"
#include "../Qt5Gui/QPainter.hpp"
#include "../Qt5Gui/QTransform.hpp"
#include "QGraphicsScene.hpp"
#include "QAbstractScrollArea.hpp"
#include "../Qt5Core/QRectF.hpp"

#include "../Qt5Core/QList.hpp"
#include "../Qt5Gui/QPolygon.hpp"
#include "QGraphicsItem.hpp"

int QGraphicsView_centerOn(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    if (lua::is_type<QGraphicsItem>(state, 2)) {
        // void     centerOn(const QGraphicsItem * item)
        self->centerOn(
            lua::get<const QGraphicsItem*>(state, 2)
        );
    } else if (lua::is_type<QPointF>(state, 2)) {
        // void     centerOn(const QPointF & pos)
        self->centerOn(
            lua::get<const QPointF&>(state, 2)
        );
    } else {
        // void     centerOn(qreal x, qreal y)
        self->centerOn(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        );
    }
    return 0;
}

int QGraphicsView_ensureVisible(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    switch (lua_gettop(state)) {
    case 2:
        if (lua::is_type<QRectF>(state, 2)) {
            // void     ensureVisible(const QRectF & rect, int xmargin = 50, int ymargin = 50)
            self->ensureVisible(
                lua::get<const QRectF&>(state, 2)
            );
        } else {
            // void     ensureVisible(const QGraphicsItem * item, int xmargin = 50, int ymargin = 50)
            self->ensureVisible(
                lua::get<const QGraphicsItem*>(state, 2)
            );
        }
        break;
    case 3:
        if (lua::is_type<QRectF>(state, 2)) {
            // void     ensureVisible(const QRectF & rect, int xmargin = 50, int ymargin = 50)
            self->ensureVisible(
                lua::get<const QRectF&>(state, 2),
                lua::get<int>(state, 3)
            );
        } else {
            // void     ensureVisible(const QGraphicsItem * item, int xmargin = 50, int ymargin = 50)
            self->ensureVisible(
                lua::get<const QGraphicsItem*>(state, 2),
                lua::get<int>(state, 3)
            );
        }
        break;
    case 4:
        if (lua::is_type<QRectF>(state, 2)) {
            // void     ensureVisible(const QRectF & rect, int xmargin = 50, int ymargin = 50)
            self->ensureVisible(
                lua::get<const QRectF&>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4)
            );
        } else {
            // void     ensureVisible(const QGraphicsItem * item, int xmargin = 50, int ymargin = 50)
            self->ensureVisible(
                lua::get<const QGraphicsItem*>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4)
            );
        }
        break;
    case 5:
        // void     ensureVisible(qreal x, qreal y, qreal w, qreal h)
        self->ensureVisible(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        );
        break;
    case 6:
        // void     ensureVisible(qreal x, qreal y, qreal w, qreal h, int xmargin = 50, int ymargin = 50)
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

    return 0;
}

int QGraphicsView_fitInView(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    if (lua::is_type<QRectF>(state, 2)) {
        //  void    fitInView(const QRectF & rect, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio)
        if (lua_gettop(state) == 2) {
            self->fitInView(
                lua::get<const QRectF&>(state, 2)
            );
        } else {
            self->fitInView(
                lua::get<const QRectF&>(state, 2),
                lua::get<Qt::AspectRatioMode>(state, 3)
            );
        }
    } else if (lua::is_type<QGraphicsItem>(state, 2)) {
        //  void    fitInView(const QGraphicsItem * item, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio)
        if (lua_gettop(state) == 2) {
            self->fitInView(
                lua::get<const QGraphicsItem*>(state, 2)
            );
        } else {
            self->fitInView(
                lua::get<const QGraphicsItem*>(state, 2),
                lua::get<Qt::AspectRatioMode>(state, 3)
            );
        }
    } else {
        //  void    fitInView(qreal x, qreal y, qreal w, qreal h, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio)
        if (lua_gettop(state) == 5) {
            self->fitInView(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5)
            );
        } else {
            self->fitInView(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5),
                lua::get<Qt::AspectRatioMode>(state, 6)
            );
        }
    }

    return 0;
}

int QGraphicsView_itemAt(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);
    if (lua_gettop(state) == 1) {
        //  QGraphicsItem *     itemAt(const QPoint & pos) const
        lua::push(state, self->itemAt(
            lua::get<const QPoint&>(state, 2)
        ));
    } else {
        //  QGraphicsItem *     itemAt(int x, int y) const
        lua::push(state, self->itemAt(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        ));
    }
    return 1;
}

int QGraphicsView_items(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    switch (lua_gettop(state)) {
    case 1:
        // QList<QGraphicsItem *>   items() const
        lua::push(state, self->items());
        break;
    case 2:
        if (lua::is_type<QPoint>(state, 2)) {
            // QList<QGraphicsItem *>   items(const QPoint & pos) const
            lua::push(state, self->items(
                lua::get<const QPoint&>(state, 2)
            ));
        } else if (lua::is_type<QRect>(state, 2)) {
            // QList<QGraphicsItem *>   items(const QRect & rect, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const
            lua::push(state, self->items(
                lua::get<const QRect&>(state, 2)
            ));
        } else if (lua::is_type<QPolygon>(state, 2)) {
            // QList<QGraphicsItem *>   items(const QPolygon & polygon, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const
            lua::push(state, self->items(
                lua::get<const QPolygon&>(state, 2)
            ));
        } else if (lua::is_type<QPainterPath>(state, 2)) {
            // QList<QGraphicsItem *>   items(const QPainterPath & path, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const
            lua::push(state, self->items(
                lua::get<const QPainterPath&>(state, 2)
            ));
        }
        break;
    case 3:
        // QList<QGraphicsItem *>   items(int x, int y) const
        lua::push(state, self->items(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        ));
        break;
    case 5:
        // QList<QGraphicsItem *>   items(int x, int y, int w, int h) const
        lua::push(state, self->items(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5)
        ));
        break;
    case 6:
        // QList<QGraphicsItem *>   items(int x, int y, int w, int h, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const
        lua::push(state, self->items(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5),
            lua::get<Qt::ItemSelectionMode>(state, 6)
        ));
        break;
    }
    return 1;
}

int QGraphicsView_mapFromScene(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    switch (lua_gettop(state)) {
    case 2:
        // QPoint   mapFromScene(const QPointF & point) const
        // QPolygon     mapFromScene(const QRectF & rect) const
        // QPolygon     mapFromScene(const QPolygonF & polygon) const
        // QPainterPath     mapFromScene(const QPainterPath & path) const
        if (lua::is_type<QPointF>(state, 2)) {
            lua::push(state, self->mapFromScene(
                lua::get<const QPointF&>(state, 2)
            ));
        } else if (lua::is_type<QRectF>(state, 2)) {
            lua::push(state, self->mapFromScene(
                lua::get<const QRectF&>(state, 2)
            ));
        } else if (lua::is_type<QPolygonF>(state, 2)) {
            lua::push(state, self->mapFromScene(
                lua::get<const QPolygonF&>(state, 2)
            ));
        } else if (lua::is_type<QPainterPath>(state, 2)) {
            lua::push(state, self->mapFromScene(
                lua::get<const QPainterPath&>(state, 2)
            ));
        }
        break;
    case 3:
        // QPoint  mapFromScene(qreal x, qreal y) const
        lua::push(state, self->mapFromScene(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        ));
        break;
    case 5:
    default:
        // QPolygon    mapFromScene(qreal x, qreal y, qreal w, qreal h) const
        lua::push(state, self->mapFromScene(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        ));
        break;
    }

    return 1;
}

int QGraphicsView_mapToScene(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    switch (lua_gettop(state)) {
    case 2:
        // QPointF  mapToScene(const QPoint & point) const
        // QPolygonF    mapToScene(const QRect & rect) const
        // QPolygonF    mapToScene(const QPolygon & polygon) const
        // QPainterPath     mapToScene(const QPainterPath & path) const
        if (lua::is_type<QPoint>(state, 2)) {
            lua::push(state, self->mapToScene(
                lua::get<const QPoint&>(state, 2)
            ));
        } else if (lua::is_type<QRect>(state, 2)) {
            lua::push(state, self->mapToScene(
                lua::get<const QRect&>(state, 2)
            ));
        } else if (lua::is_type<QPolygon>(state, 2)) {
            lua::push(state, self->mapToScene(
                lua::get<const QPolygon&>(state, 2)
            ));
        } else if (lua::is_type<QPainterPath>(state, 2)) {
            lua::push(state, self->mapToScene(
                lua::get<const QPainterPath&>(state, 2)
            ));
        }
        break;
    case 3:
        // QPointF  mapToScene(int x, int y) const
        lua::push(state, self->mapToScene(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        ));
        break;
    case 5:
    default:
        // QPolygonF    mapToScene(int x, int y, int w, int h) const
        lua::push(state, self->mapToScene(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5)
        ));
        break;
    }

    return 1;
}

int QGraphicsView_render(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    //  void    render(QPainter * painter, const QRectF & target = QRectF(), const QRect & source = QRect(), Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio)
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
            lua::get<const QRect&>(state, 4)
        );
        break;
    case 5:
    default:
        self->render(
            lua::get<QPainter*>(state, 2),
            lua::get<const QRectF&>(state, 3),
            lua::get<const QRect&>(state, 4),
            lua::get<Qt::AspectRatioMode>(state, 5)
        );
        break;
    }

    return 0;
}

int QGraphicsView_setMatrix(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    // void     setMatrix(const QMatrix & matrix, bool combine = false)
    if (lua_gettop(state) == 2) {
        self->setMatrix(
            lua::get<const QMatrix&>(state, 2)
        );
    } else {
        self->setMatrix(
            lua::get<const QMatrix&>(state, 2),
            lua::get<bool>(state, 3)
        );
    }
    return 0;
}

int QGraphicsView_setOptimizationFlag(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    // void     setOptimizationFlag(OptimizationFlag flag, bool enabled = true)
    if (lua_gettop(state) == 2) {
        self->setOptimizationFlag(
            lua::get<QGraphicsView::OptimizationFlag>(state, 2)
        );
    } else {
        self->setOptimizationFlag(
            lua::get<QGraphicsView::OptimizationFlag>(state, 2),
            lua::get<bool>(state, 3)
        );
    }
    return 0;
}

int QGraphicsView_setRenderHint(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    // void     setRenderHint(QPainter::RenderHint hint, bool enabled = true)
    if (lua_gettop(state) == 2) {
        self->setRenderHint(
            lua::get<QPainter::RenderHint>(state, 2)
        );
    } else {
        self->setRenderHint(
            lua::get<QPainter::RenderHint>(state, 2),
            lua::get<bool>(state, 3)
        );
    }
    return 0;
}

int QGraphicsView_setSceneRect(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);
    if (lua_gettop(state) == 2) {
        // void    setSceneRect(const QRectF & rect)
        self->setSceneRect(
            lua::get<const QRectF&>(state, 2)
        );
    } else {
        // void    setSceneRect(qreal x, qreal y, qreal w, qreal h)
        self->setSceneRect(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        );
    }
    return 0;
}

int QGraphicsView_setTransform(lua_State* const state)
{
    auto self = lua::get<QGraphicsView*>(state, 1);

    // void     setTransform(const QTransform & matrix, bool combine = false)
    if (lua_gettop(state) == 2) {
        self->setTransform(
            lua::get<const QTransform&>(state, 2)
        );
    } else {
        self->setTransform(
            lua::get<const QTransform&>(state, 2),
            lua::get<bool>(state, 3)
        );
    }
    return 0;
}

void lua::QGraphicsView_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractScrollArea_metatable(state, pos);

    lua::index mt(state, pos);
    mt["alignment"] = &QGraphicsView::alignment;
    mt["backgroundBrush"] = &QGraphicsView::backgroundBrush;
    mt["cacheMode"] = &QGraphicsView::cacheMode;
    mt["centerOn"] = QGraphicsView_centerOn;
    mt["dragMode"] = &QGraphicsView::dragMode;
    mt["ensureVisible"] = QGraphicsView_ensureVisible;
    mt["fitInView"] = QGraphicsView_fitInView;
    mt["foregroundBrush"] = &QGraphicsView::foregroundBrush;
    mt["isInteractive"] = &QGraphicsView::isInteractive;
    mt["isTransformed"] = &QGraphicsView::isTransformed;
    mt["itemAt"] = QGraphicsView_itemAt;
    mt["items"] = QGraphicsView_items;
    mt["mapFromScene"] = QGraphicsView_mapFromScene;
    mt["mapToScene"] = QGraphicsView_mapToScene;
    mt["matrix"] = &QGraphicsView::matrix;
    mt["optimizationFlags"] = &QGraphicsView::optimizationFlags;
    mt["render"] = QGraphicsView_render;
    mt["renderHints"] = &QGraphicsView::renderHints;
    mt["resetCachedContent"] = &QGraphicsView::resetCachedContent;
    mt["resetMatrix"] = &QGraphicsView::resetMatrix;
    mt["resetTransform"] = &QGraphicsView::resetTransform;
    mt["resizeAnchor"] = &QGraphicsView::resizeAnchor;
    mt["rotate"] = &QGraphicsView::rotate;
    mt["rubberBandRect"] = &QGraphicsView::rubberBandRect;
    mt["rubberBandSelectionMode"] = &QGraphicsView::rubberBandSelectionMode;
    mt["scale"] = &QGraphicsView::scale;
    mt["scene"] = &QGraphicsView::scene;
    mt["sceneRect"] = &QGraphicsView::sceneRect;
    mt["setAlignment"] = &QGraphicsView::setAlignment;
    mt["setBackgroundBrush"] = &QGraphicsView::setBackgroundBrush;
    mt["setCacheMode"] = &QGraphicsView::setCacheMode;
    mt["setDragMode"] = &QGraphicsView::setDragMode;
    mt["setForegroundBrush"] = &QGraphicsView::setForegroundBrush;
    mt["setInteractive"] = &QGraphicsView::setInteractive;
    mt["setMatrix"] = QGraphicsView_setMatrix;
    mt["setOptimizationFlag"] = QGraphicsView_setOptimizationFlag;
    mt["setOptimizationFlags"] = &QGraphicsView::setOptimizationFlags;
    mt["setRenderHint"] = QGraphicsView_setRenderHint;
    mt["setRenderHints"] = &QGraphicsView::setRenderHints;
    mt["setResizeAnchor"] = &QGraphicsView::setResizeAnchor;
    mt["setRubberBandSelectionMode"] = &QGraphicsView::setRubberBandSelectionMode;
    mt["setScene"] = &QGraphicsView::setScene;
    mt["setSceneRect"] = QGraphicsView_setSceneRect;
    mt["setTransform"] = QGraphicsView_setTransform;
    mt["setTransformationAnchor"] = &QGraphicsView::setTransformationAnchor;
    mt["setViewportUpdateMode"] = &QGraphicsView::setViewportUpdateMode;
    mt["shear"] = &QGraphicsView::shear;
    mt["transform"] = &QGraphicsView::transform;
    mt["transformationAnchor"] = &QGraphicsView::transformationAnchor;
    mt["translate"] = &QGraphicsView::translate;
    mt["viewportTransform"] = &QGraphicsView::viewportTransform;
    mt["viewportUpdateMode"] = &QGraphicsView::viewportUpdateMode;
}

int QGraphicsView_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QGraphicsView()
        lua::push(state, new QGraphicsView);
    } else if (lua_gettop(state) == 2) {
        // QGraphicsView(QGraphicsScene * scene, QWidget * parent = 0)
        lua::push(state, new QGraphicsView(
            lua::get<QGraphicsScene*>(state, 1),
            lua::get<QWidget*>(state, 2)
        ));
    } else if (lua::is_type<QGraphicsScene>(state, 1)) {
        // QGraphicsView(QGraphicsScene * scene, QWidget * parent = 0)
        lua::push(state, new QGraphicsView(
            lua::get<QGraphicsScene*>(state, 1)
        ));
    } else {
        // QGraphicsView(QWidget * parent = 0)
        lua::push(state, new QGraphicsView(
            lua::get<QWidget*>(state, 1)
        ));
    }

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsView(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsView"] = lua::value::table;
    env["QGraphicsView"]["new"] = QGraphicsView_new;
    auto t = env["QGraphicsView"];

    // enum QGraphicsView::CacheModeFlag
    t["CacheNone"] = QGraphicsView::CacheNone;
    t["CacheBackground"] = QGraphicsView::CacheBackground;

    // enum QGraphicsView::DragMode
    t["NoDrag"] = QGraphicsView::NoDrag;
    t["ScrollHandDrag"] = QGraphicsView::ScrollHandDrag;
    t["RubberBandDrag"] = QGraphicsView::RubberBandDrag;

    // enum QGraphicsView::OptimizationFlag
    t["DontClipPainter"] = QGraphicsView::DontClipPainter;
    t["DontSavePainterState"] = QGraphicsView::DontSavePainterState;
    t["DontAdjustForAntialiasing"] = QGraphicsView::DontAdjustForAntialiasing;
    t["IndirectPainting"] = QGraphicsView::IndirectPainting;

    // enum QGraphicsView::ViewportAnchor
    t["NoAnchor"] = QGraphicsView::NoAnchor;
    t["AnchorViewCenter"] = QGraphicsView::AnchorViewCenter;
    t["AnchorUnderMouse"] = QGraphicsView::AnchorUnderMouse;

    // enum QGraphicsView::ViewportUpdateMode
    t["FullViewportUpdate"] = QGraphicsView::FullViewportUpdate;
    t["MinimalViewportUpdate"] = QGraphicsView::MinimalViewportUpdate;
    t["SmartViewportUpdate"] = QGraphicsView::SmartViewportUpdate;
    t["BoundingRectViewportUpdate"] = QGraphicsView::BoundingRectViewportUpdate;
    t["NoViewportUpdate"] = QGraphicsView::NoViewportUpdate;

    return 0;
}

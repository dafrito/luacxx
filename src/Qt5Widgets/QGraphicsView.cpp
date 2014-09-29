#include "QGraphicsView.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QGraphicsView>

#include "../Qt5Gui/QBrush.hpp"
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

int QGraphicsView_centerOn(lua_State* const state)
{
    return 0;
}
int QGraphicsView_ensureVisible(lua_State* const state)
{
    return 0;
}
int QGraphicsView_fitInView(lua_State* const state)
{
    return 0;
}
int QGraphicsView_itemAt(lua_State* const state)
{
    return 0;
}
int QGraphicsView_items(lua_State* const state)
{
    return 0;
}
int QGraphicsView_mapFromScene(lua_State* const state)
{
    return 0;
}
int QGraphicsView_mapToScene(lua_State* const state)
{
    return 0;
}
int QGraphicsView_render(lua_State* const state)
{
    return 0;
}
int QGraphicsView_setMatrix(lua_State* const state)
{
    return 0;
}
int QGraphicsView_setOptimizationFlag(lua_State* const state)
{
    return 0;
}
int QGraphicsView_setRenderHint(lua_State* const state)
{
    return 0;
}
int QGraphicsView_setSceneRect(lua_State* const state)
{
    return 0;
}
int QGraphicsView_setTransform(lua_State* const state)
{
    return 0;
}

void lua::QGraphicsView_metatable(const lua::index& mt)
{
    lua::QAbstractScrollArea_metatable(mt);

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
    // QGraphicsView(QWidget * parent = 0)
    // QGraphicsView(QGraphicsScene * scene, QWidget * parent = 0)
    lua::make<QGraphicsView>(state);
    // TODO Set up object-specific methods

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

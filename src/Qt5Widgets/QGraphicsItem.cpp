#include "QGraphicsItem.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Gui/QPainterPath.hpp"
#include "../Qt5Gui/QCursor.hpp"
#include "../Qt5Gui/QTransform.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Gui/QRegion.hpp"
#include "QGraphicsEffect.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "QGraphicsWidget.hpp"
#include "QGraphicsObject.hpp"
#include "QGraphicsScene.hpp"
#include "QGraphicsTransform.hpp"
#include "QGraphicsItemGroup.hpp"

#include <QGraphicsItem>

int QGraphicsItem_collidesWithItem(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_collidesWithPath(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_cursor(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_collidingItems(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_ensureVisible(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_isObscured(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_itemTransform(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapFromItem(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapFromParent(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapFromScene(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapRectFromItem(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapRectFromParent(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapRectFromScene(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapRectToItem(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapRectToParent(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapRectToScene(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapToItem(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapToParent(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_mapToScene(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_paint(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_scroll(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_setCacheMode(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_setFlag(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_setFocus(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_setPos(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_setTransform(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_setTransformOriginPoint(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_toGraphicsObject(lua_State* const state)
{
    return 0;
}
int QGraphicsItem_update(lua_State* const state)
{
    return 0;
}

void lua::QGraphicsItem_metatable(const lua::index& mt)
{
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
    mt["cursor"] = QGraphicsItem_cursor;
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

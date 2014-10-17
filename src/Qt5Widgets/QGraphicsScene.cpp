#include "QGraphicsScene.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QGraphicsScene>

#include "QGraphicsWidget.hpp"
#include "../Qt5Gui/QBrush.hpp"
#include "../Qt5Gui/QFont.hpp"
#include "QGraphicsItem.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "QGraphicsItemGroup.hpp"
#include "../Qt5Gui/QPalette.hpp"
#include "QStyle.hpp"
#include "../Qt5Core/QEvent.hpp"
#include "../Qt5Gui/QPainterPath.hpp"
#include "QGraphicsView.hpp"

// https://qt-project.org/doc/qt-5/qgraphicsscene.html

int QGraphicsScene_addEllipse(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_addLine(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_addPath(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_addPolygon(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_addRect(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_addSimpleText(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_addText(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_addWidget(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_collidingItems(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_invalidate(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_itemAt(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_items(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_render(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_setFocus(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_setFocusItem(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_setSceneRect(lua_State* const state)
{
    return 0;
}
int QGraphicsScene_setSelectionArea(lua_State* const state)
{
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

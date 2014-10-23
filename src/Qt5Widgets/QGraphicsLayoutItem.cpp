#include "QGraphicsLayoutItem.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QSizeF.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "QSizePolicy.hpp"
#include "QGraphicsItem.hpp"

int QGraphicsLayoutItem_effectiveSizeHint(lua_State* const state)
{
    return 0;
}
int QGraphicsLayoutItem_getContentsMargins(lua_State* const state)
{
    return 0;
}
int QGraphicsLayoutItem_setMaximumSize(lua_State* const state)
{
    return 0;
}
int QGraphicsLayoutItem_setMinimumSize(lua_State* const state)
{
    return 0;
}
int QGraphicsLayoutItem_setPreferredSize(lua_State* const state)
{
    return 0;
}
int QGraphicsLayoutItem_setSizePolicy(lua_State* const state)
{
    return 0;
}

void lua::QGraphicsLayoutItem_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["contentsRect"] = &QGraphicsLayoutItem::contentsRect;
    mt["effectiveSizeHint"] = QGraphicsLayoutItem_effectiveSizeHint;
    mt["geometry"] = &QGraphicsLayoutItem::geometry;
    mt["getContentsMargins"] = QGraphicsLayoutItem_getContentsMargins;
    mt["graphicsItem"] = &QGraphicsLayoutItem::graphicsItem;
    mt["isLayout"] = &QGraphicsLayoutItem::isLayout;
    mt["maximumHeight"] = &QGraphicsLayoutItem::maximumHeight;
    mt["maximumSize"] = &QGraphicsLayoutItem::maximumSize;
    mt["maximumWidth"] = &QGraphicsLayoutItem::maximumWidth;
    mt["minimumHeight"] = &QGraphicsLayoutItem::minimumHeight;
    mt["minimumSize"] = &QGraphicsLayoutItem::minimumSize;
    mt["minimumWidth"] = &QGraphicsLayoutItem::minimumWidth;
    mt["ownedByLayout"] = &QGraphicsLayoutItem::ownedByLayout;
    mt["parentLayoutItem"] = &QGraphicsLayoutItem::parentLayoutItem;
    mt["preferredHeight"] = &QGraphicsLayoutItem::preferredHeight;
    mt["preferredSize"] = &QGraphicsLayoutItem::preferredSize;
    mt["preferredWidth"] = &QGraphicsLayoutItem::preferredWidth;
    mt["setGeometry"] = &QGraphicsLayoutItem::setGeometry;
    mt["setMaximumHeight"] = &QGraphicsLayoutItem::setMaximumHeight;
    mt["setMaximumSize"] = QGraphicsLayoutItem_setMaximumSize;
    mt["setMaximumWidth"] = &QGraphicsLayoutItem::setMaximumWidth;
    mt["setMinimumHeight"] = &QGraphicsLayoutItem::setMinimumHeight;
    mt["setMinimumSize"] = QGraphicsLayoutItem_setMinimumSize;
    mt["setMinimumWidth"] = &QGraphicsLayoutItem::setMinimumWidth;
    mt["setParentLayoutItem"] = &QGraphicsLayoutItem::setParentLayoutItem;
    mt["setPreferredHeight"] = &QGraphicsLayoutItem::setPreferredHeight;
    mt["setPreferredSize"] = QGraphicsLayoutItem_setPreferredSize;
    mt["setPreferredWidth"] = &QGraphicsLayoutItem::setPreferredWidth;
    mt["setSizePolicy"] = QGraphicsLayoutItem_setSizePolicy;
    mt["sizePolicy"] = &QGraphicsLayoutItem::sizePolicy;
    mt["updateGeometry"] = &QGraphicsLayoutItem::updateGeometry;
}

int luaopen_Qt5Widgets_QGraphicsLayoutItem(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsLayoutItem"] = lua::value::table;

    return 0;
}

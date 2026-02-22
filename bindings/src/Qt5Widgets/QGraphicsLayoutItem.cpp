#include "QGraphicsLayoutItem.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QSizeF.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/Qt.hpp"
#include "QSizePolicy.hpp"
#include "QGraphicsItem.hpp"

int QGraphicsLayoutItem_effectiveSizeHint(lua_State* const state)
{
    // QSizeF effectiveSizeHint(Qt::SizeHint which, const QSizeF & constraint = QSizeF()) const
    auto self = lua::get<QGraphicsLayoutItem*>(state, 1);
    if (lua_gettop(state) == 2) {
        lua::push(state, self->effectiveSizeHint(
            lua::get<Qt::SizeHint>(state, 2)
        ));
    } else {
        lua::push(state, self->effectiveSizeHint(
            lua::get<Qt::SizeHint>(state, 2),
            lua::get<const QSizeF&>(state, 3)
        ));
    }
    return 1;
}

// void getContentsMargins(qreal * left, qreal * top, qreal * right, qreal * bottom)
int QGraphicsLayoutItem_getContentsMargins(lua_State* const state)
{
    auto self = lua::get<QGraphicsLayoutItem*>(state, 1);
    if (lua_gettop(state) > 1) {
        self->getContentsMargins(
            lua::get<qreal*>(state, 2),
            lua::get<qreal*>(state, 3),
            lua::get<qreal*>(state, 4),
            lua::get<qreal*>(state, 5)
        );
        return 0;
    }

    qreal left, top, right, bottom;
    self->getContentsMargins(&left, &top, &right, &bottom);
    lua::push(state,
        left,
        top,
        right,
        bottom
    );
    return 4;
}

int QGraphicsLayoutItem_setMaximumSize(lua_State* const state)
{
    auto self = lua::get<QGraphicsLayoutItem*>(state, 1);

    if (lua_gettop(state) == 2) {
        // void setMaximumSize(const QSizeF & size)
        self->setMaximumSize(lua::get<const QSizeF&>(state, 2));
    } else {
        // void setMaximumSize(qreal w, qreal h)
        self->setMaximumSize(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        );
    }
    return 0;
}

int QGraphicsLayoutItem_setMinimumSize(lua_State* const state)
{
    auto self = lua::get<QGraphicsLayoutItem*>(state, 1);

    if (lua_gettop(state) == 2) {
        // void setMinimumSize(const QSizeF & size)
        self->setMinimumSize(lua::get<const QSizeF&>(state, 2));
    } else {
        // void setMinimumSize(qreal w, qreal h)
        self->setMinimumSize(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        );
    }
    return 0;
}

int QGraphicsLayoutItem_setPreferredSize(lua_State* const state)
{
    auto self = lua::get<QGraphicsLayoutItem*>(state, 1);

    if (lua_gettop(state) == 2) {
        // void setPreferredSize(const QSizeF & size)
        self->setPreferredSize(lua::get<const QSizeF&>(state, 2));
    } else {
        // void setPreferredSize(qreal w, qreal h)
        self->setPreferredSize(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        );
    }
    return 0;
}

int QGraphicsLayoutItem_setSizePolicy(lua_State* const state)
{
    auto self = lua::get<QGraphicsLayoutItem*>(state, 1);

    if (lua_gettop(state) == 2) {
        // void setSizePolicy(const QSizePolicy & policy)
        self->setSizePolicy(lua::get<const QSizePolicy&>(state, 2));
    } else if (lua_gettop(state) == 3) {
        // void setSizePolicy(QSizePolicy::Policy hPolicy, QSizePolicy::Policy vPolicy, QSizePolicy::ControlType controlType = QSizePolicy::DefaultType)
        self->setSizePolicy(
            lua::get<QSizePolicy::Policy>(state, 2),
            lua::get<QSizePolicy::Policy>(state, 3)
        );
    } else {
        self->setSizePolicy(
            lua::get<QSizePolicy::Policy>(state, 2),
            lua::get<QSizePolicy::Policy>(state, 3),
            lua::get<QSizePolicy::ControlType>(state, 4)
        );
    }
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

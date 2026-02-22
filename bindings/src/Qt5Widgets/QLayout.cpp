#include "QLayout.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QLayoutItem.hpp"
#include "QWidget.hpp"
#include "../Qt5Core/QMargins.hpp"
#include "../Qt5Core/QRect.hpp"

int QLayout_getContentsMargins(lua_State* const state)
{
    return 0;
}
int QLayout_replaceWidget(lua_State* const state)
{
    return 0;
}
int QLayout_setAlignment(lua_State* const state)
{
    return 0;
}
int QLayout_setContentsMargins(lua_State* const state)
{
    return 0;
}

void lua::QLayout_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["activate"] = &QLayout::activate;
    mt["addWidget"] = &QLayout::addWidget;
    mt["contentsMargins"] = &QLayout::contentsMargins;
    mt["contentsRect"] = &QLayout::contentsRect;
    mt["getContentsMargins"] = QLayout_getContentsMargins;
    mt["indexOf"] = &QLayout::indexOf;
    mt["isEnabled"] = &QLayout::isEnabled;
    mt["menuBar"] = &QLayout::menuBar;
    mt["parentWidget"] = &QLayout::parentWidget;
    mt["removeItem"] = &QLayout::removeItem;
    mt["removeWidget"] = &QLayout::removeWidget;
    mt["replaceWidget"] = QLayout_replaceWidget;
    mt["setAlignment"] = QLayout_setAlignment;
    mt["setContentsMargins"] = QLayout_setContentsMargins;
    mt["setEnabled"] = &QLayout::setEnabled;
    mt["setMenuBar"] = &QLayout::setMenuBar;
    mt["setSizeConstraint"] = &QLayout::setSizeConstraint;
    mt["setSpacing"] = &QLayout::setSpacing;
    mt["sizeConstraint"] = &QLayout::sizeConstraint;
    mt["spacing"] = &QLayout::spacing;
    mt["update"] = &QLayout::update;
}

int luaopen_Qt5Widgets_QLayout(lua_State* const state)
{
    lua::thread env(state);

    env["QLayout"] = lua::value::table;
    auto t = env["QLayout"];

    // enum QLayout::SizeConstraint
    t["SetDefaultConstraint"] = QLayout::SetDefaultConstraint;
    t["SetFixedSize"] = QLayout::SetFixedSize;
    t["SetMinimumSize"] = QLayout::SetMinimumSize;
    t["SetMaximumSize"] = QLayout::SetMaximumSize;
    t["SetMinAndMaxSize"] = QLayout::SetMinAndMaxSize;
    t["SetNoConstraint"] = QLayout::SetNoConstraint;

    return 0;
}

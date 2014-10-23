#include "QMenuBar.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QMenuBar>
#include "QAction.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "QWidget.hpp"
#include "../Qt5Core/QRect.hpp"
#include "QMenu.hpp"

int QMenuBar_addAction(lua_State* const state)
{
    return 0;
}
int QMenuBar_addMenu(lua_State* const state)
{
    return 0;
}
int QMenuBar_cornerWidget(lua_State* const state)
{
    return 0;
}
int QMenuBar_setCornerWidget(lua_State* const state)
{
    return 0;
}

void lua::QMenuBar_metatable(lua_State* const state, const int pos)
{
    lua::QWidget_metatable(state, pos);

    lua::index mt(state, pos);
    mt["actionAt"] = &QMenuBar::actionAt;
    mt["actionGeometry"] = &QMenuBar::actionGeometry;
    mt["activeAction"] = &QMenuBar::activeAction;
    mt["addAction"] = QMenuBar_addAction;
    mt["addMenu"] = QMenuBar_addMenu;
    mt["addSeparator"] = &QMenuBar::addSeparator;
    mt["clear"] = &QMenuBar::clear;
    mt["cornerWidget"] = QMenuBar_cornerWidget;
    // mt["defaultAction"] = &QMenuBar::defaultAction;
    mt["insertMenu"] = &QMenuBar::insertMenu;
    mt["insertSeparator"] = &QMenuBar::insertSeparator;
    mt["isDefaultUp"] = &QMenuBar::isDefaultUp;
    mt["isNativeMenuBar"] = &QMenuBar::isNativeMenuBar;
    mt["setActiveAction"] = &QMenuBar::setActiveAction;
    mt["setCornerWidget"] = QMenuBar_setCornerWidget;
    // mt["setDefaultAction"] = &QMenuBar::setDefaultAction;
    mt["setDefaultUp"] = &QMenuBar::setDefaultUp;
    mt["setNativeMenuBar"] = &QMenuBar::setNativeMenuBar;
}

int QMenuBar_new(lua_State* const state)
{
    // QMenuBar(QWidget * parent = 0)
    lua::make<QMenuBar>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QMenuBar(lua_State* const state)
{
    lua::thread env(state);

    env["QMenuBar"] = lua::value::table;
    env["QMenuBar"]["new"] = QMenuBar_new;

    return 0;
}

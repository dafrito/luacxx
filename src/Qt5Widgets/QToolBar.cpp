#include "QToolBar.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QToolBar>

#include "QAction.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QSize.hpp"
#include "QWidget.hpp"

void lua::QToolBar_metatable(const lua::index& mt)
{
    lua::QWidget_metatable(mt);

    mt["actionAt"] = QToolBar_actionAt;
    mt["addAction"] = QToolBar_addAction;
    mt["addSeparator"] = &QToolBar::addSeparator;
    mt["addWidget"] = &QToolBar::addWidget;
    mt["allowedAreas"] = &QToolBar::allowedAreas;
    mt["clear"] = &QToolBar::clear;
    mt["iconSize"] = &QToolBar::iconSize;
    mt["insertSeparator"] = &QToolBar::insertSeparator;
    mt["insertWidget"] = &QToolBar::insertWidget;
    mt["isAreaAllowed"] = &QToolBar::isAreaAllowed;
    mt["isFloatable"] = &QToolBar::isFloatable;
    mt["isFloating"] = &QToolBar::isFloating;
    mt["isMovable"] = &QToolBar::isMovable;
    mt["orientation"] = &QToolBar::orientation;
    mt["setAllowedAreas"] = &QToolBar::setAllowedAreas;
    mt["setFloatable"] = &QToolBar::setFloatable;
    mt["setMovable"] = &QToolBar::setMovable;
    mt["setOrientation"] = &QToolBar::setOrientation;
    mt["toggleViewAction"] = &QToolBar::toggleViewAction;
    mt["toolButtonStyle"] = &QToolBar::toolButtonStyle;
    mt["widgetForAction"] = &QToolBar::widgetForAction;
}

int QToolBar_new(lua_State* const state)
{
    // QToolBar(const QString & title, QWidget * parent = 0)
    // QToolBar(QWidget * parent = 0)
    lua::make<QToolBar>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QToolBar(lua_State* const state)
{
    lua::thread env(state);

    env["QToolBar"] = lua::value::table;
    env["QToolBar"]["new"] = QToolBar_new;
    auto t = env["QToolBar"];

    return 0;
}

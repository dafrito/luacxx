#include "QDockWidget.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QWidget.hpp"
#include "QAction.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"

void lua::QDockWidget_metatable(lua_State* const state, const int pos)
{
    lua::QWidget_metatable(state, pos);

    lua::index mt(state, pos);
    mt["allowedAreas"] = &QDockWidget::allowedAreas;
    mt["features"] = &QDockWidget::features;
    mt["isAreaAllowed"] = &QDockWidget::isAreaAllowed;
    mt["isFloating"] = &QDockWidget::isFloating;
    mt["setAllowedAreas"] = &QDockWidget::setAllowedAreas;
    mt["setFeatures"] = &QDockWidget::setFeatures;
    mt["setFloating"] = &QDockWidget::setFloating;
    mt["setTitleBarWidget"] = &QDockWidget::setTitleBarWidget;
    mt["setWidget"] = &QDockWidget::setWidget;
    mt["titleBarWidget"] = &QDockWidget::titleBarWidget;
    mt["toggleViewAction"] = &QDockWidget::toggleViewAction;
    mt["widget"] = &QDockWidget::widget;
}

int QDockWidget_new(lua_State* const state)
{
    // QDockWidget(const QString & title, QWidget * parent = 0, Qt::WindowFlags flags = 0)
    // QDockWidget(QWidget * parent = 0, Qt::WindowFlags flags = 0)
    lua::make<QDockWidget>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QDockWidget(lua_State* const state)
{
    lua::thread env(state);

    env["QDockWidget"] = lua::value::table;
    env["QDockWidget"]["new"] = QDockWidget_new;
    auto t = env["QDockWidget"];

    // enum QDockWidget::DockWidgetFeature
    t["DockWidgetClosable"] = QDockWidget::DockWidgetClosable;
    t["DockWidgetMovable"] = QDockWidget::DockWidgetMovable;
    t["DockWidgetFloatable"] = QDockWidget::DockWidgetFloatable;
    t["DockWidgetVerticalTitleBar"] = QDockWidget::DockWidgetVerticalTitleBar;
    t["AllDockWidgetFeatures"] = QDockWidget::AllDockWidgetFeatures;
    t["NoDockWidgetFeatures"] = QDockWidget::NoDockWidgetFeatures;

    return 0;
}

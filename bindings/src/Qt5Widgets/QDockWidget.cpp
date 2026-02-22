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
    if (lua_gettop(state) == 0) {
        // QDockWidget()
        lua::push(state, new QDockWidget);
    } else if (lua::is_type<QString>(state, 1) || lua_isstring(state, 1)) {
        switch (lua_gettop(state)) {
            case 1:
                // QDockWidget(const QString & title)
                lua::push(state, new QDockWidget(lua::get<QString>(state, 1)));
                break;
            case 2:
                // QDockWidget(const QString & title, QWidget * parent)
                lua::push(state, new QDockWidget(
                    lua::get<QString>(state, 1),
                    lua::get<QWidget*>(state, 2)
                ));
                break;
            default:
                // QDockWidget(const QString & title, QWidget * parent, Qt::WindowFlags flags)
                lua::push(state, new QDockWidget(
                    lua::get<QString>(state, 1),
                    lua::get<QWidget*>(state, 2),
                    lua::get<Qt::WindowFlags>(state, 3)
                ));
                break;
        }
    } else {
        if (lua_gettop(state) == 1) {
            // QDockWidget(QWidget * parent)
            lua::push(state, new QDockWidget(
                lua::get<QWidget*>(state, 1)
            ));
        } else {
            // QDockWidget(QWidget * parent, Qt::WindowFlags flags)
            lua::push(state, new QDockWidget(
                lua::get<QWidget*>(state, 1),
                lua::get<Qt::WindowFlags>(state, 2)
            ));
        }
    }
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

#include "QTabWidget.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QTabWidget>

#include "QWidget.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Gui/QIcon.hpp"
#include "QTabBar.hpp"

// https://qt-project.org/doc/qt-5/qtabwidget.html

int QTabWidget_addTab(lua_State* const state)
{
    return 0;
}
int QTabWidget_cornerWidget(lua_State* const state)
{
    return 0;
}
int QTabWidget_insertTab(lua_State* const state)
{
    return 0;
}
int QTabWidget_setCornerWidget(lua_State* const state)
{
    return 0;
}

void lua::QTabWidget_metatable(const lua::index& mt)
{
    lua::QWidget_metatable(mt);

    mt["addTab"] = QTabWidget_addTab;
    mt["clear"] = &QTabWidget::clear;
    mt["cornerWidget"] = QTabWidget_cornerWidget;
    mt["count"] = &QTabWidget::count;
    mt["currentIndex"] = &QTabWidget::currentIndex;
    mt["currentWidget"] = &QTabWidget::currentWidget;
    mt["documentMode"] = &QTabWidget::documentMode;
    mt["elideMode"] = &QTabWidget::elideMode;
    mt["iconSize"] = &QTabWidget::iconSize;
    mt["indexOf"] = &QTabWidget::indexOf;
    mt["insertTab"] = QTabWidget_insertTab;
    mt["isMovable"] = &QTabWidget::isMovable;
    mt["isTabEnabled"] = &QTabWidget::isTabEnabled;
    mt["removeTab"] = &QTabWidget::removeTab;
    mt["setCornerWidget"] = QTabWidget_setCornerWidget;
    mt["setDocumentMode"] = &QTabWidget::setDocumentMode;
    mt["setElideMode"] = &QTabWidget::setElideMode;
    mt["setIconSize"] = &QTabWidget::setIconSize;
    mt["setMovable"] = &QTabWidget::setMovable;
    mt["setTabEnabled"] = &QTabWidget::setTabEnabled;
    mt["setTabIcon"] = &QTabWidget::setTabIcon;
    mt["setTabPosition"] = &QTabWidget::setTabPosition;
    mt["setTabShape"] = &QTabWidget::setTabShape;
    mt["setTabText"] = &QTabWidget::setTabText;
    mt["setTabToolTip"] = &QTabWidget::setTabToolTip;
    mt["setTabWhatsThis"] = &QTabWidget::setTabWhatsThis;
    mt["setTabsClosable"] = &QTabWidget::setTabsClosable;
    mt["setUsesScrollButtons"] = &QTabWidget::setUsesScrollButtons;
    mt["tabBar"] = &QTabWidget::tabBar;
    mt["tabIcon"] = &QTabWidget::tabIcon;
    mt["tabPosition"] = &QTabWidget::tabPosition;
    mt["tabShape"] = &QTabWidget::tabShape;
    mt["tabText"] = &QTabWidget::tabText;
    mt["tabToolTip"] = &QTabWidget::tabToolTip;
    mt["tabWhatsThis"] = &QTabWidget::tabWhatsThis;
    mt["tabsClosable"] = &QTabWidget::tabsClosable;
    mt["usesScrollButtons"] = &QTabWidget::usesScrollButtons;
    mt["widget"] = &QTabWidget::widget;
}

int QTabWidget_new(lua_State* const state)
{
    // QTabWidget(QWidget * parent = 0)
    lua::make<QTabWidget>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QTabWidget(lua_State* const state)
{
    lua::thread env(state);

    env["QTabWidget"] = lua::value::table;
    env["QTabWidget"]["new"] = QTabWidget_new;
    auto t = env["QTabWidget"];

    // enum QTabWidget::TabPosition
    t["North"] = QTabWidget::North;
    t["South"] = QTabWidget::South;
    t["West"] = QTabWidget::West;
    t["East"] = QTabWidget::East;

    // enum QTabWidget::TabShape
    t["Rounded"] = QTabWidget::Rounded;
    t["Triangular"] = QTabWidget::Triangular;

    return 0;
}

#include "QTabBar.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QTabBar>

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QSize.hpp"
#include "QWidget.hpp"
#include "../Qt5Gui/QIcon.hpp"
#include "../Qt5Gui/QColor.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QVariant.hpp"

int QTabBar_addTab(lua_State* const state)
{
    return 0;
}
int QTabBar_insertTab(lua_State* const state)
{
    return 0;
}

void lua::QTabBar_metatable(const lua::index& mt)
{
    lua::QWidget_metatable(mt);

    mt["addTab"] = QTabBar_addTab;
    mt["count"] = &QTabBar::count;
    mt["currentIndex"] = &QTabBar::currentIndex;
    mt["documentMode"] = &QTabBar::documentMode;
    mt["drawBase"] = &QTabBar::drawBase;
    mt["elideMode"] = &QTabBar::elideMode;
    mt["expanding"] = &QTabBar::expanding;
    mt["iconSize"] = &QTabBar::iconSize;
    mt["insertTab"] = QTabBar_insertTab;
    mt["isMovable"] = &QTabBar::isMovable;
    mt["isTabEnabled"] = &QTabBar::isTabEnabled;
    mt["moveTab"] = &QTabBar::moveTab;
    mt["removeTab"] = &QTabBar::removeTab;
    mt["selectionBehaviorOnRemove"] = &QTabBar::selectionBehaviorOnRemove;
    mt["setDocumentMode"] = &QTabBar::setDocumentMode;
    mt["setDrawBase"] = &QTabBar::setDrawBase;
    mt["setElideMode"] = &QTabBar::setElideMode;
    mt["setExpanding"] = &QTabBar::setExpanding;
    mt["setIconSize"] = &QTabBar::setIconSize;
    mt["setMovable"] = &QTabBar::setMovable;
    mt["setSelectionBehaviorOnRemove"] = &QTabBar::setSelectionBehaviorOnRemove;
    mt["setShape"] = &QTabBar::setShape;
    mt["setTabButton"] = &QTabBar::setTabButton;
    mt["setTabData"] = &QTabBar::setTabData;
    mt["setTabEnabled"] = &QTabBar::setTabEnabled;
    mt["setTabIcon"] = &QTabBar::setTabIcon;
    mt["setTabText"] = &QTabBar::setTabText;
    mt["setTabTextColor"] = &QTabBar::setTabTextColor;
    mt["setTabToolTip"] = &QTabBar::setTabToolTip;
    mt["setTabWhatsThis"] = &QTabBar::setTabWhatsThis;
    mt["setTabsClosable"] = &QTabBar::setTabsClosable;
    mt["setUsesScrollButtons"] = &QTabBar::setUsesScrollButtons;
    mt["shape"] = &QTabBar::shape;
    mt["tabAt"] = &QTabBar::tabAt;
    mt["tabButton"] = &QTabBar::tabButton;
    mt["tabData"] = &QTabBar::tabData;
    mt["tabIcon"] = &QTabBar::tabIcon;
    mt["tabRect"] = &QTabBar::tabRect;
    mt["tabText"] = &QTabBar::tabText;
    mt["tabTextColor"] = &QTabBar::tabTextColor;
    mt["tabToolTip"] = &QTabBar::tabToolTip;
    mt["tabWhatsThis"] = &QTabBar::tabWhatsThis;
    mt["tabsClosable"] = &QTabBar::tabsClosable;
    mt["usesScrollButtons"] = &QTabBar::usesScrollButtons;
}

int QTabBar_new(lua_State* const state)
{
    // QTabBar(QWidget * parent = 0)
    lua::make<QTabBar>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QTabBar(lua_State* const state)
{
    lua::thread env(state);

    env["QTabBar"] = lua::value::table;
    env["QTabBar"]["new"] = QTabBar_new;
    auto t = env["QTabBar"];

    // enum QTabBar::ButtonPosition
    t["LeftSide"] = QTabBar::LeftSide;
    t["RightSide"] = QTabBar::RightSide;

    // enum QTabBar::SelectionBehavior
    t["SelectRightTab"] = QTabBar::SelectRightTab;
    t["SelectPreviousTab"] = QTabBar::SelectPreviousTab;

    // enum QTabBar::Shape
    t["RoundedNorth"] = QTabBar::RoundedNorth;
    t["RoundedSouth"] = QTabBar::RoundedSouth;
    t["RoundedWest"] = QTabBar::RoundedWest;
    t["RoundedEast"] = QTabBar::RoundedEast;
    t["TriangularNorth"] = QTabBar::TriangularNorth;
    t["TriangularSouth"] = QTabBar::TriangularSouth;
    t["TriangularWest"] = QTabBar::TriangularWest;
    t["TriangularEast"] = QTabBar::TriangularEast;

    return 0;
}

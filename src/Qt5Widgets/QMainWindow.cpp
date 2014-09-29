#include "QMainWindow.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QMainWindow>

#include "../Qt5Core/QSize.hpp"
#include "QMenuBar.hpp"
#include "QWidget.hpp"
#include "QToolBar.hpp"
#include "../Qt5Core/Qt.hpp"
#include "QDockWidget.hpp"
#include "QStatusBar.hpp"
#include "QMenu.hpp"
#include "QTabWidget.hpp"
#include "../Qt5Core/QByteArray.hpp"
#include "../Qt5Core/QList.hpp"

// https://qt-project.org/doc/qt-5/qmainwindow.html

int QMainWindow_addDockWidget(lua_State* const state)
{
    return 0;
}
int QMainWindow_addToolBar(lua_State* const state)
{
    return 0;
}
int QMainWindow_addToolBarBreak(lua_State* const state)
{
    return 0;
}
int QMainWindow_insertToolBar(lua_State* const state)
{
    return 0;
}
int QMainWindow_restoreState(lua_State* const state)
{
    return 0;
}
int QMainWindow_saveState(lua_State* const state)
{
    return 0;
}

void lua::QMainWindow_metatable(const lua::index& mt)
{
    lua::QWidget_metatable(mt);

    mt["addDockWidget"] = QMainWindow_addDockWidget;
    mt["addToolBar"] = QMainWindow_addToolBar;
    mt["addToolBarBreak"] = QMainWindow_addToolBarBreak;
    mt["centralWidget"] = &QMainWindow::centralWidget;
    mt["corner"] = &QMainWindow::corner;
    mt["createPopupMenu"] = &QMainWindow::createPopupMenu;
    mt["dockOptions"] = &QMainWindow::dockOptions;
    mt["dockWidgetArea"] = &QMainWindow::dockWidgetArea;
    mt["documentMode"] = &QMainWindow::documentMode;
    mt["iconSize"] = &QMainWindow::iconSize;
    mt["insertToolBar"] = QMainWindow_insertToolBar;
    mt["isAnimated"] = &QMainWindow::isAnimated;
    mt["isDockNestingEnabled"] = &QMainWindow::isDockNestingEnabled;
    mt["menuBar"] = &QMainWindow::menuBar;
    mt["menuWidget"] = &QMainWindow::menuWidget;
    mt["removeDockWidget"] = &QMainWindow::removeDockWidget;
    mt["removeToolBar"] = &QMainWindow::removeToolBar;
    mt["removeToolBarBreak"] = &QMainWindow::removeToolBarBreak;
    mt["restoreDockWidget"] = &QMainWindow::restoreDockWidget;
    mt["restoreState"] = QMainWindow_restoreState;
    mt["saveState"] = QMainWindow_saveState;
    mt["setCentralWidget"] = &QMainWindow::setCentralWidget;
    mt["setCorner"] = &QMainWindow::setCorner;
    mt["setDockOptions"] = &QMainWindow::setDockOptions;
    mt["setDocumentMode"] = &QMainWindow::setDocumentMode;
    mt["setIconSize"] = &QMainWindow::setIconSize;
    mt["setMenuBar"] = &QMainWindow::setMenuBar;
    mt["setMenuWidget"] = &QMainWindow::setMenuWidget;
    mt["setStatusBar"] = &QMainWindow::setStatusBar;
    mt["setTabPosition"] = &QMainWindow::setTabPosition;
    mt["setTabShape"] = &QMainWindow::setTabShape;
    mt["setToolButtonStyle"] = &QMainWindow::setToolButtonStyle;
    mt["setUnifiedTitleAndToolBarOnMac"] = &QMainWindow::setUnifiedTitleAndToolBarOnMac;
    mt["splitDockWidget"] = &QMainWindow::splitDockWidget;
    mt["statusBar"] = &QMainWindow::statusBar;
    mt["tabPosition"] = &QMainWindow::tabPosition;
    mt["tabShape"] = &QMainWindow::tabShape;
    mt["tabifiedDockWidgets"] = &QMainWindow::tabifiedDockWidgets;
    mt["tabifyDockWidget"] = &QMainWindow::tabifyDockWidget;
    mt["takeCentralWidget"] = &QMainWindow::takeCentralWidget;
    mt["toolBarArea"] = &QMainWindow::toolBarArea;
    mt["toolBarBreak"] = &QMainWindow::toolBarBreak;
    mt["toolButtonStyle"] = &QMainWindow::toolButtonStyle;
    mt["unifiedTitleAndToolBarOnMac"] = &QMainWindow::unifiedTitleAndToolBarOnMac;
}

int QMainWindow_new(lua_State* const state)
{
    // QMainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0)
    lua::make<QMainWindow>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QMainWindow(lua_State* const state)
{
    lua::thread env(state);

    env["QMainWindow"] = lua::value::table;
    env["QMainWindow"]["new"] = QMainWindow_new;
    auto t = env["QMainWindow"];

    // enum QMainWindow::DockOption
    t["AnimatedDocks"] = QMainWindow::AnimatedDocks;
    t["AllowNestedDocks"] = QMainWindow::AllowNestedDocks;
    t["AllowTabbedDocks"] = QMainWindow::AllowTabbedDocks;
    t["ForceTabbedDocks"] = QMainWindow::ForceTabbedDocks;
    t["VerticalTabs"] = QMainWindow::VerticalTabs;

    return 0;
}

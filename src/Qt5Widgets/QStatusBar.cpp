#include "QStatusBar.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QStatusBar>

#include "QWidget.hpp"
#include "../Qt5Core/QString.hpp"

// https://qt-project.org/doc/qt-5/qstatusbar.html

int QStatusBar_addPermanentWidget(lua_State* const state)
{
    return 0;
}
int QStatusBar_insertPermanentWidget(lua_State* const state)
{
    return 0;
}
int QStatusBar_insertWidget(lua_State* const state)
{
    return 0;
}

void lua::QStatusBar_metatable(const lua::index& mt)
{
    lua::QWidget_metatable(mt);

    mt["addPermanentWidget"] = QStatusBar_addPermanentWidget;
    mt["addWidget"] = &QStatusBar::addWidget;
    mt["currentMessage"] = &QStatusBar::currentMessage;
    mt["insertPermanentWidget"] = QStatusBar_insertPermanentWidget;
    mt["insertWidget"] = QStatusBar_insertWidget;
    mt["isSizeGripEnabled"] = &QStatusBar::isSizeGripEnabled;
    mt["removeWidget"] = &QStatusBar::removeWidget;
    mt["setSizeGripEnabled"] = &QStatusBar::setSizeGripEnabled;
}

int QStatusBar_new(lua_State* const state)
{
    // QStatusBar(QWidget * parent = 0)
    lua::make<QStatusBar>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QStatusBar(lua_State* const state)
{
    lua::thread env(state);

    env["QStatusBar"] = lua::value::table;
    env["QStatusBar"]["new"] = QStatusBar_new;

    return 0;
}

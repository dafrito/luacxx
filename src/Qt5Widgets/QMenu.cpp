#include "QMenu.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QRect.hpp"
#include "QAction.hpp"
#include "../Qt5Gui/QIcon.hpp"

#include <QMenu>

int QMenu_addAction(lua_State* const state)
{
    return 0;
}
int QMenu_addMenu(lua_State* const state)
{
    return 0;
}
int QMenu_addSection(lua_State* const state)
{
    return 0;
}
int QMenu_exec(lua_State* const state)
{
    return 0;
}
int QMenu_insertSection(lua_State* const state)
{
    return 0;
}
int QMenu_popup(lua_State* const state)
{
    return 0;
}

void lua::QMenu_metatable(const lua::index& mt)
{
    mt["actionAt"] = &QMenu::actionAt;
    mt["actionGeometry"] = &QMenu::actionGeometry;
    mt["activeAction"] = &QMenu::activeAction;
    mt["addAction"] = QMenu_addAction;
    mt["addMenu"] = QMenu_addMenu;
    mt["addSection"] = QMenu_addSection;
    mt["addSeparator"] = &QMenu::addSeparator;
    mt["clear"] = &QMenu::clear;
    mt["defaultAction"] = &QMenu::defaultAction;
    mt["exec"] = QMenu_exec;
    mt["hideTearOffMenu"] = &QMenu::hideTearOffMenu;
    mt["icon"] = &QMenu::icon;
    mt["insertMenu"] = &QMenu::insertMenu;
    mt["insertSection"] = QMenu_insertSection;
    mt["insertSeparator"] = &QMenu::insertSeparator;
    mt["isEmpty"] = &QMenu::isEmpty;
    mt["isTearOffEnabled"] = &QMenu::isTearOffEnabled;
    mt["isTearOffMenuVisible"] = &QMenu::isTearOffMenuVisible;
    mt["menuAction"] = &QMenu::menuAction;
    mt["popup"] = QMenu_popup;
    mt["separatorsCollapsible"] = &QMenu::separatorsCollapsible;
    mt["setActiveAction"] = &QMenu::setActiveAction;
    // mt["setAsDockMenu"] = &QMenu::setAsDockMenu;
    mt["setDefaultAction"] = &QMenu::setDefaultAction;
    mt["setIcon"] = &QMenu::setIcon;
    mt["setSeparatorsCollapsible"] = &QMenu::setSeparatorsCollapsible;
    mt["setTearOffEnabled"] = &QMenu::setTearOffEnabled;
    mt["setTitle"] = &QMenu::setTitle;
    mt["setToolTipsVisible"] = &QMenu::setToolTipsVisible;
    mt["title"] = &QMenu::title;
    mt["toolTipsVisible"] = &QMenu::toolTipsVisible;
}

int QMenu_new(lua_State* const state)
{
    /*
     * QMenu(QWidget * parent = 0)
     * QMenu(const QString & title, QWidget * parent = 0)
     */
    lua::make<QMenu>(state, nullptr);
    return 1;
}

int luaopen_Qt5Widgets_QMenu(lua_State* const state)
{
    lua::thread env(state);

    env["QMenu"] = lua::value::table;
    env["QMenu"]["new"] = QMenu_new;

    return 0;
}

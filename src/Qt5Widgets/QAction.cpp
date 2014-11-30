#include "QAction.hpp"

#include "../algorithm.hpp"
#include "../reference.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QWidget.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Gui/QKeySequence.hpp"
#include "../Qt5Gui/QFont.hpp"
#include "../Qt5Gui/QIcon.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "QMenu.hpp"
#include "QActionGroup.hpp"
#include "../Qt5Core/QObject.hpp"
#include "QGraphicsWidget.hpp"
#include "../Qt5Core/QVariant.hpp"

// https://qt-project.org/doc/qt-5/qaction.html

int QAction_setShortcuts(lua_State* const state)
{
    auto self = lua::get<QAction*>(state, 1);

    // void     setShortcuts(const QList<QKeySequence> & shortcuts)
    // void     setShortcuts(QKeySequence::StandardKey key)
    if (lua::is_type<QList<QKeySequence>>(state, 2)) {
        self->setShortcuts(
            lua::get<const QList<QKeySequence>&>(state, 2)
        );
    } else {
        self->setShortcuts(
            lua::get<QKeySequence::StandardKey>(state, 2)
        );
    }

    return 0;
}

int QAction_showStatusText(lua_State* const state)
{
    auto self = lua::get<QAction*>(state, 1);

    // bool    showStatusText(QWidget * widget = 0)
    if (lua_gettop(state) == 1) {
        lua::push(state, self->showStatusText());
    } else {
        lua::push(state, self->showStatusText(
            lua::get<QWidget*>(state, 2)
        ));
    }

    return 1;
}

void lua::QAction_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["actionGroup"] = &QAction::actionGroup;
    mt["activate"] = &QAction::activate;
    mt["associatedGraphicsWidgets"] = &QAction::associatedGraphicsWidgets;
    mt["associatedWidgets"] = &QAction::associatedWidgets;
    mt["autoRepeat"] = &QAction::autoRepeat;
    mt["data"] = &QAction::data;
    mt["font"] = &QAction::font;
    mt["icon"] = &QAction::icon;
    mt["iconText"] = &QAction::iconText;
    mt["isCheckable"] = &QAction::isCheckable;
    mt["isChecked"] = &QAction::isChecked;
    mt["isEnabled"] = &QAction::isEnabled;
    mt["isIconVisibleInMenu"] = &QAction::isIconVisibleInMenu;
    mt["isSeparator"] = &QAction::isSeparator;
    mt["isVisible"] = &QAction::isVisible;
    mt["menu"] = &QAction::menu;
    mt["menuRole"] = &QAction::menuRole;
    mt["parentWidget"] = &QAction::parentWidget;
    mt["priority"] = &QAction::priority;
    mt["setActionGroup"] = &QAction::setActionGroup;
    mt["setAutoRepeat"] = &QAction::setAutoRepeat;
    mt["setCheckable"] = &QAction::setCheckable;
    mt["setData"] = &QAction::setData;
    mt["setFont"] = &QAction::setFont;
    mt["setIcon"] = &QAction::setIcon;
    mt["setIconText"] = &QAction::setIconText;
    mt["setIconVisibleInMenu"] = &QAction::setIconVisibleInMenu;
    mt["setMenu"] = &QAction::setMenu;
    mt["setMenuRole"] = &QAction::setMenuRole;
    mt["setPriority"] = &QAction::setPriority;
    mt["setSeparator"] = &QAction::setSeparator;
    mt["setShortcut"] = &QAction::setShortcut;
    mt["setShortcutContext"] = &QAction::setShortcutContext;
    mt["setShortcuts"] = QAction_setShortcuts;
    mt["setStatusTip"] = &QAction::setStatusTip;
    mt["setText"] = &QAction::setText;
    mt["setToolTip"] = &QAction::setToolTip;
    mt["setWhatsThis"] = &QAction::setWhatsThis;
    mt["shortcut"] = &QAction::shortcut;
    mt["shortcutContext"] = &QAction::shortcutContext;
    mt["shortcuts"] = &QAction::shortcuts;
    mt["showStatusText"] = QAction_showStatusText;
    mt["statusTip"] = &QAction::statusTip;
    mt["text"] = &QAction::text;
    mt["toolTip"] = &QAction::toolTip;
    mt["whatsThis"] = &QAction::whatsThis;
}

int QAction_new(lua_State* const state)
{
    if (lua::is_type<QIcon>(state, 1)) {
        // QAction(const QIcon & icon, const QString & text, QObject * parent)
        lua::push(state, new QAction(
            lua::get<const QIcon&>(state, 1),
            lua::get<QString>(state, 2),
            lua::get<QObject*>(state, 3)
        ));
    } else if (lua::is_type<QString>(state, 1) || lua_isstring(state, 1)) {
        // QAction(const QString & text, QObject * parent)
        lua::push(state, new QAction(
            lua::get<QString>(state, 1),
            lua::get<QObject*>(state, 2)
        ));
    } else {
        // QAction(QObject * parent)
        lua::push(state, new QAction(
            lua::get<QObject*>(state, 1)
        ));
    }
    return 1;
}

int luaopen_Qt5Widgets_QAction(lua_State* const state)
{
    lua::thread env(state);

    env["QAction"] = lua::value::table;
    env["QAction"]["new"] = QAction_new;
    auto t = env["QAction"];

    // enum QAction::ActionEvent
    t["Trigger"] = QAction::Trigger;
    t["Hover"] = QAction::Hover;

    // enum QAction::MenuRole
    t["NoRole"] = QAction::NoRole;
    t["TextHeuristicRole"] = QAction::TextHeuristicRole;
    t["ApplicationSpecificRole"] = QAction::ApplicationSpecificRole;
    t["AboutQtRole"] = QAction::AboutQtRole;
    t["AboutRole"] = QAction::AboutRole;
    t["PreferencesRole"] = QAction::PreferencesRole;
    t["QuitRole"] = QAction::QuitRole;

    // enum QAction::Priority
    t["LowPriority"] = QAction::LowPriority;
    t["NormalPriority"] = QAction::NormalPriority;
    t["HighPriority"] = QAction::HighPriority;

    return 0;
}


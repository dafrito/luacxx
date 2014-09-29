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

// https://qt-project.org/doc/qt-5/qaction.html

int QAction_setShortcuts(lua_State* const state)
{
    return 0;
}

int QAction_showStatusText(lua_State* const state)
{
    return 0;
}

void lua::QAction_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);

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
    // QAction(QObject * parent)
    // QAction(const QString & text, QObject * parent)
    // QAction(const QIcon & icon, const QString & text, QObject * parent)
    lua::make<QAction>(state, nullptr);
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


#include "QAbstractButton.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Gui/QIcon.hpp"
#include "../Qt5Gui/QKeySequence.hpp"
#include "../Qt5Core/QSize.hpp"
#include "QWidget.hpp"

namespace lua {

void QAbstractButton_metatable(lua_State* const state, const int pos)
{
    lua::QWidget_metatable(state, pos);

    lua::index mt(state, pos);
    mt["autoExclusive"] = &QAbstractButton::autoExclusive;
    mt["autoRepeat"] = &QAbstractButton::autoRepeat;
    mt["autoRepeatDelay"] = &QAbstractButton::autoRepeatDelay;
    mt["autoRepeatInterval"] = &QAbstractButton::autoRepeatInterval;
    // QButtonGroup *  group() const
    mt["icon"] = &QAbstractButton::icon;
    mt["iconSize"] = &QAbstractButton::iconSize;
    mt["isCheckable"] = &QAbstractButton::isCheckable;
    mt["isChecked"] = &QAbstractButton::isChecked;
    mt["isDown"] = &QAbstractButton::isDown;
    mt["setAutoExclusive"] = &QAbstractButton::setAutoExclusive;
    mt["setAutoRepeat"] = &QAbstractButton::setAutoRepeat;
    mt["setAutoRepeatDelay"] = &QAbstractButton::setAutoRepeatDelay;
    mt["setAutoRepeatInterval"] = &QAbstractButton::setAutoRepeatInterval;
    mt["setCheckable"] = &QAbstractButton::setCheckable;
    mt["setDown"] = &QAbstractButton::setDown;
    mt["setIcon"] = &QAbstractButton::setIcon;
    mt["setShortcut"] = &QAbstractButton::setShortcut;
    mt["setText"] = &QAbstractButton::setText;
    mt["shortcut"] = &QAbstractButton::shortcut;
    mt["text"] = &QAbstractButton::text;
}

} // namespace lua

int luaopen_Qt5Widgets_QAbstractButton(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractButton"] = lua::value::table;
    auto t = env["QAbstractButton"];

    return 0;
}

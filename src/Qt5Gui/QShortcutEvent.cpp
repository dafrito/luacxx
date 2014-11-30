#include "QShortcutEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QKeySequence.hpp"

// http://qt-project.org/doc/qt-5/qshortcutevent.html

namespace lua {

void QShortcutEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["isAmbiguous"] = &QShortcutEvent::isAmbiguous;
    mt["key"] = &QShortcutEvent::key;
    mt["shortcutId"] = &QShortcutEvent::shortcutId;
}

} // namespace lua

int QShortcutEvent_new(lua_State* const state)
{
    if (lua_gettop(state) == 2) {
        lua::make<QShortcutEvent>(state,
            lua::get<const QKeySequence&>(state, 1),
            lua::get<int>(state, 2)
        );
    } else {
        lua::make<QShortcutEvent>(state,
            lua::get<const QKeySequence&>(state, 1),
            lua::get<int>(state, 2),
            lua::get<bool>(state, 3)
        );
    }

    return 1;
}

int luaopen_Qt5Gui_QShortcutEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QShortcutEvent"] = lua::value::table;
    env["QShortcutEvent"]["new"] = QShortcutEvent_new;
    auto t = env["QShortcutEvent"];

    return 0;
}

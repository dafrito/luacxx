#include "QActionEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QAction.hpp"

// http://qt-project.org/doc/qt-5/qactionevent.html

namespace lua {

void QActionEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["action"] = &QActionEvent::action;
    mt["before"] = &QActionEvent::before;
}

} // namespace lua

int QActionEvent_new(lua_State* const state)
{
    if (lua_gettop(state) == 2) {
        lua::make<QActionEvent>(state,
            lua::get<int>(state, 1),
            lua::get<QAction*>(state, 2)
        );
    } else {
        lua::make<QActionEvent>(state,
            lua::get<int>(state, 1),
            lua::get<QAction*>(state, 2),
            lua::get<QAction*>(state, 3)
        );
    }

    return 1;
}

int luaopen_Qt5Gui_QActionEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QActionEvent"] = lua::value::table;
    env["QActionEvent"]["new"] = QActionEvent_new;
    auto t = env["QActionEvent"];

    return 0;
}

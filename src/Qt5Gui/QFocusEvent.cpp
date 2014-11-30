#include "QFocusEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"

// http://qt-project.org/doc/qt-5/qfocusevent.html

namespace lua {

void QFocusEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["gotFocus"] = &QFocusEvent::gotFocus;
    mt["lostFocus"] = &QFocusEvent::lostFocus;
    mt["reason"] = &QFocusEvent::reason;
}

} // namespace lua

int QFocusEvent_new(lua_State* const state)
{
    // QFocusEvent(Type type, Qt::FocusReason reason = Qt::OtherFocusReason)
    if (lua_gettop(state) == 1) {
        lua::make<QFocusEvent>(state,
            lua::get<QEvent::Type>(state, 1)
        );
    } else {
        lua::make<QFocusEvent>(state,
            lua::get<QEvent::Type>(state, 1),
            lua::get<Qt::FocusReason>(state, 2)
        );
    }

    return 1;
}

int luaopen_Qt5Gui_QFocusEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QFocusEvent"] = lua::value::table;
    env["QFocusEvent"]["new"] = QFocusEvent_new;
    auto t = env["QFocusEvent"];

    return 0;
}

#include "QWhatsThisClickedEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"

// http://qt-project.org/doc/qt-5/qwhatsthisclickedevent.html

namespace lua {

void QWhatsThisClickedEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["href"] = &QWhatsThisClickedEvent::href;
}

} // namespace lua

int QWhatsThisClickedEvent_new(lua_State* const state)
{
    lua::make<QWhatsThisClickedEvent>(state,
        lua::get<QString>(state, 1)
    );

    return 1;
}

int luaopen_Qt5Gui_QWhatsThisClickedEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QWhatsThisClickedEvent"] = lua::value::table;
    env["QWhatsThisClickedEvent"]["new"] = QWhatsThisClickedEvent_new;
    auto t = env["QWhatsThisClickedEvent"];

    return 0;
}

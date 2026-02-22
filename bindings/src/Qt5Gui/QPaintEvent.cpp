#include "QPaintEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QRect.hpp"
#include "../Qt5Gui/QRegion.hpp"

// http://qt-project.org/doc/qt-5/qpaintevent.html

namespace lua {

void QPaintEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["rect"] = &QPaintEvent::rect;
    mt["region"] = &QPaintEvent::region;
}

} // namespace lua

int QPaintEvent_new(lua_State* const state)
{
    if (lua::is_type<QRect>(state, 1)) {
        lua::make<QPaintEvent>(state, lua::get<const QRect&>(state, 1));
    } else {
        lua::make<QPaintEvent>(state, lua::get<const QRegion&>(state, 1));
    }

    return 1;
}

int luaopen_Qt5Gui_QPaintEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QPaintEvent"] = lua::value::table;
    env["QPaintEvent"]["new"] = QPaintEvent_new;
    auto t = env["QPaintEvent"];

    return 0;
}

#include "QHelpEvent.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QEvent.hpp"

namespace lua {

void QHelpEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos, nullptr);

    lua::index mt(state, pos);
    mt["globalPos"] = &QHelpEvent::globalPos;
    mt["globalX"] = &QHelpEvent::globalX;
    mt["globalY"] = &QHelpEvent::globalY;
    mt["pos"] = &QHelpEvent::pos;
    mt["x"] = &QHelpEvent::x;
    mt["y"] = &QHelpEvent::y;
}

} // namespace lua

int QHelpEvent_new(lua_State* const state)
{
    lua::make<QHelpEvent>(state,
        lua::get<QEvent::Type>(state, 1),
        lua::get<const QPoint&>(state, 2),
        lua::get<const QPoint&>(state, 3)
    );

    return 1;
}

int luaopen_luacxx_QHelpEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QHelpEvent"] = lua::value::table;
    env["QHelpEvent"]["new"] = QHelpEvent_new;
    auto t = env["QHelpEvent"];

    return 0;
}

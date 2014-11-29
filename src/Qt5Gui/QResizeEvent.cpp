#include "QResizeEvent.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QSize.hpp"

namespace lua {

void QResizeEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["oldSize"] = &QResizeEvent::oldSize;
    mt["size"] = &QResizeEvent::size;
}

} // namespace lua

int QResizeEvent_new(lua_State* const state)
{
    lua::make<QResizeEvent>(state,
        lua::get<const QSize&>(state, 1),
        lua::get<const QSize&>(state, 2)
    );

    return 1;
}

int luaopen_Qt5Gui_QResizeEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QResizeEvent"] = lua::value::table;
    env["QResizeEvent"]["new"] = QResizeEvent_new;
    auto t = env["QResizeEvent"];

    return 0;
}

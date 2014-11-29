#include "QExposeEvent.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QRegion.hpp"

namespace lua {

void QExposeEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["region"] = &QExposeEvent::region;
}

} // namespace lua

int QExposeEvent_new(lua_State* const state)
{
    lua::make<QExposeEvent>(state,
        lua::get<const QRegion&>(state, 1)
    );

    return 1;
}

int luaopen_luacxx_QExposeEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QExposeEvent"] = lua::value::table;
    env["QExposeEvent"]["new"] = QExposeEvent_new;
    auto t = env["QExposeEvent"];

    return 0;
}

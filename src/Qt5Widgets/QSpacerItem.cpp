#include "QSpacerItem.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QSizePolicy.hpp"
#include "QLayoutItem.hpp"

namespace lua {

void QSpacerItem_metatable(lua_State* const state, const int pos)
{
    lua::QLayoutItem_metatable(state, pos);
    lua::index mt(state, pos);
}

} // namespace lua

int QSpacerItem_new(lua_State* const state)
{
    switch (lua::size(state)) {
    case 2:
        lua::make<QSpacerItem>(state,
            lua::get<int>(state, 1),
            lua::get<int>(state, 2)
        );
        break;
    case 3:
        lua::make<QSpacerItem>(state,
            lua::get<int>(state, 1),
            lua::get<int>(state, 2),
            lua::get<QSizePolicy::Policy>(state, 3)
        );
        break;
    case 4:
    default:
        lua::make<QSpacerItem>(state,
            lua::get<int>(state, 1),
            lua::get<int>(state, 2),
            lua::get<QSizePolicy::Policy>(state, 3),
            lua::get<QSizePolicy::Policy>(state, 4)
        );
        break;
    }
    return 1;
}

int luaopen_Qt5Widgets_QSpacerItem(lua_State* const state)
{
    lua::thread env(state);

    env["QSpacerItem"] = lua::value::table;
    env["QSpacerItem"]["new"] = QSpacerItem_new;
    auto t = env["QSpacerItem"];

    return 0;
}

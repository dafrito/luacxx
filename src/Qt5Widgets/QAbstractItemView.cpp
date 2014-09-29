#include "QAbstractItemView.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QAbstractItemView>

void lua::QAbstractItemView_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int luaopen_Qt5Widgets_QAbstractItemView(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractItemView"] = lua::value::table;
    auto t = env["QAbstractItemView"];

    return 0;
}

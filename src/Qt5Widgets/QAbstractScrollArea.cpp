#include "QAbstractScrollArea.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QAbstractScrollArea>

void lua::QAbstractScrollArea_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int luaopen_Qt5Widgets_QAbstractScrollArea(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractScrollArea"] = lua::value::table;

    return 0;
}

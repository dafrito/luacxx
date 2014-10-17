#include "QAbstractScrollArea.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QAbstractScrollArea>

#include "QFrame.hpp"

void lua::QAbstractScrollArea_metatable(lua_State* const state, const int pos)
{
    lua::QFrame_metatable(state, pos);
}

int luaopen_Qt5Widgets_QAbstractScrollArea(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractScrollArea"] = lua::value::table;

    return 0;
}

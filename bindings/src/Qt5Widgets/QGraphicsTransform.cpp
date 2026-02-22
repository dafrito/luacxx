#include "QGraphicsTransform.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QGraphicsTransform>

void lua::QGraphicsTransform_metatable(lua_State* const state, const int pos)
{
    // TODO Set up metatable methods for this class
}

int luaopen_Qt5Widgets_QGraphicsTransform(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsTransform"] = lua::value::table;
    auto t = env["QGraphicsTransform"];

    return 0;
}

#include "QGraphicsItemGroup.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QGraphicsItemGroup>

void lua::QGraphicsItemGroup_metatable(lua_State* const state, const int pos)
{
    // TODO Set up metatable methods for this class
}

int QGraphicsItemGroup_new(lua_State* const state)
{
    lua::make<QGraphicsItemGroup>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsItemGroup(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsItemGroup"] = lua::value::table;
    env["QGraphicsItemGroup"]["new"] = QGraphicsItemGroup_new;
    auto t = env["QGraphicsItemGroup"];

    return 0;
}

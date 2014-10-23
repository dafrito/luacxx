#include "QGraphicsLayout.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QGraphicsLayoutItem.hpp"
#include "../Qt5Core/QEvent.hpp"

namespace lua {

void QGraphicsLayout_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["activate"] = &QGraphicsLayout::activate;
    mt["count"] = &QGraphicsLayout::count;
    mt["invalidate"] = &QGraphicsLayout::invalidate;
    mt["isActivated"] = &QGraphicsLayout::isActivated;
    mt["itemAt"] = &QGraphicsLayout::itemAt;
    mt["removeAt"] = &QGraphicsLayout::removeAt;
    mt["setContentsMargins"] = &QGraphicsLayout::setContentsMargins;
    mt["widgetEvent"] = &QGraphicsLayout::widgetEvent;
}

} // namespace lua

int luaopen_luacxx_QGraphicsLayout(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsLayout"] = lua::value::table;
    auto t = env["QGraphicsLayout"];

    return 0;
}

#include "QGraphicsProxyWidget.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QGraphicsProxyWidget>

void lua::QGraphicsProxyWidget_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int QGraphicsProxyWidget_new(lua_State* const state)
{
    lua::make<QGraphicsProxyWidget>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsProxyWidget(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsProxyWidget"] = lua::value::table;
    env["QGraphicsProxyWidget"]["new"] = QGraphicsProxyWidget_new;
    auto t = env["QGraphicsProxyWidget"];

    return 0;
}

#include "QScrollBar.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QAbstractSlider.hpp"
#include "../Qt5Core/Qt.hpp"

namespace lua {

void QScrollBar_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractSlider_metatable(state, pos);
}

} // namespace lua

int QScrollBar_new(lua_State* const state)
{
    if (lua_gettop(state) == 1) {
        lua::make<QScrollBar>(state, lua::get<Qt::Orientation>(state, 1));
    } else {
        lua::make<QScrollBar>(state);
    }

    return 1;
}

int luaopen_luacxx_QScrollBar(lua_State* const state)
{
    lua::thread env(state);

    env["QScrollBar"] = lua::value::table;
    env["QScrollBar"]["new"] = QScrollBar_new;
    auto t = env["QScrollBar"];

    return 0;
}

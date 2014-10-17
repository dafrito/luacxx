#include "QMargins.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QMargins>

void lua::QMargins_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["bottom"] = &QMargins::bottom;
    mt["isNull"] = &QMargins::isNull;
    mt["left"] = &QMargins::left;
    mt["right"] = &QMargins::right;
    mt["setBottom"] = &QMargins::setBottom;
    mt["setLeft"] = &QMargins::setLeft;
    mt["setRight"] = &QMargins::setRight;
    mt["setTop"] = &QMargins::setTop;
    mt["top"] = &QMargins::top;
}

int QMargins_new(lua_State* const state)
{
    // TODO Set up object-specific methods
    // QMargins()
    // QMargins(int left, int top, int right, int bottom)
    lua::make<QMargins>(state);

    return 1;
}

int luaopen_luacxx_QMargins(lua_State* const state)
{
    lua::thread env(state);

    env["QMargins"] = lua::value::table;
    env["QMargins"]["new"] = QMargins_new;

    return 0;
}

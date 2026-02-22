#include "QBitmap.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QPixmap.hpp"

int QBitmap_transformed(lua_State* const state)
{
    return 0;
}

void lua::QBitmap_metatable(lua_State* const state, const int pos)
{
    lua::QPixmap_metatable(state, pos);

    lua::index mt(state, pos);
    mt["clear"] = &QBitmap::clear;
    mt["swap"] = &QBitmap::swap;
    mt["transformed"] = QBitmap_transformed;
}

int QBitmap_new(lua_State* const state)
{
    lua::make<QBitmap>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Gui_QBitmap(lua_State* const state)
{
    lua::thread env(state);

    env["QBitmap"] = lua::value::table;
    env["QBitmap"]["new"] = QBitmap_new;

    return 0;
}

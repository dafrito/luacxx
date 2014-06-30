#include "QBitmap.hpp"
#include "../luacxx/type/function.hpp"
#include "../luacxx/thread.hpp"
#include "QPixmap.hpp"

#include <QBitmap>

int QBitmap_transformed(lua_State* const state)
{
    return 0;
}

void lua::QBitmap_metatable(const lua::index& mt)
{
    lua::QPixmap_metatable(mt);

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

int luaopen_luacxx_QBitmap(lua_State* const state)
{
    lua::thread env(state);

    env["QBitmap"] = lua::value::table;
    env["QBitmap"]["new"] = QBitmap_new;

    return 0;
}

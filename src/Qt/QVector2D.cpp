#include "QVector2D.hpp"
#include "../lua-cxx/type/function.hpp"
#include "../lua-cxx/thread.hpp"

#include <QVector2D>

void lua::QVector2D_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int QVector2D_new(lua_State* const state)
{
    lua::make<QVector2D>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QVector2D(lua_State* const state)
{
    lua::thread env(state);

    env["QVector2D"] = lua::value::table;
    env["QVector2D"]["new"] = QVector2D_new;

    return 0;
}

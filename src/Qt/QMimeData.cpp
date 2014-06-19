#include "QMimeData.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QMimeData>

void lua::QMimeData_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int QMimeData_new(lua_State* const state)
{
    lua::make<QMimeData>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QMimeData(lua_State* const state)
{
    lua::thread env(state);

    env["QMimeData"] = lua::value::table;
    env["QMimeData"]["new"] = QMimeData_new;

    return 0;
}

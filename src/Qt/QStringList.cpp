#include "QStringList.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QStringList>

void lua::QStringList_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int QStringList_new(lua_State* const state)
{
    lua::make<QStringList>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QStringList(lua_State* const state)
{
    lua::thread env(state);

    env["QStringList"] = lua::value::table;
    env["QStringList"]["new"] = QStringList_new;

    return 0;
}

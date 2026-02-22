#include "QStringList.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QList.hpp"

void lua::QStringList_metatable(lua_State* const state, const int mt)
{
    lua::QList_metatable<QString>(state, mt);
}

int QStringList_new(lua_State* const state)
{
    lua::make<QStringList>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Core_QStringList(lua_State* const state)
{
    lua::thread env(state);

    env["QStringList"] = lua::value::table;
    env["QStringList"]["new"] = QStringList_new;

    return 0;
}

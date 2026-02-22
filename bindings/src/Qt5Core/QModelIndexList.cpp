#include "QModelIndexList.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QList.hpp"
#include "QModelIndex.hpp"

namespace lua {

void QModelIndexList_metatable(lua_State* const state, const int pos)
{
    lua::QList_metatable<QModelIndex>(state, pos);
}

} // namespace lua

int QModelIndexList_new(lua_State* const state)
{
    lua::make<QModelIndexList>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Core_QModelIndexList(lua_State* const state)
{
    lua::thread env(state);

    env["QModelIndexList"] = lua::value::table;
    env["QModelIndexList"]["new"] = QModelIndexList_new;
    auto t = env["QModelIndexList"];

    return 0;
}

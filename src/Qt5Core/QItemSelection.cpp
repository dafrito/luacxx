#include "QItemSelection.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QModelIndex.hpp"
#include "QModelIndexList.hpp"
#include "QItemSelectionModel.hpp"
#include "QItemSelectionRange.hpp"
#include "QFlags.hpp"

namespace lua {

void QItemSelection_metatable(lua_State* const state, const int pos)
{
    lua::QList_metatable<QItemSelection>(state, pos);

    lua::index mt(state, pos);
    mt["contains"] = &QItemSelection::contains;
    mt["indexes"] = &QItemSelection::indexes;
    mt["merge"] = &QItemSelection::merge;
    mt["select"] = &QItemSelection::select;
}

} // namespace lua

int QItemSelection_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::make<QItemSelection>(state);
    } else {
        lua::make<QItemSelection>(state,
            lua::get<const QModelIndex&>(state, 1),
            lua::get<const QModelIndex&>(state, 2)
        );
    }

    return 1;
}

int static_QItemSelection_split(lua_State* const state)
{
    if (lua_gettop(state) == 2) {
        QItemSelection::split(
            lua::get<const QItemSelectionRange&>(state, 1),
            lua::get<const QItemSelectionRange&>(state, 2),
            lua::get<QItemSelection*>(state, 3)
        );
        return 0;
    }

    auto selection = lua::make<QItemSelection>(state);
    QItemSelection::split(
        lua::get<const QItemSelectionRange&>(state, 1),
        lua::get<const QItemSelectionRange&>(state, 2),
        selection
    );

    return 1;
}

int luaopen_Qt5Core_QItemSelection(lua_State* const state)
{
    lua::thread env(state);

    env["QItemSelection"] = lua::value::table;
    env["QItemSelection"]["new"] = QItemSelection_new;
    auto t = env["QItemSelection"];

    t["split"] = static_QItemSelection_split;

    return 0;
}

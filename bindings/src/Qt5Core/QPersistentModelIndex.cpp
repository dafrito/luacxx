#include "QPersistentModelIndex.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QModelIndex.hpp"
#include "Qt.hpp"
#include "QAbstractItemModel.hpp"
#include "QVariant.hpp"
#include "QFlags.hpp"

int QPersistentModelIndex_data(lua_State* const state)
{
    auto self = lua::get<QPersistentModelIndex*>(state, 1);

    // QVariant  data(int role = Qt::DisplayRole) const
    if (lua_gettop(state) == 1) {
        lua::push(state, self->data());
    } else {
        lua::push(state, self->data(
            lua::get<int>(state, 1)
        ));
    }

    return 1;
}

namespace lua {

void QPersistentModelIndex_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["child"] = &QPersistentModelIndex::child;
    mt["column"] = &QPersistentModelIndex::column;
    mt["data"] = QPersistentModelIndex_data;
    mt["flags"] = &QPersistentModelIndex::flags;
    mt["isValid"] = &QPersistentModelIndex::isValid;
    mt["model"] = &QPersistentModelIndex::model;
    mt["parent"] = &QPersistentModelIndex::parent;
    mt["row"] = &QPersistentModelIndex::row;
    mt["sibling"] = &QPersistentModelIndex::sibling;
    mt["swap"] = &QPersistentModelIndex::swap;
}

} // namespace lua

int QPersistentModelIndex_new(lua_State* const state)
{
    if (lua::is_type<QModelIndex>(state, 1)) {
        // QPersistentModelIndex(const QModelIndex & index)
        lua::make<QPersistentModelIndex>(state,
            lua::get<const QModelIndex&>(state, 1)
        );
    } else {
        // QPersistentModelIndex(const QPersistentModelIndex & other)
        lua::make<QPersistentModelIndex>(state,
            lua::get<const QPersistentModelIndex&>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Core_QPersistentModelIndex(lua_State* const state)
{
    lua::thread env(state);

    env["QPersistentModelIndex"] = lua::value::table;
    env["QPersistentModelIndex"]["new"] = QPersistentModelIndex_new;
    auto t = env["QPersistentModelIndex"];

    return 0;
}

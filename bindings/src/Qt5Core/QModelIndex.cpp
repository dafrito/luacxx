#include "QModelIndex.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QModelIndex>

#include "QVariant.hpp"
#include "Qt.hpp"
#include "QFlags.hpp"
#include "QAbstractItemModel.hpp"

int QModelIndex_data(lua_State* const state)
{
    return 0;
}

void lua::QModelIndex_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["child"] = &QModelIndex::child;
    mt["column"] = &QModelIndex::column;
    mt["data"] = QModelIndex_data;
    mt["flags"] = &QModelIndex::flags;
    mt["internalId"] = &QModelIndex::internalId;
    mt["internalPointer"] = &QModelIndex::internalPointer;
    mt["isValid"] = &QModelIndex::isValid;
    mt["model"] = &QModelIndex::model;
    mt["parent"] = &QModelIndex::parent;
    mt["row"] = &QModelIndex::row;
    mt["sibling"] = &QModelIndex::sibling;
}

int QModelIndex_new(lua_State* const state)
{
    // QModelIndex()
    lua::make<QModelIndex>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Core_QModelIndex(lua_State* const state)
{
    lua::thread env(state);

    env["QModelIndex"] = lua::value::table;
    env["QModelIndex"]["new"] = QModelIndex_new;
    auto t = env["QModelIndex"];

    return 0;
}

#include "QAbstractItemModel.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QAbstractItemModel>

#include "QModelIndex.hpp"
#include "QModelIndexList.hpp"
#include "QMimeData.hpp"
#include "Qt.hpp"
#include "QMap.hpp"
#include "QHash.hpp"
#include "QVariant.hpp"
#include "QStringList.hpp"
#include "QByteArray.hpp"
#include "QFlags.hpp"
#include "QSize.hpp"

int QAbstractItemModel_columnCount(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual int columnCount(const QModelIndex & parent = QModelIndex()) const = 0
    if (lua_gettop(state) == 1) {
        lua::push(state, self->columnCount());
    } else {
        lua::push(state, self->columnCount(
            lua::get<const QModelIndex&>(state, 2)
        ));
    }

    return 1;
}

int QAbstractItemModel_data(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const = 0
    if (lua_gettop(state) == 2) {
        lua::push(state, self->data(
            lua::get<const QModelIndex&>(state, 2)
        ));
    } else {
        lua::push(state, self->data(
            lua::get<const QModelIndex&>(state, 2),
            lua::get<int>(state, 3)
        ));
    }

    return 1;
}

int QAbstractItemModel_hasChildren(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual bool     hasChildren(const QModelIndex & parent = QModelIndex()) const
    if (lua_gettop(state) == 1) {
        lua::push(state, self->hasChildren());
    } else {
        lua::push(state, self->hasChildren(
            lua::get<const QModelIndex&>(state, 2)
        ));
    }
    return 1;
}

int QAbstractItemModel_hasIndex(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // bool     hasIndex(int row, int column, const QModelIndex & parent = QModelIndex()) const
    if (lua_gettop(state) == 3) {
        lua::push(state, self->hasIndex(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        ));
    } else {
        lua::push(state, self->hasIndex(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QModelIndex&>(state, 4)
        ));
    }

    return 1;
}

int QAbstractItemModel_headerData(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    if (lua_gettop(state) == 3) {
        lua::push(state, self->headerData(
            lua::get<int>(state, 2),
            lua::get<Qt::Orientation>(state, 3)
        ));
    } else {
        lua::push(state, self->headerData(
            lua::get<int>(state, 2),
            lua::get<Qt::Orientation>(state, 3),
            lua::get<int>(state, 4)
        ));
    }

    return 1;
}

int QAbstractItemModel_index(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual QModelIndex  index(int row, int column, const QModelIndex & parent = QModelIndex()) const = 0
    if (lua_gettop(state) == 3) {
        lua::push(state, self->index(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        ));
    } else {
        lua::push(state, self->index(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QModelIndex&>(state, 4)
        ));
    }

    return 1;
}

int QAbstractItemModel_insertColumn(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // bool insertColumn(int column, const QModelIndex & parent = QModelIndex())
    if (lua_gettop(state) == 2) {
        lua::push(state, self->insertColumn(
            lua::get<int>(state, 2)
        ));
    } else {
        lua::push(state, self->insertColumn(
            lua::get<int>(state, 2),
            lua::get<const QModelIndex&>(state, 3)
        ));
    }

    return 1;
}

int QAbstractItemModel_insertColumns(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual bool     insertColumns(int column, int count, const QModelIndex & parent = QModelIndex())
    if (lua_gettop(state) == 3) {
        lua::push(state, self->insertColumns(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        ));
    } else {
        lua::push(state, self->insertColumns(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QModelIndex&>(state, 4)
        ));
    }

    return 1;
}

int QAbstractItemModel_insertRow(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // bool     insertRow(int row, const QModelIndex & parent = QModelIndex())
    if (lua_gettop(state) == 2) {
        lua::push(state, self->insertRow(
            lua::get<int>(state, 2)
        ));
    } else {
        lua::push(state, self->insertRow(
            lua::get<int>(state, 2),
            lua::get<const QModelIndex&>(state, 3)
        ));
    }

    return 1;
}

int QAbstractItemModel_insertRows(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual bool     insertRows(int row, int count, const QModelIndex & parent = QModelIndex())
    if (lua_gettop(state) == 3) {
        lua::push(state, self->insertRows(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        ));
    } else {
        lua::push(state, self->insertRows(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QModelIndex&>(state, 4)
        ));
    }
    return 1;
}

int QAbstractItemModel_match(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual QModelIndexList  match(const QModelIndex & start, int role, const QVariant & value, int hits = 1, Qt::MatchFlags flags = Qt::MatchFlags( Qt::MatchStartsWith | Qt::MatchWrap )) const
    switch (lua_gettop(state)) {
    case 4:
        lua::push(state, self->match(
            lua::get<const QModelIndex&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QVariant&>(state, 4)
        ));
        break;
    case 5:
        lua::push(state, self->match(
            lua::get<const QModelIndex&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QVariant&>(state, 4),
            lua::get<int>(state, 5)
        ));
        break;
    case 6:
    default:
        lua::push(state, self->match(
            lua::get<const QModelIndex&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QVariant&>(state, 4),
            lua::get<int>(state, 5),
            lua::get<Qt::MatchFlags>(state, 6)
        ));
        break;
    }

    return 1;
}

int QAbstractItemModel_parent(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    if (lua_gettop(state) == 1) {
        lua::push(state, self->parent());
    } else {
        lua::push(state, self->parent(
            lua::get<const QModelIndex&>(state, 2)
        ));
    }

    return 1;
}

int QAbstractItemModel_removeColumn(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // bool     removeColumn(int column, const QModelIndex & parent = QModelIndex())
    if (lua_gettop(state) == 2) {
        lua::push(state, self->removeColumn(
            lua::get<int>(state, 2)
        ));
    } else {
        lua::push(state, self->removeColumn(
            lua::get<int>(state, 2),
            lua::get<const QModelIndex&>(state, 3)
        ));
    }

    return 1;
}

int QAbstractItemModel_removeColumns(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual bool     removeColumns(int column, int count, const QModelIndex & parent = QModelIndex())
    if (lua_gettop(state) == 3) {
        lua::push(state, self->removeColumns(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        ));
    } else {
        lua::push(state, self->removeColumns(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QModelIndex&>(state, 4)
        ));
    }

    return 1;
}

int QAbstractItemModel_removeRow(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // bool     removeRow(int row, const QModelIndex & parent = QModelIndex())
    if (lua_gettop(state) == 2) {
        lua::push(state, self->removeRow(
            lua::get<int>(state, 2)
        ));
    } else {
        lua::push(state, self->removeRow(
            lua::get<int>(state, 2),
            lua::get<const QModelIndex&>(state, 3)
        ));
    }

    return 1;
}

int QAbstractItemModel_removeRows(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual bool     removeRows(int row, int count, const QModelIndex & parent = QModelIndex())
    if (lua_gettop(state) == 3) {
        lua::push(state, self->removeRows(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        ));
    } else {
        lua::push(state, self->removeRows(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QModelIndex&>(state, 4)
        ));
    }

    return 1;
}

int QAbstractItemModel_rowCount(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual int rowCount(const QModelIndex & parent = QModelIndex()) const = 0
    if (lua_gettop(state) == 1) {
        lua::push(state, self->rowCount());
    } else {
        lua::push(state, self->rowCount(
            lua::get<const QModelIndex&>(state, 2)
        ));
    }

    return 1;
}

int QAbstractItemModel_setData(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual bool     setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole)
    if (lua_gettop(state) == 3) {
        lua::push(state, self->setData(
            lua::get<const QModelIndex&>(state, 2),
            lua::get<const QVariant&>(state, 3)
        ));
    } else {
        lua::push(state, self->setData(
            lua::get<const QModelIndex&>(state, 2),
            lua::get<const QVariant&>(state, 3),
            lua::get<int>(state, 4)
        ));
    }
    return 1;
}

int QAbstractItemModel_setHeaderData(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    // virtual bool     setHeaderData(int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole)
    if (lua_gettop(state) == 4) {
        lua::push(state, self->setHeaderData(
            lua::get<int>(state, 2),
            lua::get<Qt::Orientation>(state, 3),
            lua::get<const QVariant&>(state, 4)
        ));
    } else {
        lua::push(state, self->setHeaderData(
            lua::get<int>(state, 2),
            lua::get<Qt::Orientation>(state, 3),
            lua::get<const QVariant&>(state, 4),
            lua::get<int>(state, 5)
        ));
    }
    return 1;
}

int QAbstractItemModel_sort(lua_State* const state)
{
    auto self = lua::get<QAbstractItemModel*>(state, 1);

    if (lua_gettop(state) == 2) {
        self->sort(
            lua::get<int>(state, 2)
        );
    } else {
        self->sort(
            lua::get<int>(state, 2),
            lua::get<Qt::SortOrder>(state, 3)
        );
    }

    return 0;
}

void lua::QAbstractItemModel_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["buddy"] = &QAbstractItemModel::buddy;
    mt["canDropMimeData"] = &QAbstractItemModel::canDropMimeData;
    mt["canFetchMore"] = &QAbstractItemModel::canFetchMore;
    mt["columnCount"] = QAbstractItemModel_columnCount;
    mt["data"] = QAbstractItemModel_data;
    mt["dropMimeData"] = &QAbstractItemModel::dropMimeData;
    mt["fetchMore"] = &QAbstractItemModel::fetchMore;
    mt["flags"] = &QAbstractItemModel::flags;
    mt["hasChildren"] = QAbstractItemModel_hasChildren;
    mt["hasIndex"] = QAbstractItemModel_hasIndex;
    mt["headerData"] = QAbstractItemModel_headerData;
    mt["index"] = QAbstractItemModel_index;
    mt["insertColumn"] = QAbstractItemModel_insertColumn;
    mt["insertColumns"] = QAbstractItemModel_insertColumns;
    mt["insertRow"] = QAbstractItemModel_insertRow;
    mt["insertRows"] = QAbstractItemModel_insertRows;
    mt["itemData"] = &QAbstractItemModel::itemData;
    mt["match"] = QAbstractItemModel_match;
    mt["mimeData"] = &QAbstractItemModel::mimeData;
    mt["mimeTypes"] = &QAbstractItemModel::mimeTypes;
    mt["moveColumn"] = &QAbstractItemModel::moveColumn;
    mt["moveColumns"] = &QAbstractItemModel::moveColumns;
    mt["moveRow"] = &QAbstractItemModel::moveRow;
    mt["moveRows"] = &QAbstractItemModel::moveRows;
    mt["parent"] = QAbstractItemModel_parent;
    mt["removeColumn"] = QAbstractItemModel_removeColumn;
    mt["removeColumns"] = QAbstractItemModel_removeColumns;
    mt["removeRow"] = QAbstractItemModel_removeRow;
    mt["removeRows"] = QAbstractItemModel_removeRows;
    mt["roleNames"] = &QAbstractItemModel::roleNames;
    mt["rowCount"] = QAbstractItemModel_rowCount;
    mt["setData"] = QAbstractItemModel_setData;
    mt["setHeaderData"] = QAbstractItemModel_setHeaderData;
    mt["setItemData"] = &QAbstractItemModel::setItemData;
    mt["sibling"] = &QAbstractItemModel::sibling;
    mt["sort"] = &QAbstractItemModel_sort;
    mt["span"] = &QAbstractItemModel::span;
    mt["supportedDragActions"] = &QAbstractItemModel::supportedDragActions;
    mt["supportedDropActions"] = &QAbstractItemModel::supportedDropActions;
}

int luaopen_Qt5Core_QAbstractItemModel(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractItemModel"] = lua::value::table;
    auto t = env["QAbstractItemModel"];

    // enum QAbstractItemModel::LayoutChangeHint
    t["NoLayoutChangeHint"] = QAbstractItemModel::NoLayoutChangeHint;
    t["VerticalSortHint"] = QAbstractItemModel::VerticalSortHint;
    t["HorizontalSortHint"] = QAbstractItemModel::HorizontalSortHint;

    return 0;
}

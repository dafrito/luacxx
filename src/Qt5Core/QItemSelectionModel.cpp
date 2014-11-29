#include "QItemSelectionModel.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QModelIndex.hpp"
#include "QModelIndexList.hpp"
#include "QAbstractItemModel.hpp"
#include "QItemSelection.hpp"
#include "QItemSelectionRange.hpp"
#include "QFlags.hpp"

int QItemSelectionModel_selectedColumns(lua_State* const state)
{
    auto self = lua::get<QItemSelectionModel*>(state, 1);

    if (lua_gettop(state) == 1) {
        lua::push(state, self->selectedColumns());
    } else {
        lua::push(state, self->selectedColumns(
            lua::get<int>(state, 2)
        ));
    }

    return 1;
}

int QItemSelectionModel_selectedRows(lua_State* const state)
{
    auto self = lua::get<QItemSelectionModel*>(state, 1);

    if (lua_gettop(state) == 1) {
        lua::push(state, self->selectedRows());
    } else {
        lua::push(state, self->selectedRows(
            lua::get<int>(state, 2)
        ));
    }

    return 1;
}

namespace lua {

void QItemSelectionModel_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["columnIntersectsSelection"] = &QItemSelectionModel::columnIntersectsSelection;
    mt["currentIndex"] = &QItemSelectionModel::currentIndex;
    mt["hasSelection"] = &QItemSelectionModel::hasSelection;
    mt["isColumnSelected"] = &QItemSelectionModel::isColumnSelected;
    mt["isRowSelected"] = &QItemSelectionModel::isRowSelected;
    mt["isSelected"] = &QItemSelectionModel::isSelected;
    mt["model"] = &QItemSelectionModel::model;
    mt["rowIntersectsSelection"] = &QItemSelectionModel::rowIntersectsSelection;
    mt["selectedColumns"] = QItemSelectionModel_selectedColumns;
    mt["selectedIndexes"] = &QItemSelectionModel::selectedIndexes;
    mt["selectedRows"] = QItemSelectionModel_selectedRows;
    mt["selection"] = &QItemSelectionModel::selection;
}

} // namespace lua

int QItemSelectionModel_new(lua_State* const state)
{
    if (lua_gettop(state) == 1) {
        // QItemSelectionModel(QAbstractItemModel * model)
        lua::push(state, new QItemSelectionModel(
            lua::get<QAbstractItemModel*>(state, 1)
        ));
    } else {
        // QItemSelectionModel(QAbstractItemModel * model, QObject * parent)
        lua::push(state, new QItemSelectionModel(
            lua::get<QAbstractItemModel*>(state, 1),
            lua::get<QObject*>(state, 2)
        ));
    }

    return 1;
}

int luaopen_Qt5Core_QItemSelectionModel(lua_State* const state)
{
    lua::thread env(state);

    env["QItemSelectionModel"] = lua::value::table;
    env["QItemSelectionModel"]["new"] = QItemSelectionModel_new;
    auto t = env["QItemSelectionModel"];

    // enum QItemSelectionModel::SelectionFlag
    t["SelectionFlags"] = lua::QFlags_new<QItemSelectionModel::SelectionFlags>;
    t["NoUpdate"] = QItemSelectionModel::NoUpdate;
    t["Clear"] = QItemSelectionModel::Clear;
    t["Select"] = QItemSelectionModel::Select;
    t["Deselect"] = QItemSelectionModel::Deselect;
    t["Toggle"] = QItemSelectionModel::Toggle;
    t["Current"] = QItemSelectionModel::Current;
    t["Rows"] = QItemSelectionModel::Rows;
    t["Columns"] = QItemSelectionModel::Columns;
    t["SelectCurrent"] = QItemSelectionModel::SelectCurrent;
    t["ToggleCurrent"] = QItemSelectionModel::ToggleCurrent;
    t["ClearAndSelect"] = QItemSelectionModel::ClearAndSelect;

    return 0;
}

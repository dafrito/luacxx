#include "QItemSelectionRange.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QModelIndexList.hpp"
#include "QAbstractItemModel.hpp"
#include "QPersistentModelIndex.hpp"
#include "QModelIndex.hpp"

int QItemSelectionRange_contains(lua_State* const state)
{
    auto self = lua::get<QItemSelectionRange*>(state, 1);

    if (lua_gettop(state) == 1) {
        // bool contains(const QModelIndex & index) const
        lua::push(state, self->contains(
            lua::get<const QModelIndex&>(state, 2)
        ));
    } else {
        // bool contains(int row, int column, const QModelIndex & parentIndex) const
        lua::push(state, self->contains(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QModelIndex&>(state, 4)
        ));
    }

    return 1;
}

namespace lua {

void QItemSelectionRange_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["bottom"] = &QItemSelectionRange::bottom;
    mt["bottomRight"] = &QItemSelectionRange::bottomRight;
    mt["contains"] = QItemSelectionRange_contains;
    mt["height"] = &QItemSelectionRange::height;
    mt["indexes"] = &QItemSelectionRange::indexes;
    mt["intersected"] = &QItemSelectionRange::intersected;
    mt["intersects"] = &QItemSelectionRange::intersects;
    mt["isEmpty"] = &QItemSelectionRange::isEmpty;
    mt["isValid"] = &QItemSelectionRange::isValid;
    mt["left"] = &QItemSelectionRange::left;
    mt["model"] = &QItemSelectionRange::model;
    mt["parent"] = &QItemSelectionRange::parent;
    mt["right"] = &QItemSelectionRange::right;
    mt["top"] = &QItemSelectionRange::top;
    mt["topLeft"] = &QItemSelectionRange::topLeft;
    mt["width"] = &QItemSelectionRange::width;
}

} // namespace lua

int QItemSelectionRange_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QItemSelectionRange()
        lua::make<QItemSelectionRange>(state);
    } else if (lua_gettop(state) == 2) {
        // QItemSelectionRange(const QModelIndex & topLeft, const QModelIndex & bottomRight)
        lua::make<QItemSelectionRange>(state,
            lua::get<const QModelIndex&>(state, 1),
            lua::get<const QModelIndex&>(state, 2)
        );
    } else if (lua::is_type<QModelIndex>(state, 1)) {
        // QItemSelectionRange(const QModelIndex & index)
        lua::make<QItemSelectionRange>(state,
            lua::get<const QModelIndex&>(state, 1)
        );
    } else {
        // QItemSelectionRange(const QItemSelectionRange & other)
        lua::make<QItemSelectionRange>(state,
            lua::get<const QItemSelectionRange&>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Core_QItemSelectionRange(lua_State* const state)
{
    lua::thread env(state);

    env["QItemSelectionRange"] = lua::value::table;
    env["QItemSelectionRange"]["new"] = QItemSelectionRange_new;
    auto t = env["QItemSelectionRange"];

    return 0;
}

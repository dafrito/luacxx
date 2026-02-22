#include "QAbstractTableModel.hpp"

namespace lua {

void QAbstractTableModel_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractItemModel_metatable(state, pos);
}

} // namespace lua

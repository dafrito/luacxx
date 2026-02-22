#include "QTextTable.hpp"
#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QTextTableCell.hpp"
#include "QTextTableFormat.hpp"
#include "QTextFrame.hpp"
#include "QTextCursor.hpp"
#include "QTextDocument.hpp"

int QTextTable_cellAt(lua_State* const state)
{
    auto self = lua::get<QTextTable*>(state, 1);
    if (lua_gettop(state) == 3) {
        // QTextTableCell   cellAt(int row, int column) const
        lua::push(state, self->cellAt(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        ));
    } else if (lua_type(state, 2) == LUA_TNUMBER) {
        // QTextTableCell   cellAt(int position) const
        lua::push(state, self->cellAt(
            lua::get<int>(state, 2)
        ));
    } else {
        // QTextTableCell   cellAt(const QTextCursor & cursor) const
        lua::push(state, self->cellAt(
            lua::get<const QTextCursor&>(state, 2)
        ));
    }
    return 1;
}

int QTextTable_mergeCells(lua_State* const state)
{
    return 0;
}

namespace lua {

void QTextTable_metatable(lua_State* const state, const int pos)
{
    lua::QTextFrame_metatable(state, pos);

    lua::index mt(state, pos);
    mt["appendColumns"] = &QTextTable::appendColumns;
    mt["appendRows"] = &QTextTable::appendRows;
    mt["cellAt"] = QTextTable_cellAt;
    mt["columns"] = &QTextTable::columns;
    mt["format"] = &QTextTable::format;
    mt["insertColumns"] = &QTextTable::insertColumns;
    mt["insertRows"] = &QTextTable::insertRows;
    mt["mergeCells"] = QTextTable_mergeCells;
    mt["removeColumns"] = &QTextTable::removeColumns;
    mt["removeRows"] = &QTextTable::removeRows;
    mt["resize"] = &QTextTable::resize;
    mt["rowEnd"] = &QTextTable::rowEnd;
    mt["rowStart"] = &QTextTable::rowStart;
    mt["rows"] = &QTextTable::rows;
    mt["setFormat"] = &QTextTable::setFormat;
    mt["splitCell"] = &QTextTable::splitCell;
}

} // namespace lua

int QTextTable_new(lua_State* const state)
{
    lua::make<QTextTable>(state, lua::get<QTextDocument*>(state, 1));
    return 1;
}

int luaopen_Qt5Gui_QTextTable(lua_State* const state)
{
    lua::thread env(state);

    env["QTextTable"] = lua::value::table;
    env["QTextTable"]["new"] = QTextTable_new;
    auto t = env["QTextTable"];

    return 0;
}

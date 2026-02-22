#include "QTextTableCell.hpp"
#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QTextCursor.hpp"
#include "QTextCharFormat.hpp"

namespace lua {

void QTextTableCell_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    //QTextFrame::iterator    begin() const
    mt["column"] = &QTextTableCell::column;
    mt["columnSpan"] = &QTextTableCell::columnSpan;
    //QTextFrame::iterator    end() const
    mt["firstCursorPosition"] = &QTextTableCell::firstCursorPosition;
    mt["format"] = &QTextTableCell::format;
    mt["isValid"] = &QTextTableCell::isValid;
    mt["lastCursorPosition"] = &QTextTableCell::lastCursorPosition;
    mt["row"] = &QTextTableCell::row;
    mt["rowSpan"] = &QTextTableCell::rowSpan;
    mt["setFormat"] = &QTextTableCell::setFormat;
    mt["tableCellFormatIndex"] = &QTextTableCell::tableCellFormatIndex;
}

} // namespace lua

int QTextTableCell_new(lua_State* const state)
{
    lua::make<QTextTableCell>(state);
    return 1;
}

int luaopen_Qt5Gui_QTextTableCell(lua_State* const state)
{
    lua::thread env(state);

    env["QTextTableCell"] = lua::value::table;
    env["QTextTableCell"]["new"] = QTextTableCell_new;
    auto t = env["QTextTableCell"];

    return 0;
}

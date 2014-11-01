#include "QTextTableCellFormat.hpp"
#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QTextCharFormat.hpp"

namespace lua {

void QTextTableCellFormat_metatable(lua_State* const state, const int pos)
{
    lua::QTextCharFormat_metatable(state, pos);

    lua::index mt(state, pos);
    mt["bottomPadding"] = &QTextTableCellFormat::bottomPadding;
    mt["isValid"] = &QTextTableCellFormat::isValid;
    mt["leftPadding"] = &QTextTableCellFormat::leftPadding;
    mt["rightPadding"] = &QTextTableCellFormat::rightPadding;
    mt["setBottomPadding"] = &QTextTableCellFormat::setBottomPadding;
    mt["setLeftPadding"] = &QTextTableCellFormat::setLeftPadding;
    mt["setPadding"] = &QTextTableCellFormat::setPadding;
    mt["setRightPadding"] = &QTextTableCellFormat::setRightPadding;
    mt["setTopPadding"] = &QTextTableCellFormat::setTopPadding;
    mt["topPadding"] = &QTextTableCellFormat::topPadding;
}

} // namespace lua

int QTextTableCellFormat_new(lua_State* const state)
{
    lua::make<QTextTableCellFormat>(state);
    return 1;
}

int luaopen_luacxx_QTextTableCellFormat(lua_State* const state)
{
    lua::thread env(state);

    env["QTextTableCellFormat"] = lua::value::table;
    env["QTextTableCellFormat"]["new"] = QTextTableCellFormat_new;
    auto t = env["QTextTableCellFormat"];

    return 0;
}

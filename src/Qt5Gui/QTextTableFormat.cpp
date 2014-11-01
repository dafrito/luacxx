#include "QTextTableFormat.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"

#include "QTextFrameFormat.hpp"
#include "QTextLength.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/QVector.hpp"

namespace lua {

void QTextTableFormat_metatable(lua_State* const state, const int pos)
{
    lua::QTextFrameFormat_metatable(state, pos);

    lua::index mt(state, pos);
    mt["alignment"] = &QTextTableFormat::alignment;
    mt["cellPadding"] = &QTextTableFormat::cellPadding;
    mt["cellSpacing"] = &QTextTableFormat::cellSpacing;
    mt["clearColumnWidthConstraints"] = &QTextTableFormat::clearColumnWidthConstraints;
    mt["columnWidthConstraints"] = &QTextTableFormat::columnWidthConstraints;
    mt["columns"] = &QTextTableFormat::columns;
    mt["headerRowCount"] = &QTextTableFormat::headerRowCount;
    mt["isValid"] = &QTextTableFormat::isValid;
    mt["setAlignment"] = &QTextTableFormat::setAlignment;
    mt["setCellPadding"] = &QTextTableFormat::setCellPadding;
    mt["setCellSpacing"] = &QTextTableFormat::setCellSpacing;
    mt["setColumnWidthConstraints"] = &QTextTableFormat::setColumnWidthConstraints;
    mt["setHeaderRowCount"] = &QTextTableFormat::setHeaderRowCount;
}

} // namespace lua

int QTextTableFormat_new(lua_State* const state)
{
    lua::make<QTextTableFormat>(state);
    return 1;
}

int luaopen_Qt5Gui_QTextTableFormat(lua_State* const state)
{
    lua::thread env(state);

    env["QTextTableFormat"] = lua::value::table;
    env["QTextTableFormat"]["new"] = QTextTableFormat_new;
    auto t = env["QTextTableFormat"];

    return 0;
}

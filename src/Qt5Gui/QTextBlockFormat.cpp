#include "QTextBlockFormat.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QList.hpp"
#include "QTextOption.hpp"

namespace lua {

void QTextBlockFormat_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["alignment"] = &QTextBlockFormat::alignment;
    mt["bottomMargin"] = &QTextBlockFormat::bottomMargin;
    mt["indent"] = &QTextBlockFormat::indent;
    mt["isValid"] = &QTextBlockFormat::isValid;
    mt["leftMargin"] = &QTextBlockFormat::leftMargin;
    mt["lineHeight"] = &QTextBlockFormat::lineHeight;
    mt["lineHeight"] = &QTextBlockFormat::lineHeight;
    mt["lineHeightType"] = &QTextBlockFormat::lineHeightType;
    mt["nonBreakableLines"] = &QTextBlockFormat::nonBreakableLines;
    mt["pageBreakPolicy"] = &QTextBlockFormat::pageBreakPolicy;
    mt["rightMargin"] = &QTextBlockFormat::rightMargin;
    mt["setAlignment"] = &QTextFormat::setAlignment;
    mt["setBottomMargin"] = &QTextBlockFormat::setBottomMargin;
    mt["setIndent"] = &QTextBlockFormat::setIndent;
    mt["setLeftMargin"] = &QTextBlockFormat::setLeftMargin;
    mt["setLineHeight"] = &QTextBlockFormat::setLineHeight;
    mt["setNonBreakableLines"] = &QTextBlockFormat::setNonBreakableLines;
    mt["setPageBreakPolicy"] = &QTextBlockFormat::setPageBreakPolicy;
    mt["setRightMargin"] = &QTextBlockFormat::setRightMargin;
    mt["setTabPositions"] = &QTextBlockFormat::setTabPositions;
    mt["setTextIndent"] = &QTextBlockFormat::setTextIndent;
    mt["setTopMargin"] = &QTextBlockFormat::setTopMargin;
    mt["tabPositions"] = &QTextBlockFormat::tabPositions;
    mt["textIndent"] = &QTextBlockFormat::textIndent;
    mt["topMargin"] = &QTextBlockFormat::topMargin;
}

} // namespace lua

int QTextBlockFormat_new(lua_State* const state)
{
    lua::make<QTextBlockFormat>(state);

    return 1;
}

int luaopen_luacxx_QTextBlockFormat(lua_State* const state)
{
    lua::thread env(state);

    env["QTextBlockFormat"] = lua::value::table;
    env["QTextBlockFormat"]["new"] = QTextBlockFormat_new;
    auto t = env["QTextBlockFormat"];

    // enum QTextBlockFormat::LineHeightTypes
    t["SingleHeight"] = QTextBlockFormat::SingleHeight;
    t["ProportionalHeight"] = QTextBlockFormat::ProportionalHeight;
    t["FixedHeight"] = QTextBlockFormat::FixedHeight;
    t["MinimumHeight"] = QTextBlockFormat::MinimumHeight;
    t["LineDistanceHeight"] = QTextBlockFormat::LineDistanceHeight;

    return 0;
}

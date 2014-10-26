#include "QTextFrameFormat.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QTextLength.hpp"
#include "QBrush.hpp"

namespace lua {

void QTextFrameFormat_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["border"] = &QTextFrameFormat::border;
    mt["borderBrush"] = &QTextFrameFormat::borderBrush;
    mt["borderStyle"] = &QTextFrameFormat::borderStyle;
    mt["bottomMargin"] = &QTextFrameFormat::bottomMargin;
    mt["height"] = &QTextFrameFormat::height;
    mt["isValid"] = &QTextFrameFormat::isValid;
    mt["leftMargin"] = &QTextFrameFormat::leftMargin;
    mt["margin"] = &QTextFrameFormat::margin;
    mt["padding"] = &QTextFrameFormat::padding;
    mt["pageBreakPolicy"] = &QTextFrameFormat::pageBreakPolicy;
    mt["position"] = &QTextFrameFormat::position;
    mt["rightMargin"] = &QTextFrameFormat::rightMargin;
    mt["setBorder"] = &QTextFrameFormat::setBorder;
    mt["setBorderBrush"] = &QTextFrameFormat::setBorderBrush;
    mt["setBorderStyle"] = &QTextFrameFormat::setBorderStyle;
    mt["setBottomMargin"] = &QTextFrameFormat::setBottomMargin;
    mt["setHeight"] = &QTextFrameFormat::setHeight;
    mt["setHeight"] = &QTextFrameFormat::setHeight;
    mt["setLeftMargin"] = &QTextFrameFormat::setLeftMargin;
    mt["setMargin"] = &QTextFrameFormat::setMargin;
    mt["setPadding"] = &QTextFrameFormat::setPadding;
    mt["setPageBreakPolicy"] = &QTextFrameFormat::setPageBreakPolicy;
    mt["setPosition"] = &QTextFrameFormat::setPosition;
    mt["setRightMargin"] = &QTextFrameFormat::setRightMargin;
    mt["setTopMargin"] = &QTextFrameFormat::setTopMargin;
    mt["setWidth"] = QTextFrameFormat_setWidth;
    mt["topMargin"] = &QTextFrameFormat::topMargin;
    mt["width"] = &QTextFrameFormat::width;
}

} // namespace lua

int QTextFrameFormat_new(lua_State* const state)
{
    lua::make<QTextFrameFormat>(state);
    return 1;
}

int luaopen_luacxx_QTextFrameFormat(lua_State* const state)
{
    lua::thread env(state);

    env["QTextFrameFormat"] = lua::value::table;
    env["QTextFrameFormat"]["new"] = QTextFrameFormat_new;
    auto t = env["QTextFrameFormat"];

    // enum QTextFrameFormat::BorderStyle
    t["BorderStyle_None"] = QTextFrameFormat::BorderStyle_None;
    t["BorderStyle_Dotted"] = QTextFrameFormat::BorderStyle_Dotted;
    t["BorderStyle_Dashed"] = QTextFrameFormat::BorderStyle_Dashed;
    t["BorderStyle_Solid"] = QTextFrameFormat::BorderStyle_Solid;
    t["BorderStyle_Double"] = QTextFrameFormat::BorderStyle_Double;
    t["BorderStyle_DotDash"] = QTextFrameFormat::BorderStyle_DotDash;
    t["BorderStyle_DotDotDash"] = QTextFrameFormat::BorderStyle_DotDotDash;
    t["BorderStyle_Groove"] = QTextFrameFormat::BorderStyle_Groove;
    t["BorderStyle_Ridge"] = QTextFrameFormat::BorderStyle_Ridge;
    t["BorderStyle_Inset"] = QTextFrameFormat::BorderStyle_Inset;
    t["BorderStyle_Outset"] = QTextFrameFormat::BorderStyle_Outset;

    // enum QTextFrameFormat::Position
    t["InFlow"] = QTextFrameFormat::InFlow;
    t["FloatLeft"] = QTextFrameFormat::FloatLeft;
    t["FloatRight"] = QTextFrameFormat::FloatRight;

    return 0;
}

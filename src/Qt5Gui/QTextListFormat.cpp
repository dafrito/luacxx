#include "QTextListFormat.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

namespace lua {

void QTextListFormat_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["indent"] = &QTextListFormat::indent;
    mt["isValid"] = &QTextListFormat::isValid;
    mt["numberPrefix"] = &QTextListFormat::numberPrefix;
    mt["numberSuffix"] = &QTextListFormat::numberSuffix;
    mt["setIndent"] = &QTextListFormat::setIndent;
    mt["setNumberPrefix"] = &QTextListFormat::setNumberPrefix;
    mt["setNumberSuffix"] = &QTextListFormat::setNumberSuffix;
    mt["setStyle"] = &QTextListFormat::setStyle;
    mt["style"] = &QTextListFormat::style;
}

} // namespace lua

int QTextListFormat_new(lua_State* const state)
{
    lua::make<QTextListFormat>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_Qt5Gui_QTextListFormat(lua_State* const state)
{
    lua::thread env(state);

    env["QTextListFormat"] = lua::value::table;
    env["QTextListFormat"]["new"] = QTextListFormat_new;
    auto t = env["QTextListFormat"];

    // enum QTextListFormat::Style
    t["ListDisc"] = QTextListFormat::ListDisc;
    t["ListCircle"] = QTextListFormat::ListCircle;
    t["ListSquare"] = QTextListFormat::ListSquare;
    t["ListDecimal"] = QTextListFormat::ListDecimal;
    t["ListLowerAlpha"] = QTextListFormat::ListLowerAlpha;
    t["ListUpperAlpha"] = QTextListFormat::ListUpperAlpha;
    t["ListLowerRoman"] = QTextListFormat::ListLowerRoman;
    t["ListUpperRoman"] = QTextListFormat::ListUpperRoman;

    return 0;
}

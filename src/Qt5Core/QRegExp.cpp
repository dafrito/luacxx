#include "QRegExp.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "Qt.hpp"
#include "QString.hpp"
#include "QStringList.hpp"

int QRegExp_cap(lua_State* const state)
{
    return 0;
}
int QRegExp_indexIn(lua_State* const state)
{
    return 0;
}
int QRegExp_lastIndexIn(lua_State* const state)
{
    return 0;
}
int QRegExp_pos(lua_State* const state)
{
    return 0;
}
int QRegExp_errorString(lua_State* const state)
{
    return 0;
}
int QRegExp_capturedTexts(lua_State* const state)
{
    return 0;
}

namespace lua {

void QRegExp_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["cap"] = QRegExp_cap;
    mt["captureCount"] = &QRegExp::captureCount;
    mt["capturedTexts"] = QRegExp_capturedTexts;
    mt["caseSensitivity"] = &QRegExp::caseSensitivity;
    mt["errorString"] = QRegExp_errorString;
    mt["exactMatch"] = &QRegExp::exactMatch;
    mt["indexIn"] = QRegExp_indexIn;
    mt["isEmpty"] = &QRegExp::isEmpty;
    mt["isMinimal"] = &QRegExp::isMinimal;
    mt["isValid"] = &QRegExp::isValid;
    mt["lastIndexIn"] = QRegExp_lastIndexIn;
    mt["matchedLength"] = &QRegExp::matchedLength;
    mt["pattern"] = &QRegExp::pattern;
    mt["patternSyntax"] = &QRegExp::patternSyntax;
    mt["pos"] = QRegExp_pos;
    mt["setCaseSensitivity"] = &QRegExp::setCaseSensitivity;
    mt["setMinimal"] = &QRegExp::setMinimal;
    mt["setPattern"] = &QRegExp::setPattern;
    mt["setPatternSyntax"] = &QRegExp::setPatternSyntax;
    mt["swap"] = &QRegExp::swap;
}

} // namespace lua

int QRegExp_new(lua_State* const state)
{
    lua::make<QRegExp>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QRegExp(lua_State* const state)
{
    lua::thread env(state);

    env["QRegExp"] = lua::value::table;
    env["QRegExp"]["new"] = QRegExp_new;
    auto t = env["QRegExp"];

    // enum QRegExp::CaretMode
    t["CaretAtZero"] = QRegExp::CaretAtZero;
    t["CaretAtOffset"] = QRegExp::CaretAtOffset;
    t["CaretWontMatch"] = QRegExp::CaretWontMatch;

    // enum QRegExp::PatternSyntax
    t["RegExp"] = QRegExp::RegExp;
    t["RegExp2"] = QRegExp::RegExp2;
    t["Wildcard"] = QRegExp::Wildcard;
    t["WildcardUnix"] = QRegExp::WildcardUnix;
    t["FixedString"] = QRegExp::FixedString;
    t["W3CXmlSchema11"] = QRegExp::W3CXmlSchema11;

    return 0;
}

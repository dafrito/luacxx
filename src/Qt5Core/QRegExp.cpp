#include "QRegExp.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "Qt.hpp"
#include "QString.hpp"
#include "QStringList.hpp"

int QRegExp_cap(lua_State* const state)
{
    auto self = lua::get<QRegExp*>(state, 1);

    if (lua_gettop(state) > 1) {
        lua::push(state, self->cap(lua::get<int>(state, 2)));
    } else {
        lua::push(state, self->cap());
    }
    return 1;
}

int QRegExp_indexIn(lua_State* const state)
{
    auto self = lua::get<QRegExp*>(state, 1);

    // int indexIn(const QString & str, int offset = 0, CaretMode caretMode = CaretAtZero) const
    switch (lua_gettop(state)) {
    case 2:
        lua::push(state, self->indexIn(
            lua::get<QString>(state, 2)
        ));
        break;
    case 3:
        lua::push(state, self->indexIn(
            lua::get<QString>(state, 2),
            lua::get<int>(state, 3)
        ));
        break;
    case 4:
    default:
        lua::push(state, self->indexIn(
            lua::get<QString>(state, 2),
            lua::get<int>(state, 3),
            lua::get<QRegExp::CaretMode>(state, 4)
        ));
        break;
    }

    return 1;
}

int QRegExp_lastIndexIn(lua_State* const state)
{
    auto self = lua::get<QRegExp*>(state, 1);

    // int lastIndexIn(const QString & str, int offset = -1, CaretMode caretMode = CaretAtZero) const
    switch (lua_gettop(state)) {
    case 2:
        lua::push(state, self->lastIndexIn(
            lua::get<QString>(state, 2)
        ));
        break;
    case 3:
        lua::push(state, self->lastIndexIn(
            lua::get<QString>(state, 2),
            lua::get<int>(state, 3)
        ));
        break;
    case 4:
    default:
        lua::push(state, self->lastIndexIn(
            lua::get<QString>(state, 2),
            lua::get<int>(state, 3),
            lua::get<QRegExp::CaretMode>(state, 4)
        ));
        break;
    }

    return 1;
}

int QRegExp_pos(lua_State* const state)
{
    auto self = lua::get<QRegExp*>(state, 1);

    if (lua_gettop(state) > 1) {
        lua::push(state, self->pos(lua::get<int>(state, 2)));
    } else {
        lua::push(state, self->pos());
    }
    return 1;
}

int QRegExp_errorString(lua_State* const state)
{
    auto self = lua::get<QRegExp*>(state, 1);

    lua::push(state, self->errorString());
    return 1;
}

int QRegExp_capturedTexts(lua_State* const state)
{
    auto self = lua::get<QRegExp*>(state, 1);

    lua::push(state, self->capturedTexts());
    return 1;
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
    if (lua_gettop(state) == 0) {
        // QRegExp()
        lua::make<QRegExp>(state);
    } else if (lua::is_type<QRegExp>(state, 1)) {
        // QRegExp(const QRegExp & rx)
        lua::make<QRegExp>(state, lua::get<const QRegExp&>(state, 1));
    } else {
        // QRegExp(const QString & pattern, Qt::CaseSensitivity cs = Qt::CaseSensitive, PatternSyntax syntax = RegExp)
        switch (lua_gettop(state)) {
        case 1:
            lua::make<QRegExp>(state,
                lua::get<QString>(state, 1)
            );
            break;
        case 2:
            lua::make<QRegExp>(state,
                lua::get<QString>(state, 1),
                lua::get<Qt::CaseSensitivity>(state, 2)
            );
            break;
        case 3:
        default:
            lua::make<QRegExp>(state,
                lua::get<QString>(state, 1),
                lua::get<Qt::CaseSensitivity>(state, 2),
                lua::get<QRegExp::PatternSyntax>(state, 3)
            );
            break;
        }
    }
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

#include "QFontInfo.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QFontInfo>

#include "QFont.hpp"
#include "../Qt5Core/QString.hpp"

// http://qt-project.org/doc/qt-5/qfontinfo.html

void lua::QFontInfo_metatable(const lua::index& mt)
{
    mt["bold"] = &QFontInfo::bold;
    mt["exactMatch"] = &QFontInfo::exactMatch;
    mt["family"] = &QFontInfo::family;
    mt["fixedPitch"] = &QFontInfo::fixedPitch;
    mt["italic"] = &QFontInfo::italic;
    mt["pixelSize"] = &QFontInfo::pixelSize;
    mt["pointSize"] = &QFontInfo::pointSize;
    mt["pointSizeF"] = &QFontInfo::pointSizeF;
    mt["rawMode"] = &QFontInfo::rawMode;
    mt["style"] = &QFontInfo::style;
    mt["styleHint"] = &QFontInfo::styleHint;
    mt["styleName"] = &QFontInfo::styleName;
    mt["swap"] = &QFontInfo::swap;
    mt["weight"] = &QFontInfo::weight;
}

int QFontInfo_new(lua_State* const state)
{
    // QFontInfo(const QFont & font)
    // QFontInfo(const QFontInfo & fi)
    if (lua::is_type<QFont>(state, 1)) {
        lua::make<QFontInfo>(state, lua::get<const QFont&>(state, 1));
    } else {
        lua::make<QFontInfo>(state, lua::get<const QFontInfo&>(state, 1));
    }
    return 1;
}

int luaopen_luacxx_QFontInfo(lua_State* const state)
{
    lua::thread env(state);

    env["QFontInfo"] = lua::value::table;
    env["QFontInfo"]["new"] = QFontInfo_new;

    return 0;
}

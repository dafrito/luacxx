#include "QFont.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QPaintDevice.hpp"

int QFont_resolve(lua_State* const state)
{
    auto self = lua::get<QFont*>(state, 1);
    lua::push(state, self->resolve(lua::get<const QFont&>(state, 2)));
    return 1;
}

void lua::QFont_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["bold"] = &QFont::bold;
    mt["capitalization"] = &QFont::capitalization;
    mt["defaultFamily"] = &QFont::defaultFamily;
    mt["exactMatch"] = &QFont::exactMatch;
    mt["family"] = &QFont::family;
    mt["fixedPitch"] = &QFont::fixedPitch;
    mt["fromString"] = &QFont::fromString;
    mt["hintingPreference"] = &QFont::hintingPreference;
    mt["isCopyOf"] = &QFont::isCopyOf;
    mt["italic"] = &QFont::italic;
    mt["kerning"] = &QFont::kerning;
    mt["key"] = &QFont::key;
    mt["lastResortFamily"] = &QFont::lastResortFamily;
    mt["lastResortFont"] = &QFont::lastResortFont;
    mt["letterSpacing"] = &QFont::letterSpacing;
    mt["letterSpacingType"] = &QFont::letterSpacingType;
    mt["overline"] = &QFont::overline;
    mt["pixelSize"] = &QFont::pixelSize;
    mt["pointSize"] = &QFont::pointSize;
    mt["pointSizeF"] = &QFont::pointSizeF;
    mt["rawMode"] = &QFont::rawMode;
    mt["resolve"] = QFont_resolve;
    mt["setBold"] = &QFont::setBold;
    mt["setCapitalization"] = &QFont::setCapitalization;
    mt["setFamily"] = &QFont::setFamily;
    mt["setFixedPitch"] = &QFont::setFixedPitch;
    mt["setHintingPreference"] = &QFont::setHintingPreference;
    mt["setItalic"] = &QFont::setItalic;
    mt["setKerning"] = &QFont::setKerning;
    mt["setLetterSpacing"] = &QFont::setLetterSpacing;
    mt["setOverline"] = &QFont::setOverline;
    mt["setPixelSize"] = &QFont::setPixelSize;
    mt["setPointSize"] = &QFont::setPointSize;
    mt["setPointSizeF"] = &QFont::setPointSizeF;
    mt["setRawMode"] = &QFont::setRawMode;
    mt["setStretch"] = &QFont::setStretch;
    mt["setStrikeOut"] = &QFont::setStrikeOut;
    mt["setStyle"] = &QFont::setStyle;
    mt["setStyleHint"] = &QFont::setStyleHint;
    mt["setStyleName"] = &QFont::setStyleName;
    mt["setStyleStrategy"] = &QFont::setStyleStrategy;
    mt["setUnderline"] = &QFont::setUnderline;
    mt["setWeight"] = &QFont::setWeight;
    mt["setWordSpacing"] = &QFont::setWordSpacing;
    mt["stretch"] = &QFont::stretch;
    mt["strikeOut"] = &QFont::strikeOut;
    mt["style"] = &QFont::style;
    mt["styleHint"] = &QFont::styleHint;
    mt["styleName"] = &QFont::styleName;
    mt["styleStrategy"] = &QFont::styleStrategy;
    mt["swap"] = &QFont::swap;
    mt["toString"] = &QFont::toString;
    mt["underline"] = &QFont::underline;
    mt["weight"] = &QFont::weight;
    mt["wordSpacing"] = &QFont::wordSpacing;
}

int QFont_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::make<QFont>(state);
        return 1;
    }

    if (lua::is_type<QFont>(state, 1)) {
        if (lua_gettop(state) == 1) {
            lua::make<QFont>(state, lua::get<const QFont&>(state, 1));
            return 1;
        }
        lua::make<QFont>(state,
            lua::get<const QFont&>(state, 1),
            lua::get<QPaintDevice*>(state, 2)
        );
        return 1;
    }

    switch (lua_gettop(state)) {
    case 1:
        lua::make<QFont>(state,
            lua::get<QString>(state, 1) // family
        );
        return 1;
    case 2:
        lua::make<QFont>(state,
            lua::get<QString>(state, 1), // family
            lua::get<int>(state, 2) // pointSize
        );
        return 1;
    case 3:
        lua::make<QFont>(state,
            lua::get<QString>(state, 1), // family
            lua::get<int>(state, 2), // pointSize
            lua::get<int>(state, 3) // weight
        );
        return 1;
    default:
        lua::make<QFont>(state,
            lua::get<QString>(state, 1), // family
            lua::get<int>(state, 2), // pointSize
            lua::get<int>(state, 3), // weight
            lua::get<bool>(state, 4) // italic
        );
        return 1;
    }
    return 1;
}

int luaopen_Qt5Gui_QFont(lua_State* const state)
{
    lua::thread env(state);

    env["QFont"] = lua::value::table;
    env["QFont"]["new"] = QFont_new;

    // enum QFont::Capitalization
    env["QFont"]["MixedCase"] = QFont::MixedCase;
    env["QFont"]["AllUppercase"] = QFont::AllUppercase;
    env["QFont"]["AllLowercase"] = QFont::AllLowercase;
    env["QFont"]["SmallCaps"] = QFont::SmallCaps;
    env["QFont"]["Capitalize"] = QFont::Capitalize;

    // enum QFont::HintingPreference
    env["QFont"]["PreferDefaultHinting"] = QFont::PreferDefaultHinting;
    env["QFont"]["PreferNoHinting"] = QFont::PreferNoHinting;
    env["QFont"]["PreferVerticalHinting"] = QFont::PreferVerticalHinting;
    env["QFont"]["PreferFullHinting"] = QFont::PreferFullHinting;

    // enum QFont::SpacingType
    env["QFont"]["PercentageSpacing"] = QFont::PercentageSpacing;
    env["QFont"]["AbsoluteSpacing"] = QFont::AbsoluteSpacing;

    // enum QFont::Stretch
    env["QFont"]["UltraCondensed"] = QFont::UltraCondensed;
    env["QFont"]["ExtraCondensed"] = QFont::ExtraCondensed;
    env["QFont"]["Condensed"] = QFont::Condensed;
    env["QFont"]["SemiCondensed"] = QFont::SemiCondensed;
    env["QFont"]["Unstretched"] = QFont::Unstretched;
    env["QFont"]["SemiExpanded"] = QFont::SemiExpanded;
    env["QFont"]["Expanded"] = QFont::Expanded;
    env["QFont"]["ExtraExpanded"] = QFont::ExtraExpanded;
    env["QFont"]["UltraExpanded"] = QFont::UltraExpanded;

    // enum QFont::Style
    env["QFont"]["StyleNormal"] = QFont::StyleNormal;
    env["QFont"]["StyleItalic"] = QFont::StyleItalic;
    env["QFont"]["StyleOblique"] = QFont::StyleOblique;

    // enum QFont::StyleHint
    env["QFont"]["AnyStyle"] = QFont::AnyStyle;
    env["QFont"]["SansSerif"] = QFont::SansSerif;
    env["QFont"]["Helvetica"] = QFont::Helvetica;
    env["QFont"]["Serif"] = QFont::Serif;
    env["QFont"]["Times"] = QFont::Times;
    env["QFont"]["TypeWriter"] = QFont::TypeWriter;
    env["QFont"]["Courier"] = QFont::Courier;
    env["QFont"]["OldEnglish"] = QFont::OldEnglish;
    env["QFont"]["Decorative"] = QFont::Decorative;
    env["QFont"]["Monospace"] = QFont::Monospace;
    env["QFont"]["Fantasy"] = QFont::Fantasy;
    env["QFont"]["Cursive"] = QFont::Cursive;
    env["QFont"]["System"] = QFont::System;

    // enum QFont::StyleStrategy
    env["QFont"]["PreferDefault"] = QFont::PreferDefault;
    env["QFont"]["PreferBitmap"] = QFont::PreferBitmap;
    env["QFont"]["PreferDevice"] = QFont::PreferDevice;
    env["QFont"]["PreferOutline"] = QFont::PreferOutline;
    env["QFont"]["ForceOutline"] = QFont::ForceOutline;
    env["QFont"]["NoAntialias"] = QFont::NoAntialias;
    env["QFont"]["PreferAntialias"] = QFont::PreferAntialias;
    env["QFont"]["OpenGLCompatible"] = QFont::OpenGLCompatible;
    env["QFont"]["NoFontMerging"] = QFont::NoFontMerging;
    env["QFont"]["PreferMatch"] = QFont::PreferMatch;
    env["QFont"]["PreferQuality"] = QFont::PreferQuality;
    env["QFont"]["ForceIntegerMetrics"] = QFont::ForceIntegerMetrics;

    // enum QFont::Weight
    env["QFont"]["Light"] = QFont::Light;
    env["QFont"]["Normal"] = QFont::Normal;
    env["QFont"]["DemiBold"] = QFont::DemiBold;
    env["QFont"]["Bold"] = QFont::Bold;
    env["QFont"]["Black"] = QFont::Black;

    return 0;
}

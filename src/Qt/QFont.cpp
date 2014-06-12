#include "QFont.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QFont>

int QFont_resolve(lua_State* const state)
{
    return 0;
}

void lua::QFont_metatable(const lua::index& mt)
{
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

int QFont_new(lua::state* const state)
{
    lua::make<QFont>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QFont(lua::state* const state)
{
    lua::thread env(state);

    env["QFont"] = lua::value::table;
    env["QFont"]["new"] = QFont_new;

    env["QFont"]["PreferDefaultHinting"] = QFont::PreferDefaultHinting;
    env["QFont"]["PreferNoHinting"] = QFont::PreferNoHinting;
    env["QFont"]["PreferVerticalHinting"] = QFont::PreferVerticalHinting;
    env["QFont"]["PreferFullHinting"] = QFont::PreferFullHinting;

    env["QFont"]["MixedCase"] = QFont::MixedCase;
    env["QFont"]["AllUppercase"] = QFont::AllUppercase;
    env["QFont"]["AllLowercase"] = QFont::AllLowercase;
    env["QFont"]["SmallCaps"] = QFont::SmallCaps;
    env["QFont"]["Capitalize"] = QFont::Capitalize;

    env["QFont"]["PercentageSpacing"] = QFont::PercentageSpacing;
    env["QFont"]["AbsoluteSpacing"] = QFont::AbsoluteSpacing;

    env["QFont"]["UltraCondensed"] = QFont::UltraCondensed;
    env["QFont"]["ExtraCondensed"] = QFont::ExtraCondensed;
    env["QFont"]["Condensed"] = QFont::Condensed;
    env["QFont"]["SemiCondensed"] = QFont::SemiCondensed;
    env["QFont"]["Unstretched"] = QFont::Unstretched;
    env["QFont"]["SemiExpanded"] = QFont::SemiExpanded;
    env["QFont"]["Expanded"] = QFont::Expanded;
    env["QFont"]["ExtraExpanded"] = QFont::ExtraExpanded;
    env["QFont"]["UltraExpanded"] = QFont::UltraExpanded;

    env["QFont"]["StyleNormal"] = QFont::StyleNormal;
    env["QFont"]["StyleItalic"] = QFont::StyleItalic;
    env["QFont"]["StyleOblique"] = QFont::StyleOblique;

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

    env["QFont"]["Light"] = QFont::Light;
    env["QFont"]["Normal"] = QFont::Normal;
    env["QFont"]["DemiBold"] = QFont::DemiBold;
    env["QFont"]["Bold"] = QFont::Bold;
    env["QFont"]["Black"] = QFont::Black;

    return 0;
}

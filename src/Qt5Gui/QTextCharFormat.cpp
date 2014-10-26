#include "QTextCharFormat.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QStringList.hpp"
#include "QFont.hpp"
#include "QTextFormat.hpp"

int QTextCharFormat_setFont(lua_State* const state)
{
    return 0;
}

int QTextCharFormat_setFontStyleHint(lua_State* const state)
{
    return 0;
}

namespace lua {

void QTextCharFormat_metatable(lua_State* const state, const int pos)
{
    lua::QTextFormat_metatable(state, pos);

    lua::index mt(state, pos);
    mt["anchorHref"] = &QTextCharFormat::anchorHref;
    mt["anchorNames"] = &QTextCharFormat::anchorNames;
    mt["font"] = &QTextCharFormat::font;
    mt["fontCapitalization"] = &QTextCharFormat::fontCapitalization;
    mt["fontFamily"] = &QTextCharFormat::fontFamily;
    mt["fontFixedPitch"] = &QTextCharFormat::fontFixedPitch;
    mt["fontHintingPreference"] = &QTextCharFormat::fontHintingPreference;
    mt["fontItalic"] = &QTextCharFormat::fontItalic;
    mt["fontKerning"] = &QTextCharFormat::fontKerning;
    mt["fontLetterSpacing"] = &QTextCharFormat::fontLetterSpacing;
    mt["fontLetterSpacingType"] = &QTextCharFormat::fontLetterSpacingType;
    mt["fontOverline"] = &QTextCharFormat::fontOverline;
    mt["fontPointSize"] = &QTextCharFormat::fontPointSize;
    mt["fontStretch"] = &QTextCharFormat::fontStretch;
    mt["fontStrikeOut"] = &QTextCharFormat::fontStrikeOut;
    mt["fontStyleHint"] = &QTextCharFormat::fontStyleHint;
    mt["fontStyleStrategy"] = &QTextCharFormat::fontStyleStrategy;
    mt["fontUnderline"] = &QTextCharFormat::fontUnderline;
    mt["fontWeight"] = &QTextCharFormat::fontWeight;
    mt["fontWordSpacing"] = &QTextCharFormat::fontWordSpacing;
    mt["isAnchor"] = &QTextCharFormat::isAnchor;
    mt["isValid"] = &QTextCharFormat::isValid;
    mt["setAnchor"] = &QTextCharFormat::setAnchor;
    mt["setAnchorHref"] = &QTextCharFormat::setAnchorHref;
    mt["setAnchorNames"] = &QTextCharFormat::setAnchorNames;
    mt["setFont"] = QTextCharFormat_setFont;
    mt["setFontCapitalization"] = &QTextCharFormat::setFontCapitalization;
    mt["setFontFamily"] = &QTextCharFormat::setFontFamily;
    mt["setFontFixedPitch"] = &QTextCharFormat::setFontFixedPitch;
    mt["setFontHintingPreference"] = &QTextCharFormat::setFontHintingPreference;
    mt["setFontItalic"] = &QTextCharFormat::setFontItalic;
    mt["setFontKerning"] = &QTextCharFormat::setFontKerning;
    mt["setFontLetterSpacing"] = &QTextCharFormat::setFontLetterSpacing;
    mt["setFontLetterSpacingType"] = &QTextCharFormat::setFontLetterSpacingType;
    mt["setFontOverline"] = &QTextCharFormat::setFontOverline;
    mt["setFontPointSize"] = &QTextCharFormat::setFontPointSize;
    mt["setFontStretch"] = &QTextCharFormat::setFontStretch;
    mt["setFontStrikeOut"] = &QTextCharFormat::setFontStrikeOut;
    mt["setFontStyleHint"] = QTextCharFormat_setFontStyleHint;
    mt["setFontStyleStrategy"] = &QTextCharFormat::setFontStyleStrategy;
    mt["setFontUnderline"] = &QTextCharFormat::setFontUnderline;
    mt["setFontWeight"] = &QTextCharFormat::setFontWeight;
    mt["setFontWordSpacing"] = &QTextCharFormat::setFontWordSpacing;
    mt["setTextOutline"] = &QTextCharFormat::setTextOutline;
    mt["setToolTip"] = &QTextCharFormat::setToolTip;
    mt["setUnderlineColor"] = &QTextCharFormat::setUnderlineColor;
    mt["setUnderlineStyle"] = &QTextCharFormat::setUnderlineStyle;
    mt["setVerticalAlignment"] = &QTextCharFormat::setVerticalAlignment;
    mt["textOutline"] = &QTextCharFormat::textOutline;
    mt["toolTip"] = &QTextCharFormat::toolTip;
    mt["underlineColor"] = &QTextCharFormat::underlineColor;
    mt["underlineStyle"] = &QTextCharFormat::underlineStyle;
    mt["verticalAlignment"] = &QTextCharFormat::verticalAlignment;
}

} // namespace lua

int QTextCharFormat_new(lua_State* const state)
{
    lua::make<QTextCharFormat>(state);

    return 1;
}

int luaopen_luacxx_QTextCharFormat(lua_State* const state)
{
    lua::thread env(state);

    env["QTextCharFormat"] = lua::value::table;
    env["QTextCharFormat"]["new"] = QTextCharFormat_new;
    auto t = env["QTextCharFormat"];

    // enum QTextCharFormat::FontPropertiesInheritanceBehavior
    t["FontPropertiesSpecifiedOnly"] = QTextCharFormat::FontPropertiesSpecifiedOnly;
    t["FontPropertiesAll"] = QTextCharFormat::FontPropertiesAll;

    // enum QTextCharFormat::UnderlineStyle
    t["NoUnderline"] = QTextCharFormat::NoUnderline;
    t["SingleUnderline"] = QTextCharFormat::SingleUnderline;
    t["DashUnderline"] = QTextCharFormat::DashUnderline;
    t["DotLine"] = QTextCharFormat::DotLine;
    t["DashDotLine"] = QTextCharFormat::DashDotLine;
    t["DashDotDotLine"] = QTextCharFormat::DashDotDotLine;
    t["WaveUnderline"] = QTextCharFormat::WaveUnderline;
    t["SpellCheckUnderline"] = QTextCharFormat::SpellCheckUnderline;

    // enum QTextCharFormat::VerticalAlignment
    t["AlignNormal"] = QTextCharFormat::AlignNormal;
    t["AlignSuperScript"] = QTextCharFormat::AlignSuperScript;
    t["AlignSubScript"] = QTextCharFormat::AlignSubScript;
    t["AlignMiddle"] = QTextCharFormat::AlignMiddle;
    t["AlignBottom"] = QTextCharFormat::AlignBottom;
    t["AlignTop"] = QTextCharFormat::AlignTop;
    t["AlignBaseline"] = QTextCharFormat::AlignBaseline;

    return 0;
}

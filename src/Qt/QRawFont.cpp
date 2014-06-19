#include "QRawFont.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QRawFont.hpp"

#include <QRawFont>

int QRawFont_advancesForGlyphIndexes(lua_State* const state)
{
    return 0;
}

int QRawFont_supportsCharacter(lua_State* const state)
{
    return 0;
}

void lua::QRawFont_metatable(const lua::index& mt)
{
    mt["advancesForGlyphIndexes"] = QRawFont_advancesForGlyphIndexes;
    mt["alphaMapForGlyph"] = &QRawFont::alphaMapForGlyph;
    mt["ascent"] = &QRawFont::ascent;
    mt["averageCharWidth"] = &QRawFont::averageCharWidth;
    mt["boundingRect"] = &QRawFont::boundingRect;
    mt["descent"] = &QRawFont::descent;
    mt["familyName"] = &QRawFont::familyName;
    mt["fontTable"] = &QRawFont::fontTable;
    mt["glyphIndexesForChars"] = &QRawFont::glyphIndexesForChars;
    mt["glyphIndexesForString"] = &QRawFont::glyphIndexesForString;
    mt["hintingPreference"] = &QRawFont::hintingPreference;
    mt["isValid"] = &QRawFont::isValid;
    mt["leading"] = &QRawFont::leading;
    mt["lineThickness"] = &QRawFont::lineThickness;
    mt["loadFromData"] = &QRawFont::loadFromData;
    mt["loadFromFile"] = &QRawFont::loadFromFile;
    mt["maxCharWidth"] = &QRawFont::maxCharWidth;
    mt["pathForGlyph"] = &QRawFont::pathForGlyph;
    mt["pixelSize"] = &QRawFont::pixelSize;
    mt["setPixelSize"] = &QRawFont::setPixelSize;
    mt["style"] = &QRawFont::style;
    mt["styleName"] = &QRawFont::styleName;
    mt["supportedWritingSystems"] = &QRawFont::supportedWritingSystems;
    mt["supportsCharacter"] = QRawFont_supportsCharacter;
    mt["swap"] = &QRawFont::swap;
    mt["underlinePosition"] = &QRawFont::underlinePosition;
    mt["unitsPerEm"] = &QRawFont::unitsPerEm;
    mt["weight"] = &QRawFont::weight;
    mt["xHeight"] = &QRawFont::xHeight;
}

/*
    QRawFont()
    QRawFont(const QString & fileName, qreal pixelSize, QFont::HintingPreference hintingPreference = QFont::PreferDefaultHinting)
    QRawFont(const QByteArray & fontData, qreal pixelSize, QFont::HintingPreference hintingPreference = QFont::PreferDefaultHinting)
    QRawFont(const QRawFont & other)
*/
int QRawFont_new(lua_State* const state)
{
    lua::make<QRawFont>(state);

    return 1;
}

int luaopen_luacxx_QRawFont(lua_State* const state)
{
    lua::thread env(state);

    env["QRawFont"] = lua::value::table;
    env["QRawFont"]["new"] = QRawFont_new;

    env["QRawFont"]["PixelAntialiasing"] = QRawFont::PixelAntialiasing;
    env["QRawFont"]["SubPixelAntialiasing"] = QRawFont::SubPixelAntialiasing;

    env["QRawFont"]["SeparateAdvances"] = QRawFont::SeparateAdvances;
    env["QRawFont"]["KernedAdvances"] = QRawFont::KernedAdvances;
    env["QRawFont"]["UseDesignMetrics"] = QRawFont::UseDesignMetrics;

    return 0;
}

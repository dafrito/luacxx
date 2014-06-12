#include "QImage.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QImage>

int QImage_bits(lua_State* const state)
{
    return 0;
}

int QImage_convertToFormat(lua_State* const state)
{
    return 0;
}

int QImage_copy(lua_State* const state)
{
    return 0;
}

int QImage_fill(lua_State* const state)
{
    return 0;
}

int QImage_load(lua_State* const state)
{
    return 0;
}

int QImage_loadFromData(lua_State* const state)
{
    return 0;
}

int QImage_pixel(lua_State* const state)
{
    return 0;
}

int QImage_pixelIndex(lua_State* const state)
{
    return 0;
}

int QImage_save(lua_State* const state)
{
    return 0;
}

int QImage_scaled(lua_State* const state)
{
    return 0;
}

int QImage_scanLine(lua_State* const state)
{
    return 0;
}

int QImage_setPixel(lua_State* const state)
{
    return 0;
}

int QImage_transformed(lua_State* const state)
{
    return 0;
}

int QImage_valid(lua_State* const state)
{
    return 0;
}

void lua::QImage_metatable(const lua::index& mt)
{
    mt["allGray"] = &QImage::allGray;
    mt["bitPlaneCount"] = &QImage::bitPlaneCount;
    mt["bits"] = QImage_bits;
    mt["byteCount"] = &QImage::byteCount;
    mt["bytesPerLine"] = &QImage::bytesPerLine;
    mt["cacheKey"] = &QImage::cacheKey;
    mt["color"] = &QImage::color;
    mt["colorCount"] = &QImage::colorCount;
    mt["colorTable"] = &QImage::colorTable;
    mt["constBits"] = &QImage::constBits;
    mt["constScanLine"] = &QImage::constScanLine;
    mt["convertToFormat"] = QImage_convertToFormat;
    mt["copy"] = QImage_copy;
    mt["createAlphaMask"] = &QImage::createAlphaMask;
    mt["createHeuristicMask"] = &QImage::createHeuristicMask;
    mt["createMaskFromColor"] = &QImage::createMaskFromColor;
    mt["depth"] = &QImage::depth;
    mt["devicePixelRatio"] = &QImage::devicePixelRatio;
    mt["dotsPerMeterX"] = &QImage::dotsPerMeterX;
    mt["dotsPerMeterY"] = &QImage::dotsPerMeterY;
    mt["fill"] = QImage_fill;
    mt["format"] = &QImage::format;
    mt["hasAlphaChannel"] = &QImage::hasAlphaChannel;
    mt["height"] = &QImage::height;
    mt["invertPixels"] = &QImage::invertPixels;
    mt["isGrayscale"] = &QImage::isGrayscale;
    mt["isNull"] = &QImage::isNull;
    mt["load"] = QImage_load;
    mt["loadFromData"] = QImage_loadFromData;
    mt["mirrored"] = &QImage::mirrored;
    mt["offset"] = &QImage::offset;
    mt["pixel"] = QImage_pixel;
    mt["pixelIndex"] = QImage_pixelIndex;
    mt["rect"] = &QImage::rect;
    mt["rgbSwapped"] = &QImage::rgbSwapped;
    mt["save"] = QImage_save;
    mt["scaled"] = QImage_scaled;
    mt["scaledToHeight"] = &QImage::scaledToHeight;
    mt["scaledToWidth"] = &QImage::scaledToWidth;
    mt["scanLine"] = QImage_scanLine;
    mt["setColor"] = &QImage::setColor;
    mt["setColorCount"] = &QImage::setColorCount;
    mt["setColorTable"] = &QImage::setColorTable;
    mt["setDevicePixelRatio"] = &QImage::setDevicePixelRatio;
    mt["setDotsPerMeterX"] = &QImage::setDotsPerMeterX;
    mt["setDotsPerMeterY"] = &QImage::setDotsPerMeterY;
    mt["setOffset"] = &QImage::setOffset;
    mt["setPixel"] = QImage_setPixel;
    mt["setText"] = &QImage::setText;
    mt["size"] = &QImage::size;
    mt["swap"] = &QImage::swap;
    mt["text"] = &QImage::text;
    //mt["textKeys"] = &QImage::textKeys;
    mt["transformed"] = QImage_transformed;
    mt["valid"] = QImage_valid;
    mt["width"] = &QImage::width;
}


int QImage_new(lua::state* const state)
{
    lua::make<QImage>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QImage(lua::state* const state)
{
    lua::thread env(state);

    env["QImage"] = lua::value::table;
    env["QImage"]["new"] = QImage_new;

    auto t = env["QImage"];

    // enum QImage::Format
    t["Format_Invalid"] = QImage::Format_Invalid;
    t["Format_Mono"] = QImage::Format_Mono;
    t["Format_MonoLSB"] = QImage::Format_MonoLSB;
    t["Format_Indexed8"] = QImage::Format_Indexed8;
    t["Format_RGB32"] = QImage::Format_RGB32;
    t["Format_ARGB32"] = QImage::Format_ARGB32;
    t["Format_ARGB32_Premultiplied"] = QImage::Format_ARGB32_Premultiplied;
    t["Format_RGB16"] = QImage::Format_RGB16;
    t["Format_ARGB8565_Premultiplied"] = QImage::Format_ARGB8565_Premultiplied;
    t["Format_RGB666"] = QImage::Format_RGB666;
    t["Format_ARGB6666_Premultiplied"] = QImage::Format_ARGB6666_Premultiplied;
    t["Format_RGB555"] = QImage::Format_RGB555;
    t["Format_ARGB8555_Premultiplied"] = QImage::Format_ARGB8555_Premultiplied;
    t["Format_RGB888"] = QImage::Format_RGB888;
    t["Format_RGB444"] = QImage::Format_RGB444;
    t["Format_ARGB4444_Premultiplied"] = QImage::Format_ARGB4444_Premultiplied;
    t["Format_RGBX8888"] = QImage::Format_RGBX8888;
    t["Format_RGBA8888"] = QImage::Format_RGBA8888;
    t["Format_RGBA8888_Premultiplied"] = QImage::Format_RGBA8888_Premultiplied;

    // enum QImage::InvertMode
    t["InvertRgb"] = QImage::InvertRgb;
    t["InvertRgba"] = QImage::InvertRgba;

    return 0;
}

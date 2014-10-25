#include "QImageIOHandler.hpp"
#include "../thread.hpp"

#include <QImageIOHandler>

#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QIODevice.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/QByteArray.hpp"
#include "QImage.hpp"
#include "../Qt5Core/QVariant.hpp"

int QImageIOHandler_setFormat(lua_State* const state)
{
    return 0;
}

void lua::QImageIOHandler_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["currentImageNumber"] = &QImageIOHandler::currentImageNumber;
    mt["currentImageRect"] = &QImageIOHandler::currentImageRect;
    mt["device"] = &QImageIOHandler::device;
    mt["format"] = &QImageIOHandler::format;
    mt["imageCount"] = &QImageIOHandler::imageCount;
    mt["jumpToImage"] = &QImageIOHandler::jumpToImage;
    mt["jumpToNextImage"] = &QImageIOHandler::jumpToNextImage;
    mt["loopCount"] = &QImageIOHandler::loopCount;
    mt["nextImageDelay"] = &QImageIOHandler::nextImageDelay;
    mt["option"] = &QImageIOHandler::option;
    mt["read"] = &QImageIOHandler::read;
    mt["setDevice"] = &QImageIOHandler::setDevice;
    mt["setFormat"] = QImageIOHandler_setFormat;
    mt["setOption"] = &QImageIOHandler::setOption;
    mt["supportsOption"] = &QImageIOHandler::supportsOption;
    mt["write"] = &QImageIOHandler::write;
}

int QImageIOHandler_new(lua_State* const state)
{
    return 0;
}

int luaopen_luacxx_QImageIOHandler(lua_State* const state)
{
    lua::thread env(state);

    env["QImageIOHandler"] = lua::value::table;
    env["QImageIOHandler"]["new"] = QImageIOHandler_new;
    auto t = env["QImageIOHandler"];

    // enum QImageIOHandler::ImageOption
    t["Size"] = QImageIOHandler::Size;
    t["ClipRect"] = QImageIOHandler::ClipRect;
    t["ScaledSize"] = QImageIOHandler::ScaledSize;
    t["ScaledClipRect"] = QImageIOHandler::ScaledClipRect;
    t["Description"] = QImageIOHandler::Description;
    t["CompressionRatio"] = QImageIOHandler::CompressionRatio;
    t["Gamma"] = QImageIOHandler::Gamma;
    t["Quality"] = QImageIOHandler::Quality;
    t["Name"] = QImageIOHandler::Name;
    t["SubType"] = QImageIOHandler::SubType;
    t["IncrementalReading"] = QImageIOHandler::IncrementalReading;
    t["Endianness"] = QImageIOHandler::Endianness;
    t["Animation"] = QImageIOHandler::Animation;
    t["BackgroundColor"] = QImageIOHandler::BackgroundColor;
    t["ImageFormat"] = QImageIOHandler::ImageFormat;

    return 0;
}

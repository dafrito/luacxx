#include "QMimeData.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QObject.hpp"
#include "QVariant.hpp"
#include "QByteArray.hpp"
#include "QString.hpp"
#include "QStringList.hpp"
#include "QList.hpp"
#include "QUrl.hpp"
#include <iostream>

void lua::QMimeData_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["clear"] = &QMimeData::clear;
    mt["colorData"] = &QMimeData::colorData;
    mt["data"] = &QMimeData::data;
    mt["formats"] = &QMimeData::formats;
    mt["hasColor"] = &QMimeData::hasColor;
    mt["hasFormat"] = &QMimeData::hasFormat;
    mt["hasHtml"] = &QMimeData::hasHtml;
    mt["hasImage"] = &QMimeData::hasImage;
    mt["hasText"] = &QMimeData::hasText;
    mt["hasUrls"] = &QMimeData::hasUrls;
    mt["html"] = &QMimeData::html;
    mt["imageData"] = &QMimeData::imageData;
    mt["removeFormat"] = &QMimeData::removeFormat;
    mt["setColorData"] = &QMimeData::setColorData;
    mt["setData"] = &QMimeData::setData;
    mt["setHtml"] = &QMimeData::setHtml;
    mt["setImageData"] = &QMimeData::setImageData;
    mt["setText"] = &QMimeData::setText;
    mt["setUrls"] = &QMimeData::setUrls;
    mt["text"] = &QMimeData::text;
    mt["urls"] = &QMimeData::urls;
}

int QMimeData_new(lua_State* const state)
{
    lua::make<QMimeData>(state);
    std::cerr << "Creating QMimeData\n";
    return 1;
}

int luaopen_Qt5Core_QMimeData(lua_State* const state)
{
    lua::thread env(state);

    env["QMimeData"] = lua::value::table;
    env["QMimeData"]["new"] = QMimeData_new;

    return 0;
}

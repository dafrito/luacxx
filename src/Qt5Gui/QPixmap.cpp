#include "QPixmap.hpp"

#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QSize.hpp"
#include "QPaintDevice.hpp"
#include "QColor.hpp"
#include "QBitmap.hpp"

int QPixmap_fill(lua_State* const state)
{
    return 0;
}

int QPixmap_loadFromData(lua_State* const state)
{
    return 0;
}

int QPixmap_transformed(lua_State* const state)
{
    return 0;
}

int QPixmap_scroll(lua_State* const state)
{
    return 0;
}

int QPixmap_scaled(lua_State* const state)
{
    return 0;
}

int QPixmap_save(lua_State* const state)
{
    return 0;
}

void lua::QPixmap_metatable(lua_State* const state, const int pos)
{
    lua::QPaintDevice_metatable(state, pos);

    lua::index mt(state, pos);
    mt["createHeuristicMask"] = &QPixmap::createHeuristicMask;
    mt["createMaskFromColor"] = &QPixmap::createMaskFromColor;
    mt["depth"] = &QPixmap::depth;
    mt["detach"] = &QPixmap::detach;
    mt["devicePixelRatio"] = &QPixmap::devicePixelRatio;
    mt["fill"] = QPixmap_fill;
    mt["hasAlpha"] = &QPixmap::hasAlpha;
    mt["hasAlphaChannel"] = &QPixmap::hasAlphaChannel;
    mt["height"] = &QPixmap::height;
    mt["isNull"] = &QPixmap::isNull;
    mt["isQBitmap"] = &QPixmap::isQBitmap;
    mt["load"] = &QPixmap::load;
    mt["loadFromData"] = QPixmap_loadFromData;
    mt["mask"] = &QPixmap::mask;
    mt["rect"] = &QPixmap::rect;
    mt["save"] = QPixmap_save;
    mt["scaled"] = QPixmap_scaled;
    mt["scaledToHeight"] = &QPixmap::scaledToHeight;
    mt["scaledToWidth"] = &QPixmap::scaledToWidth;
    mt["scroll"] = QPixmap_scroll;
    mt["setDevicePixelRatio"] = &QPixmap::setDevicePixelRatio;
    mt["setMask"] = &QPixmap::setMask;
    mt["size"] = &QPixmap::size;
    mt["swap"] = &QPixmap::swap;
    mt["toImage"] = &QPixmap::toImage;
    mt["transformed"] = QPixmap_transformed;
    mt["width"] = &QPixmap::width;
}

int QPixmap_new(lua_State* const state)
{
    lua::make<QPixmap>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Gui_QPixmap(lua_State* const state)
{
    lua::thread env(state);

    env["QPixmap"] = lua::value::table;
    env["QPixmap"]["new"] = QPixmap_new;

    return 0;
}

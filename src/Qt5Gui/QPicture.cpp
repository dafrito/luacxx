#include "QPicture.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QPicture>

#include "QPaintDevice.hpp"
#include "../Qt5Core/QRect.hpp"
#include "QPainter.hpp"

void lua::QPicture_metatable(const lua::index& mt)
{
    lua::QPaintDevice_metatable(mt);

    mt["boundingRect"] = &QPaintDevice::boundingRect;
    mt["data"] = &QPaintDevice::data;
    mt["isNull"] = &QPaintDevice::isNull;
    mt["load"] = QPaintDevice_load;
    mt["play"] = &QPaintDevice::play;
    mt["save"] = QPaintDevice_save;
    mt["setBoundingRect"] = &QPaintDevice::setBoundingRect;
    mt["setData"] = &QPaintDevice::setData;
    mt["size"] = &QPaintDevice::size;
    mt["swap"] = &QPaintDevice::swap;
}

int QPicture_new(lua_State* const state)
{
    // QPicture(int formatVersion = -1)
    // QPicture(const QPicture & pic)
    lua::make<QPicture>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QPicture(lua_State* const state)
{
    lua::thread env(state);

    env["QPicture"] = lua::value::table;
    env["QPicture"]["new"] = QPicture_new;
    auto t = env["QPicture"];

    return 0;
}

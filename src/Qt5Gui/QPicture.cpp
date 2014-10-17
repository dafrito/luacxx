#include "QPicture.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QPicture>

#include "QPaintDevice.hpp"
#include "../Qt5Core/QRect.hpp"
#include "QPainter.hpp"

int QPicture_load(lua_State* const state)
{
    return 0;
}

int QPicture_save(lua_State* const state)
{
    return 0;
}

void lua::QPicture_metatable(lua_State* const state, const int pos)
{
    lua::QPaintDevice_metatable(state, pos);

    lua::index mt(state, pos);
    mt["boundingRect"] = &QPicture::boundingRect;
    mt["data"] = &QPicture::data;
    mt["isNull"] = &QPicture::isNull;
    mt["load"] = QPicture_load;
    mt["play"] = &QPicture::play;
    mt["save"] = QPicture_save;
    mt["setBoundingRect"] = &QPicture::setBoundingRect;
    mt["setData"] = &QPicture::setData;
    mt["size"] = &QPicture::size;
    mt["swap"] = &QPicture::swap;
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

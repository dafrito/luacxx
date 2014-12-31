#include "QPicture.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QPicture>

#include "QPaintDevice.hpp"
#include "../Qt5Core/QRect.hpp"
#include "QPainter.hpp"

#include "../Qt5Core/QIODevice.hpp"

int QPicture_load(lua_State* const state)
{
    auto self = lua::get<QPicture*>(state, 1);
    if (lua::is_type<QIODevice>(state, 2)) {
        // bool    load ( QIODevice * dev, const char * format = 0 )
        if (lua_gettop(state) == 2) {
            lua::push(state, self->load(
                lua::get<QIODevice*>(state, 2)
            ));
        } else {
            lua::push(state, self->load(
                lua::get<QIODevice*>(state, 2),
                lua::get<const char*>(state, 3)
            ));
        }
    } else {
        // bool    load ( const QString & fileName, const char * format = 0 )
        if (lua_gettop(state) == 2) {
            lua::push(state, self->load(
                lua::get<QString>(state, 2)
            ));
        } else {
            lua::push(state, self->load(
                lua::get<QString>(state, 2),
                lua::get<const char*>(state, 3)
            ));
        }
    }
    return 1;
}

int QPicture_save(lua_State* const state)
{
    auto self = lua::get<QPicture*>(state, 1);
    if (lua::is_type<QIODevice>(state, 2)) {
        // bool    save ( QIODevice * dev, const char * format = 0 )
        if (lua_gettop(state) == 2) {
            lua::push(state, self->save(
                lua::get<QIODevice*>(state, 2)
            ));
        } else {
            lua::push(state, self->save(
                lua::get<QIODevice*>(state, 2),
                lua::get<const char*>(state, 3)
            ));
        }
    } else {
        // bool    save ( const QString & fileName, const char * format = 0 )
        if (lua_gettop(state) == 2) {
            lua::push(state, self->save(
                lua::get<QString>(state, 2)
            ));
        } else {
            lua::push(state, self->save(
                lua::get<QString>(state, 2),
                lua::get<const char*>(state, 3)
            ));
        }
    }
    return 1;
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
    if (lua_gettop(state) == 0) {
        // QPicture()
        lua::make<QPicture>(state);
    } else if (lua::is_type<QPicture>(state, 1)) {
        // QPicture(const QPicture & pic)
        lua::make<QPicture>(state,
            lua::get<const QPicture&>(state, 1)
        );
    } else {
        // QPicture(int formatVersion = -1)
        lua::make<QPicture>(state,
            lua::get<int>(state, 1)
        );
    }

    return 1;
}

int luaopen_Qt5Gui_QPicture(lua_State* const state)
{
    lua::thread env(state);

    env["QPicture"] = lua::value::table;
    env["QPicture"]["new"] = QPicture_new;
    auto t = env["QPicture"];

    return 0;
}

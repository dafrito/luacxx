#include "QPointF.hpp"
#include "../lua-cxx/type/function.hpp"
#include "../lua-cxx/thread.hpp"

#include <QPointF>

void lua::QPointF_metatable(const lua::index& mt)
{
    mt["isNull"] = &QPointF::isNull;
    mt["manhattanLength"] = &QPointF::manhattanLength;
    mt["x"] = &QPointF::x;
    mt["y"] = &QPointF::y;
    mt["setX"] = &QPointF::setX;
    mt["setY"] = &QPointF::setY;
}

int QPointF_new(lua_State* const state)
{
    if (lua_gettop(state) > 1) {
        lua::make<QPointF>(state,
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        );
    } else {
        lua::make<QPointF>(state);
    }
    return 1;
}

int luaopen_luacxx_QPointF(lua_State* const state)
{
    lua::thread env(state);

    env["QPointF"] = lua::value::table;
    env["QPointF"]["new"] = QPointF_new;
    env["QPointF"]["dotProduct"] = &QPointF::dotProduct;

    return 0;
}

#include "QPoint.hpp"
#include "../luacxx/convert/callable.hpp"
#include "../luacxx/convert/numeric.hpp"
#include "../luacxx/thread.hpp"

#include <QPoint>

void lua::QPoint_metatable(const lua::index& mt)
{
    mt["isNull"] = &QPoint::isNull;
    mt["manhattanLength"] = &QPoint::manhattanLength;
    mt["x"] = &QPoint::x;
    mt["y"] = &QPoint::y;
    mt["setX"] = &QPoint::setX;
    mt["setY"] = &QPoint::setY;
}

int QPoint_new(lua_State* const state)
{
    if (lua_gettop(state) > 1) {
        lua::make<QPoint>(state,
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        );
    } else {
        lua::make<QPoint>(state);
    }
    return 1;
}

int luaopen_Qt5Core_QPoint(lua_State* const state)
{
    lua::thread env(state);

    env["QPoint"] = lua::value::table;
    env["QPoint"]["new"] = QPoint_new;

    return 0;
}

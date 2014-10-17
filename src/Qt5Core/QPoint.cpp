#include "QPoint.hpp"
#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"
#include "../algorithm.hpp"
#include "QVariant.hpp"

#include <QPoint>

void lua::QPoint_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

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

    lua::set_qvariant_push_handler(QVariant::Point, [](lua_State* const state, const QVariant& source) {
       auto target = lua::push(state, lua::value::table);

        auto point = source.toPoint();
        target["x"] = point.x();
        target["y"] = point.y();
    });

    lua::set_qvariant_store_handler(QVariant::Point, [](QVariant& sink, const lua::index& point) {
        if (!point.type().table()) {
            throw lua::error("Point must be a table");
        }

        if (lua::table::length(point) > 0) {
            sink.setValue(QPoint(
                point[1].get<int>(),
                point[2].get<int>()
            ));
        } else {
            sink.setValue(QPoint(
                point["x"].get<int>(),
                point["y"].get<int>()
            ));
        }
    });

    return 0;
}

#include "QPointF.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../algorithm.hpp"
#include "QVariant.hpp"

#include <QPointF>

void lua::QPointF_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

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

int luaopen_Qt5Core_QPointF(lua_State* const state)
{
    lua::thread env(state);

    env["QPointF"] = lua::value::table;
    env["QPointF"]["new"] = QPointF_new;
    env["QPointF"]["dotProduct"] = &QPointF::dotProduct;

    lua::set_qvariant_push_handler(QVariant::PointF, [](lua_State* const state, const QVariant& source) {
        auto target = lua::push(state, lua::value::table);

        auto point = source.toPoint();
        target["x"] = point.x();
        target["y"] = point.y();
    });

    lua::set_qvariant_store_handler(QVariant::PointF, [](QVariant& sink, const lua::index& point) {
        if (!point.type().table()) {
            throw lua::error("Point must be a table");
        }

        if (lua::table::length(point) > 0) {
            sink.setValue(QPointF(
                point[1].get<qreal>(),
                point[2].get<qreal>()
            ));
        } else {
            sink.setValue(QPointF(
                point["x"].get<qreal>(),
                point["y"].get<qreal>()
            ));
        }
    });

    return 0;
}

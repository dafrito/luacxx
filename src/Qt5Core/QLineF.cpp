#include "QLineF.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QPointF.hpp"
#include "QLine.hpp"

int QLineF_translate(lua_State* const state)
{
    return 0;
}
int QLineF_translated(lua_State* const state)
{
    return 0;
}
int QLineF_angle(lua_State* const state)
{
    return 0;
}

namespace lua {

void QLineF_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["p1"] = &QLineF::p1;
    mt["p2"] = &QLineF::p2;
    mt["x1"] = &QLineF::x1;
    mt["x2"] = &QLineF::x2;
    mt["y1"] = &QLineF::y1;
    mt["y2"] = &QLineF::y2;
    mt["angle"] = QLineF_angle;
    mt["angleTo"] = &QLineF::angleTo;
    mt["dx"] = &QLineF::dx;
    mt["dy"] = &QLineF::dy;
    mt["intersect"] = &QLineF::intersect;
    mt["isNull"] = &QLineF::isNull;
    mt["length"] = &QLineF::length;
    mt["normalVector"] = &QLineF::normalVector;
    mt["pointAt"] = &QLineF::pointAt;
    mt["setP1"] = &QLineF::setP1;
    mt["setP2"] = &QLineF::setP2;
    mt["setAngle"] = &QLineF::setAngle;
    mt["setLength"] = &QLineF::setLength;
    mt["setLine"] = &QLineF::setLine;
    mt["setPoints"] = &QLineF::setPoints;
    mt["toLine"] = &QLineF::toLine;
    mt["translate"] = QLineF_translate;
    mt["translated"] = QLineF_translated;
    mt["unitVector"] = &QLineF::unitVector;
}

} // namespace lua

int QLineF_new(lua_State* const state)
{
    // QLineF()
    // QLineF(const QPointF & p1, const QPointF & p2)
    // QLineF(qreal x1, qreal y1, qreal x2, qreal y2)
    // QLineF(const QLine & line)
    lua::make<QLineF>(state);

    return 1;
}

int luaopen_luacxx_QLineF(lua_State* const state)
{
    lua::thread env(state);

    env["QLineF"] = lua::value::table;
    env["QLineF"]["new"] = QLineF_new;
    auto t = env["QLineF"];

    t["fromPolar"] = QLineF::fromPolar;

    // enum QLineF::IntersectType
    t["UnboundedIntersection"] = QLineF::UnboundedIntersection;
    t["NoIntersection"] = QLineF::NoIntersection;
    t["UnboundedIntersection"] = QLineF::UnboundedIntersection;
    t["BoundedIntersection"] = QLineF::BoundedIntersection;

    return 0;
}

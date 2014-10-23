#include "QLine.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QPoint.hpp"

int QLine_translate(lua_State* const state)
{
    return 0;
}
int QLine_translated(lua_State* const state)
{
    return 0;
}

namespace lua {

void QLine_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["p1"] = &QLine::p1;
    mt["p2"] = &QLine::p2;
    mt["x1"] = &QLine::x1;
    mt["x2"] = &QLine::x2;
    mt["y1"] = &QLine::y1;
    mt["y2"] = &QLine::y2;
    mt["dx"] = &QLine::dx;
    mt["dy"] = &QLine::dy;
    mt["isNull"] = &QLine::isNull;
    mt["setP1"] = &QLine::setP1;
    mt["setP2"] = &QLine::setP2;
    mt["setLine"] = &QLine::setLine;
    mt["setPoints"] = &QLine::setPoints;
    mt["translate"] = QLine_translate;
    mt["translated"] = QLine_translated;
}

} // namespace lua

int QLine_new(lua_State* const state)
{
    // QLine()
    // QLine(const QPoint & p1, const QPoint & p2)
    // QLine(int x1, int y1, int x2, int y2)
    lua::make<QLine>(state);

    return 1;
}

int luaopen_luacxx_QLine(lua_State* const state)
{
    lua::thread env(state);

    env["QLine"] = lua::value::table;
    env["QLine"]["new"] = QLine_new;
    auto t = env["QLine"];

    return 0;
}

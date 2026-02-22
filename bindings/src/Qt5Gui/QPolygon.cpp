#include "QPolygon.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/Qt.hpp"

int QPolygon_point(lua_State* const state)
{
    return 0;
}
int QPolygon_putPoints(lua_State* const state)
{
    return 0;
}
int QPolygon_setPoint(lua_State* const state)
{
    return 0;
}
int QPolygon_setPoints(lua_State* const state)
{
    return 0;
}
int QPolygon_translate(lua_State* const state)
{
    return 0;
}
int QPolygon_translated(lua_State* const state)
{
    return 0;
}

void lua::QPolygon_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["boundingRect"] = &QPolygon::boundingRect;
    mt["containsPoint"] = &QPolygon::containsPoint;
    mt["intersected"] = &QPolygon::intersected;
    mt["point"] = QPolygon_point;
    mt["putPoints"] = QPolygon_putPoints;
    mt["setPoint"] = QPolygon_setPoint;
    mt["setPoints"] = QPolygon_setPoints;
    mt["subtracted"] = &QPolygon::subtracted;
    mt["swap"] = &QPolygon::swap;
    mt["translate"] = QPolygon_translate;
    mt["translated"] = QPolygon_translated;
    mt["united"] = &QPolygon::united;
}

int QPolygon_new(lua_State* const state)
{
    // QPolygon()
    // QPolygon(int size)
    // QPolygon(const QPolygon & polygon)
    // QPolygon(const QVector<QPoint> & points)
    // QPolygon(const QRect & rectangle, bool closed = false)
    lua::make<QPolygon>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Gui_QPolygon(lua_State* const state)
{
    lua::thread env(state);

    env["QPolygon"] = lua::value::table;
    env["QPolygon"]["new"] = QPolygon_new;
    auto t = env["QPolygon"];

    return 0;
}

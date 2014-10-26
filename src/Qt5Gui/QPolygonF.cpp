#include "QPolygonF.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QPolygonF>

#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/Qt.hpp"
#include "QPolygon.hpp"
#include "../Qt5Core/QVector.hpp"
#include "../std/vector.hpp"

int QPolygonF_translate(lua_State* const state)
{
    return 0;
}

int QPolygonF_translated(lua_State* const state)
{
    return 0;
}

void lua::QPolygonF_metatable(lua_State* const state, const int pos)
{
    lua::QVector_metatable<QPointF>(state, pos);

    lua::index mt(state, pos);
    mt["boundingRect"] = &QPolygonF::boundingRect;
    mt["containsPoint"] = &QPolygonF::containsPoint;
    mt["intersected"] = &QPolygonF::intersected;
    mt["isClosed"] = &QPolygonF::isClosed;
    mt["subtracted"] = &QPolygonF::subtracted;
    mt["swap"] = &QPolygonF::swap;
    mt["toPolygon"] = &QPolygonF::toPolygon;
    mt["translate"] = QPolygonF_translate;
    mt["translated"] = QPolygonF_translated;
    mt["united"] = &QPolygonF::united;
}

int QPolygonF_new(lua_State* const state)
{
    // QPolygonF()
    // QPolygonF(int size)
    // QPolygonF(const QPolygonF & polygon)
    // QPolygonF(const QVector<QPointF> & points)
    // QPolygonF(const QRectF & rectangle)
    // QPolygonF(const QPolygon & polygon)
    lua::make<QPolygonF>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Gui_QPolygonF(lua_State* const state)
{
    lua::thread env(state);

    env["QPolygonF"] = lua::value::table;
    env["QPolygonF"]["new"] = QPolygonF_new;
    auto t = env["QPolygonF"];

    return 0;
}

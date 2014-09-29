#include "QPolygonF.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QPolygonF>

#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QPolygon.hpp"
#include "../Qt5Core/QVector.hpp"

void lua::QPolygonF_metatable(const lua::index& mt)
{
    lua::QVector_metatable<QPointF>(mt);

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

int luaopen_luacxx_QPolygonF(lua_State* const state)
{
    lua::thread env(state);

    env["QPolygonF"] = lua::value::table;
    env["QPolygonF"]["new"] = QPolygonF_new;
    auto t = env["QPolygonF"];

    return 0;
}

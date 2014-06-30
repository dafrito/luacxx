#include "QPainterPath.hpp"
#include "../luacxx/type/function.hpp"
#include "../luacxx/thread.hpp"
#include "QTransform.hpp"
#include "QPointF.hpp"
#include "QMatrix.hpp"
#include "QRectF.hpp"
#include "QList.hpp"

#include <QPainterPath>

// https://qt-project.org/doc/qt-5/qpainterpath.html

/*

void    addEllipse(const QRectF & boundingRectangle)
void    addEllipse(qreal x, qreal y, qreal width, qreal height)
void    addEllipse(const QPointF & center, qreal rx, qreal ry)

*/
int QPainterPath_addEllipse(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    switch (lua_gettop(state)) {
    case 2:
        self->addEllipse(lua::get<const QRectF&>(state, 2));
        return 0;
    case 3:
        self->addEllipse(
            lua::get<const QPointF&>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        );
        return 0;
    default:
        self->addEllipse(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        );
        return 0;
    }
}

/*

void    addRect(const QRectF & rectangle)
void    addRect(qreal x, qreal y, qreal width, qreal height)

*/
int QPainterPath_addRect(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 2) {
        self->addRect(lua::get<const QRectF&>(state, 2));
        return 0;
    }
    self->addRect(
        lua::get<qreal>(state, 2),
        lua::get<qreal>(state, 3),
        lua::get<qreal>(state, 4),
        lua::get<qreal>(state, 5)
    );
    return 0;
}

/*

void    addRoundedRect(const QRectF & rect, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize)
void    addRoundedRect(qreal x, qreal y, qreal w, qreal h, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize)

*/
int QPainterPath_addRoundedRect(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 4) {
        self->addRoundedRect(
            lua::get<const QRectF&>(state, 2),
            lua::get<qreal>(state, 3), // xRadius
            lua::get<qreal>(state, 4) // yRadius
        );
        return 0;
    }
    if (lua_gettop(state) == 5) {
        self->addRoundedRect(
            lua::get<const QRectF&>(state, 2),
            lua::get<qreal>(state, 3), // xRadius
            lua::get<qreal>(state, 4), // yRadius
            lua::get<Qt::SizeMode>(state, 5) // mode
        );
        return 0;
    }
    if (lua_gettop(state) == 7) {
        self->addRoundedRect(
            lua::get<qreal>(state, 2), // x
            lua::get<qreal>(state, 3), // y
            lua::get<qreal>(state, 4), // width
            lua::get<qreal>(state, 5), // height
            lua::get<qreal>(state, 6), // xRadius
            lua::get<qreal>(state, 7) // yRadius
        );
        return 0;
    }
    self->addRoundedRect(
        lua::get<qreal>(state, 2), // x
        lua::get<qreal>(state, 3), // y
        lua::get<qreal>(state, 4), // width
        lua::get<qreal>(state, 5), // height
        lua::get<qreal>(state, 6), // xRadius
        lua::get<qreal>(state, 7), // yRadius
        lua::get<Qt::SizeMode>(state, 8) // mode
    );
    return 0;
}

/*

void    addText(const QPointF & point, const QFont & font, const QString & text)
void    addText(qreal x, qreal y, const QFont & font, const QString & text)

*/
int QPainterPath_addText(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 4) {
        self->addText(
            lua::get<const QPointF&>(state, 2),
            lua::get<const QFont&>(state, 3),
            lua::get<const QString&>(state, 4)
        );
        return 0;
    }
    self->addText(
        lua::get<qreal>(state, 2),
        lua::get<qreal>(state, 3),
        lua::get<const QFont&>(state, 3),
        lua::get<const QString&>(state, 4)
    );
    return 0;
}

/*

void    arcMoveTo(const QRectF & rectangle, qreal angle)
void    arcMoveTo(qreal x, qreal y, qreal width, qreal height, qreal angle)

*/
int QPainterPath_arcMoveTo(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 3) {
        self->arcMoveTo(lua::get<const QRectF&>(state, 2), lua::get<qreal>(state, 3));
        return 0;
    }
    self->arcMoveTo(
        lua::get<qreal>(state, 2),
        lua::get<qreal>(state, 3),
        lua::get<qreal>(state, 4),
        lua::get<qreal>(state, 5),
        lua::get<qreal>(state, 6)
    );
    return 0;
}

/*

void    arcTo(const QRectF & rectangle, qreal startAngle, qreal sweepLength)
void    arcTo(qreal x, qreal y, qreal width, qreal height, qreal startAngle, qreal sweepLength)

*/
int QPainterPath_arcTo(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 3) {
        self->arcTo(
            lua::get<const QRectF&>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        );
        return 0;
    }
    self->arcTo(
        lua::get<qreal>(state, 2), // x
        lua::get<qreal>(state, 3), // y
        lua::get<qreal>(state, 4), // width
        lua::get<qreal>(state, 5), // height
        lua::get<qreal>(state, 6), // startAngle
        lua::get<qreal>(state, 7) // sweepLength
    );
    return 0;
}

/*

bool    contains(const QPointF & point) const
bool    contains(const QRectF & rectangle) const
bool    contains(const QPainterPath & p) const

*/
int QPainterPath_contains(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua::is_type<QRectF>(state, 2)) {
        lua::push(state, self->contains(lua::get<const QRectF&>(state, 2)));
        return 1;
    }
    if (lua::is_type<QPointF>(state, 2)) {
        lua::push(state, self->contains(lua::get<const QPointF&>(state, 2)));
        return 1;
    }
    lua::push(state, self->intersects(lua::get<const QPainterPath&>(state, 2)));
    return 1;
}

/*

void    cubicTo(const QPointF & c1, const QPointF & c2, const QPointF & endPoint)
void    cubicTo(qreal c1X, qreal c1Y, qreal c2X, qreal c2Y, qreal endPointX, qreal endPointY)

*/
int QPainterPath_cubicTo(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 4) {
        self->cubicTo(
            lua::get<const QPointF&>(state, 2),
            lua::get<const QPointF&>(state, 3),
            lua::get<const QPointF&>(state, 4)
        );
        return 0;
    }
    self->cubicTo(
        lua::get<qreal>(state, 2), // c1x
        lua::get<qreal>(state, 3), // c1y
        lua::get<qreal>(state, 4), // c2x
        lua::get<qreal>(state, 5), // c2y
        lua::get<qreal>(state, 6), // endPointX
        lua::get<qreal>(state, 7) // endPointY
    );
    return 0;
}

/*

bool    intersects(const QRectF & rectangle) const
bool    intersects(const QPainterPath & p) const

*/
int QPainterPath_intersects(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua::is_type<QRectF>(state, 2)) {
        lua::push(state, self->intersects(lua::get<const QRectF&>(state, 2)));
        return 1;
    }
    lua::push(state, self->intersects(lua::get<const QPainterPath&>(state, 2)));
    return 1;
}

/*

void    lineTo(const QPointF & endPoint)
void    lineTo(qreal x, qreal y)

*/
int QPainterPath_lineTo(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 2) {
        self->lineTo(lua::get<const QPointF&>(state, 2));
        return 0;
    }
    self->lineTo(
        lua::get<qreal>(state, 2),
        lua::get<qreal>(state, 3)
    );
    return 0;
}

/*

void    moveTo(const QPointF & point)
void    moveTo(qreal x, qreal y)

*/
int QPainterPath_moveTo(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 2) {
        self->moveTo(lua::get<const QPointF&>(state, 2));
        return 0;
    }
    self->moveTo(
        lua::get<qreal>(state, 2),
        lua::get<qreal>(state, 3)
    );
    return 0;
}

/*

void    quadTo(const QPointF & c, const QPointF & endPoint)
void    quadTo(qreal cx, qreal cy, qreal endPointX, qreal endPointY)

*/
int QPainterPath_quadTo(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 3) {
        self->quadTo(
            lua::get<const QPointF&>(state, 2),
            lua::get<const QPointF&>(state, 3)
        );
        return 0;
    }
    self->quadTo(
        lua::get<qreal>(state, 2),
        lua::get<qreal>(state, 3),
        lua::get<qreal>(state, 4),
        lua::get<qreal>(state, 5)
    );
    return 0;
}

/*

QPolygonF   toFillPolygon(const QTransform & matrix) const
QPolygonF   toFillPolygon(const QMatrix & matrix = QMatrix()) const
QList<QPolygonF>    toFillPolygons(const QTransform & matrix) const
QList<QPolygonF>    toFillPolygons(const QMatrix & matrix = QMatrix()) const
QList<QPolygonF>    toSubpathPolygons(const QTransform & matrix) const
QList<QPolygonF>    toSubpathPolygons(const QMatrix & matrix = QMatrix()) const

*/
int QPainterPath_toFillPolygon(lua_State* const state)
{
    return 0;
}

int QPainterPath_toFillPolygons(lua_State* const state)
{
    return 0;
}

int QPainterPath_toSubpathPolygons(lua_State* const state)
{
    return 0;
}

/*

void    translate(qreal dx, qreal dy)
void    translate(const QPointF & offset)
QPainterPath    translated(qreal dx, qreal dy) const
QPainterPath    translated(const QPointF & offset) const

*/

int QPainterPath_translate(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 2) {
        self->translate(lua::get<const QPointF&>(state, 2));
        return 0;
    }
    self->translate(
        lua::get<qreal>(state, 2),
        lua::get<qreal>(state, 3)
    );
    return 0;
}

int QPainterPath_translated(lua_State* const state)
{
    auto self = lua::get<QPainterPath*>(state, 1);
    if (lua_gettop(state) == 2) {
        lua::push(state, self->translated(lua::get<const QPointF&>(state, 2)));
        return 1;
    }
    lua::push(state, self->translated(
        lua::get<qreal>(state, 2),
        lua::get<qreal>(state, 3)
    ));
    return 1;
}

void lua::QPainterPath_metatable(const lua::index& mt)
{
    mt["addEllipse"] = QPainterPath_addEllipse;
    mt["addPath"] = &QPainterPath::addPath;
    mt["addPolygon"] = &QPainterPath::addPolygon;
    mt["addRect"] = QPainterPath_addRect;
    mt["addRegion"] = &QPainterPath::addRegion;
    mt["addRoundedRect"] = QPainterPath_addRoundedRect;
    mt["addText"] = QPainterPath_addText;
    mt["angleAtPercent"] = &QPainterPath::angleAtPercent;
    mt["arcMoveTo"] = QPainterPath_arcMoveTo;
    mt["arcTo"] = QPainterPath_arcTo;
    mt["boundingRect"] = &QPainterPath::boundingRect;
    mt["closeSubpath"] = &QPainterPath::closeSubpath;
    mt["connectPath"] = &QPainterPath::connectPath;
    mt["contains"] = QPainterPath_contains;
    mt["controlPointRect"] = &QPainterPath::controlPointRect;
    mt["cubicTo"] = QPainterPath_cubicTo;
    mt["currentPosition"] = &QPainterPath::currentPosition;
    mt["elementAt"] = &QPainterPath::elementAt;
    mt["elementCount"] = &QPainterPath::elementCount;
    mt["fillRule"] = &QPainterPath::fillRule;
    mt["intersected"] = &QPainterPath::intersected;
    mt["intersects"] = QPainterPath_intersects;
    mt["isEmpty"] = &QPainterPath::isEmpty;
    mt["length"] = &QPainterPath::length;
    mt["lineTo"] = QPainterPath_lineTo;
    mt["moveTo"] = QPainterPath_moveTo;
    mt["percentAtLength"] = &QPainterPath::percentAtLength;
    mt["pointAtPercent"] = &QPainterPath::pointAtPercent;
    mt["quadTo"] = QPainterPath_quadTo;
    mt["setElementPositionAt"] = &QPainterPath::setElementPositionAt;
    mt["setFillRule"] = &QPainterPath::setFillRule;
    mt["simplified"] = &QPainterPath::simplified;
    mt["slopeAtPercent"] = &QPainterPath::slopeAtPercent;
    mt["subtracted"] = &QPainterPath::subtracted;
    mt["swap"] = &QPainterPath::swap;
    mt["toFillPolygon"] = QPainterPath_toFillPolygon;
    mt["toFillPolygons"] = QPainterPath_toFillPolygons;
    mt["toReversed"] = &QPainterPath::toReversed;
    mt["toSubpathPolygons"] = QPainterPath_toSubpathPolygons;
    mt["translate"] = QPainterPath_translate;
    mt["translated"] = QPainterPath_translated;
    mt["united"] = &QPainterPath::united;
}

void lua::QPainterPath_Element_metatable(const lua::index& mt)
{
    mt["isCurveTo"] = &QPainterPath::Element::isCurveTo;
    mt["isLineTo"] = &QPainterPath::Element::isLineTo;
    mt["isMoveTo"] = &QPainterPath::Element::isMoveTo;
}

int QPainterPath_new(lua_State* const state)
{
    if (lua_gettop(state) <= 1) {
        lua::make<QPainterPath>(state);
        return 1;
    }
    if (lua::is_type<QPainterPath>(state, 2)) {
        lua::make<QPainterPath>(state, lua::get<const QPainterPath&>(state, 2));
        return 1;
    }

    lua::make<QPainterPath>(state, lua::get<const QPointF&>(state, 2));
    return 1;
}

int luaopen_luacxx_QPainterPath(lua_State* const state)
{
    lua::thread env(state);

    env["QPainterPath"] = lua::value::table;
    env["QPainterPath"]["new"] = QPainterPath_new;

    return 0;
}

#include "QPainterPath.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
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
    return 0;
}

/*

void    addRect(const QRectF & rectangle)
void    addRect(qreal x, qreal y, qreal width, qreal height)

*/
int QPainterPath_addRect(lua_State* const state)
{
    return 0;
}

/*

void    addRoundedRect(const QRectF & rect, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize)
void    addRoundedRect(qreal x, qreal y, qreal w, qreal h, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize)

*/
int QPainterPath_addRoundedRect(lua_State* const state)
{
    return 0;
}

/*

void    addText(const QPointF & point, const QFont & font, const QString & text)
void    addText(qreal x, qreal y, const QFont & font, const QString & text)

*/
int QPainterPath_addText(lua_State* const state)
{
    return 0;
}

/*

void    arcMoveTo(const QRectF & rectangle, qreal angle)
void    arcMoveTo(qreal x, qreal y, qreal width, qreal height, qreal angle)

*/
int QPainterPath_arcMoveTo(lua_State* const state)
{
    return 0;
}

/*

void    arcTo(const QRectF & rectangle, qreal startAngle, qreal sweepLength)
void    arcTo(qreal x, qreal y, qreal width, qreal height, qreal startAngle, qreal sweepLength)

*/
int QPainterPath_arcTo(lua_State* const state)
{
    return 0;
}

/*

bool    contains(const QPointF & point) const
bool    contains(const QRectF & rectangle) const
bool    contains(const QPainterPath & p) const

*/
int QPainterPath_contains(lua_State* const state)
{
    return 0;
}

/*

void    cubicTo(const QPointF & c1, const QPointF & c2, const QPointF & endPoint)
void    cubicTo(qreal c1X, qreal c1Y, qreal c2X, qreal c2Y, qreal endPointX, qreal endPointY)

*/
int QPainterPath_cubicTo(lua_State* const state)
{
    return 0;
}

/*

bool    intersects(const QRectF & rectangle) const
bool    intersects(const QPainterPath & p) const

*/
int QPainterPath_intersects(lua_State* const state)
{
    return 0;
}

/*

void    lineTo(const QPointF & endPoint)
void    lineTo(qreal x, qreal y)

*/
int QPainterPath_lineTo(lua_State* const state)
{
    return 0;
}

/*

void    moveTo(const QPointF & point)
void    moveTo(qreal x, qreal y)

*/
int QPainterPath_moveTo(lua_State* const state)
{
    return 0;
}

/*

void    quadTo(const QPointF & c, const QPointF & endPoint)
void    quadTo(qreal cx, qreal cy, qreal endPointX, qreal endPointY)

*/
int QPainterPath_quadTo(lua_State* const state)
{
    return 0;
}

/*

QPolygonF   toFillPolygon(const QTransform & matrix) const
QPolygonF   toFillPolygon(const QMatrix & matrix = QMatrix()) const
QList<QPolygonF>    toFillPolygons(const QTransform & matrix) const
QList<QPolygonF>    toFillPolygons(const QMatrix & matrix = QMatrix()) const
QPainterPath    toReversed() const
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
    return 0;
}

int QPainterPath_translated(lua_State* const state)
{
    return 0;
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
    lua::make<QPainterPath>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QPainterPath(lua_State* const state)
{
    lua::thread env(state);

    env["QPainterPath"] = lua::value::table;
    env["QPainterPath"]["new"] = QPainterPath_new;

    return 0;
}

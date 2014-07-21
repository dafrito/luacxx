#include "QRectF.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QRectF>

//bool    contains ( const QPoint & point, bool proper = false ) const
//bool    contains ( int x, int y, bool proper ) const
//bool    contains ( int x, int y ) const
//bool    contains ( const QRectF & rectangle, bool proper = false ) const
int QRectF_contains(lua_State* const state)
{
    return 0;
}

int QRectF_moveTo(lua_State* const state)
{
    return 0;
}

//void    getCoords ( int * x1, int * y1, int * x2, int * y2 ) const
int QRectF_getCoords(lua_State* const state)
{
    qreal x1, y1, x2, y2;
    lua::get<QRectF*>(state, 1)->getCoords(&x1, &y1, &x2, &y2);

    lua::push(state, x1, y1, x2, y2);
    return 4;
}

//void    getRect ( int * x, int * y, int * width, int * height ) const
int QRectF_getRect(lua_State* const state)
{
    qreal x, y, width, height;
    lua::get<QRectF*>(state, 1)->getRect(&x, &y, &width, &height);

    lua::push(state, x, y, width, height);
    return 4;
}

std::string QRectF_tostring(QRectF* const rect)
{
    std::stringstream str;
    str << "QRectF("
        << "x: " << rect->x()
        << ", y: " << rect->y()
        << ", width: " << rect->width()
        << ", height: " << rect->height()
        << ')';
    return str.str();
}

void lua::QRectF_metatable(const lua::index& mt)
{
    mt["adjust"] = &QRectF::adjust;
    mt["adjusted"] = &QRectF::adjusted;
    mt["bottom"] = &QRectF::bottom;
    mt["bottomLeft"] = &QRectF::bottomLeft;
    mt["bottomRight"] = &QRectF::bottomRight;
    mt["center"] = &QRectF::center;
    mt["contains"] = QRectF_contains;
    mt["getCoords"] = QRectF_getCoords;
    mt["getRect"] = QRectF_getRect;
    mt["height"] = &QRectF::height;
    mt["intersected"] = &QRectF::intersected;
    mt["intersects"] = &QRectF::intersects;
    mt["isEmpty"] = &QRectF::isEmpty;
    mt["isNull"] = &QRectF::isNull;
    mt["isValid"] = &QRectF::isValid;
    mt["left"] = &QRectF::left;
    mt["moveBottom"] = &QRectF::moveBottom;
    mt["moveBottomLeft"] = &QRectF::moveBottomLeft;
    mt["moveBottomRight"] = &QRectF::moveBottomRight;
    mt["moveCenter"] = &QRectF::moveCenter;
    mt["moveLeft"] = &QRectF::moveLeft;
    mt["moveRight"] = &QRectF::moveRight;
    mt["moveTo"] = QRectF_moveTo;
    mt["moveTop"] = &QRectF::moveTop;
    mt["moveTopLeft"] = &QRectF::moveTopLeft;
    mt["moveTopRight"] = &QRectF::moveTopRight;
    mt["normalized"] = &QRectF::normalized;
    mt["right"] = &QRectF::right;
    mt["setBottom"] = &QRectF::setBottom;
    mt["setBottomLeft"] = &QRectF::setBottomLeft;
    mt["setBottomRight"] = &QRectF::setBottomRight;
    mt["setCoords"] = &QRectF::setCoords;
    mt["setBottom"] = &QRectF::setBottom;
    mt["setHeight"] = &QRectF::setHeight;
    mt["setLeft"] = &QRectF::setLeft;
    mt["setRect"] = &QRectF::setRect;
    mt["setRight"] = &QRectF::setRight;
    mt["setRect"] = &QRectF::setRect;
    mt["setSize"] = &QRectF::setSize;
    mt["setTop"] = &QRectF::setTop;
    mt["setTopLeft"] = &QRectF::setTopLeft;
    mt["setTopRight"] = &QRectF::setTopRight;
    mt["setWidth"] = &QRectF::setWidth;
    mt["setX"] = &QRectF::setX;
    mt["setY"] = &QRectF::setY;
    mt["size"] = &QRectF::size;
    mt["top"] = &QRectF::top;
    mt["topLeft"] = &QRectF::topLeft;
    mt["topRight"] = &QRectF::topRight;
    //void    translate ( int dx, int dy )
    //void    translate ( const QPoint & offset )
    //mt["translated"] = &QRectF::translated;
    mt["united"] = &QRectF::united;
    mt["width"] = &QRectF::width;
    mt["x"] = &QRectF::x;
    mt["y"] = &QRectF::y;
    mt["__tostring"] = QRectF_tostring;
}

int QRectF_new(lua_State* const state)
{
    lua::make<QRectF>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Core_QRectF(lua_State* const state)
{
    lua::thread env(state);

    env["QRectF"] = lua::value::table;
    env["QRectF"]["new"] = QRectF_new;

    return 0;
}

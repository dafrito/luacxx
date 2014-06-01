#include "QRect.hpp"
#include "../type/function.hpp"
#include "../type/numeric.hpp"
#include "../thread.hpp"

#include <QRect>
#include <cstring>

//bool    contains ( const QPoint & point, bool proper = false ) const
//bool    contains ( int x, int y, bool proper ) const
//bool    contains ( int x, int y ) const
//bool    contains ( const QRect & rectangle, bool proper = false ) const
int QRect_contains(lua::state* const state)
{
    return 0;
}

int QRect_moveTo(lua::state* const state)
{
    return 0;
}

//void    getCoords ( int * x1, int * y1, int * x2, int * y2 ) const
int QRect_getCoords(lua::state* const state)
{
    int x1, y1, x2, y2;
    lua::get<QRect*>(state, 1)->getCoords(&x1, &y1, &x2, &y2);

    lua::push(state, x1, y1, x2, y2);
    return 4;
}

//void    getRect ( int * x, int * y, int * width, int * height ) const
int QRect_getRect(lua::state* const state)
{
    int x, y, width, height;
    lua::get<QRect*>(state, 1)->getRect(&x, &y, &width, &height);

    lua::push(state, x, y, width, height);
    return 4;
}

std::string QRect_tostring(QRect* const rect)
{
    std::stringstream str;
    str << "QRect("
        << "x: " << rect->x()
        << ", y: " << rect->y()
        << ", width: " << rect->width()
        << ", height: " << rect->height()
        << ')';
    return str.str();
}

void lua::QRect_metatable(const lua::index& mt)
{
    mt["adjust"] = &QRect::adjust;
    mt["adjusted"] = &QRect::adjusted;
    mt["bottom"] = &QRect::bottom;
    mt["bottomLeft"] = &QRect::bottomLeft;
    mt["bottomRight"] = &QRect::bottomRight;
    mt["center"] = &QRect::center;
    mt["contains"] = QRect_contains;
    mt["getCoords"] = QRect_getCoords;
    mt["getRect"] = QRect_getRect;
    mt["height"] = &QRect::height;
    mt["intersected"] = &QRect::intersected;
    mt["intersects"] = &QRect::intersects;
    mt["isEmpty"] = &QRect::isEmpty;
    mt["isNull"] = &QRect::isNull;
    mt["isValid"] = &QRect::isValid;
    mt["left"] = &QRect::left;
    mt["moveBottom"] = &QRect::moveBottom;
    mt["moveBottomLeft"] = &QRect::moveBottomLeft;
    mt["moveBottomRight"] = &QRect::moveBottomRight;
    mt["moveCenter"] = &QRect::moveCenter;
    mt["moveLeft"] = &QRect::moveLeft;
    mt["moveRight"] = &QRect::moveRight;
    mt["moveTo"] = QRect_moveTo;
    mt["moveTop"] = &QRect::moveTop;
    mt["moveTopLeft"] = &QRect::moveTopLeft;
    mt["moveTopRight"] = &QRect::moveTopRight;
    mt["normalized"] = &QRect::normalized;
    mt["right"] = &QRect::right;
    mt["setBottom"] = &QRect::setBottom;
    mt["setBottomLeft"] = &QRect::setBottomLeft;
    mt["setBottomRight"] = &QRect::setBottomRight;
    mt["setCoords"] = &QRect::setCoords;
    mt["setBottom"] = &QRect::setBottom;
    mt["setHeight"] = &QRect::setHeight;
    mt["setLeft"] = &QRect::setLeft;
    mt["setRect"] = &QRect::setRect;
    mt["setRight"] = &QRect::setRight;
    mt["setRect"] = &QRect::setRect;
    mt["setSize"] = &QRect::setSize;
    mt["setTop"] = &QRect::setTop;
    mt["setTopLeft"] = &QRect::setTopLeft;
    mt["setTopRight"] = &QRect::setTopRight;
    mt["setWidth"] = &QRect::setWidth;
    mt["setX"] = &QRect::setX;
    mt["setY"] = &QRect::setY;
    mt["size"] = &QRect::size;
    mt["top"] = &QRect::top;
    mt["topLeft"] = &QRect::topLeft;
    mt["topRight"] = &QRect::topRight;
    //void    translate ( int dx, int dy )
    //void    translate ( const QPoint & offset )
    //mt["translated"] = &QRect::translated;
    mt["united"] = &QRect::united;
    mt["width"] = &QRect::width;
    mt["x"] = &QRect::x;
    mt["y"] = &QRect::y;
    mt["__tostring"] = QRect_tostring;
}

int QRect_new(lua::state* const state)
{
    if (lua_gettop(state) >= 5) {
        lua::make<QRect>(state,
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5)
        );
    } else {
        lua::make<QRect>(state);
    }
    return 1;
}

int luaopen_luacxx_QRect(lua::state* const state)
{
    lua::thread env(state);

    env["QRect"] = lua::value::table;
    env["QRect"]["new"] = QRect_new;

    return 0;
}

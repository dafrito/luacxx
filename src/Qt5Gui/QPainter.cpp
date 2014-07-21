#include "QPainter.hpp"

#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../convert/vector.hpp"

#include "../thread.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "QTextOption.hpp"
#include "../Qt5Core/Qt.hpp"

#include <QPaintEngine>

/*

QVector and QString are treated as tables and strings, respectively.

*/

int QPainter_boundingRect(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);
    if (lua_type(state, 2) != LUA_TUSERDATA) {
        // QRect boundingRect(int x, int y, int w, int h, int flags, const QString & text)
        lua::push(state, self->boundingRect(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5),
            lua::get<int>(state, 6),
            lua::get<const char*>(state, 7)
        ));
        return 1;
    }

    if (lua::is_type<QRect>(state, 2)) {
        // QRect boundingRect(const QRect & rectangle, int flags, const QString & text)
        lua::push(state, self->boundingRect(
            lua::get<const QRect&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const char*>(state, 4)
        ));
        return 1;
    }
    if (lua_type(state, 3) == LUA_TNUMBER) {
        // QRectF boundingRect(const QRectF & rectangle, int flags, const QString & text)
        lua::push(state, self->boundingRect(
            lua::get<const QRectF&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const char*>(state, 4)
        ));
        return 1;
    }

    // QRectF boundingRect(const QRectF & rectangle, const QString & text, const QTextOption & option = QTextOption())
    if (lua_gettop(state) > 3) {
        lua::push(state, self->boundingRect(
            lua::get<const QRectF&>(state, 2),
            lua::get<const char*>(state, 3),
            lua::get<const QTextOption&>(state, 4)
        ));
        return 1;
    }

    lua::push(state, self->boundingRect(
        lua::get<const QRectF&>(state, 2),
        lua::get<const char*>(state, 3)
    ));
    return 1;
}

int QPainter_drawArc(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);
    if (lua_gettop(state) == 4) {
        if (lua::is_type<QRect>(state, 2)) {
            // void drawArc( const QRect & rectangle, int startAngle, int spanAngle )
            self->drawArc(
                lua::get<const QRect&>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4)
            );
        }
        // void drawArc( const QRectF & rectangle, int startAngle, int spanAngle )
        self->drawArc(
            lua::get<const QRectF&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4)
        );
        return 0;
    }

    // void drawArc( int x, int y, int width, int height, int startAngle, int spanAngle )
    self->drawArc(
        lua::get<int>(state, 2), // x
        lua::get<int>(state, 3), // y
        lua::get<int>(state, 4), // width
        lua::get<int>(state, 5), // height
        lua::get<int>(state, 6), // startAngle
        lua::get<int>(state, 7) // spanAngle
    );
    return 0;
}

int QPainter_drawChord(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);
    if (lua_gettop(state) == 4) {
        if (lua::is_type<QRect>(state, 2)) {
            // void drawChord( const QRect & rectangle, int startAngle, int spanAngle )
            self->drawChord(
                lua::get<const QRect&>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4)
            );
        }
        // void drawChord( const QRectF & rectangle, int startAngle, int spanAngle )
        self->drawChord(
            lua::get<const QRectF&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4)
        );
        return 0;
    }

    // void drawChord( int x, int y, int width, int height, int startAngle, int spanAngle )
    self->drawChord(
        lua::get<int>(state, 2), // x
        lua::get<int>(state, 3), // y
        lua::get<int>(state, 4), // width
        lua::get<int>(state, 5), // height
        lua::get<int>(state, 6), // startAngle
        lua::get<int>(state, 7) // spanAngle
    );
    return 0;
}

int QPainter_drawConvexPolygon(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) == 1 || lua_type(state, 1) == LUA_TTABLE) {
        if (lua_rawlen(state, 1) == 0) {
            return 0;
        }

        // Get the first point of the given table
        lua_rawgeti(state, 1, 1);

        if (lua::is_type<QPoint>(state, -1)) {
            // It uses QPoint.
            std::vector<QPoint> points;
            lua::store(points, state, 1);
            self->drawConvexPolygon(&points[0], points.size());
        } else {
            // It uses QPointF.
            std::vector<QPointF> points;
            lua::store(points, state, 1);
            self->drawConvexPolygon(&points[0], points.size());
        }
        return 0;
    }

    if (lua::is_type<QPolygonF>(state, 2)) {
        // void    drawConvexPolygon ( const QPolygonF & polygon )
        self->drawConvexPolygon(
            lua::get<const QPolygonF&>(state, 2)
        );
        return 0;
    }

    if (lua::is_type<QPolygon>(state, 2)) {
        // void    drawConvexPolygon ( const QPolygon & polygon )
        self->drawConvexPolygon(
            lua::get<const QPolygon&>(state, 2)
        );
        return 0;
    }

    if (lua::is_type<QPoint>(state, 2)) {
        // void    drawConvexPolygon ( const QPoint * points, int pointCount )
        self->drawConvexPolygon(
            lua::get<QPoint*>(state, 2),
            lua::get<int>(state, 3)
        );
        return 0;
    }

    // void    drawConvexPolygon ( const QPointF * points, int pointCount )
    self->drawConvexPolygon(
        lua::get<QPointF*>(state, 2),
        lua::get<int>(state, 3)
    );

    return 0;
}

int QPainter_drawEllipse(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);
    if (lua_gettop(state) == 2) {
        if (lua::is_type<QRectF>(state, 2)) {
            // void    drawEllipse ( const QRectF & rectangle )
            self->drawEllipse(lua::get<const QRectF&>(state, 2));
            return 0;
        }

        // void    drawEllipse ( const QRect & rectangle )
        self->drawEllipse(lua::get<const QRect&>(state, 2));
        return 0;
    }

    if (lua_gettop(state) >= 4) {
        // void    drawEllipse ( int x, int y, int width, int height )
        self->drawEllipse(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5)
        );
        return 0;
    }

    if (lua::is_type<QPointF>(state, 2)) {
        // void    drawEllipse ( const QPointF & center, qreal rx, qreal ry )
        self->drawEllipse(
            lua::get<const QPointF&>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        );
        return 0;
    }

    // void    drawEllipse ( const QPoint & center, int rx, int ry )
    self->drawEllipse(
        lua::get<const QPoint&>(state, 2),
        lua::get<int>(state, 3),
        lua::get<int>(state, 4)
    );
    return 0;
}

int QPainter_drawImage(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    // void    drawImage ( const QRectF & rectangle, const QImage & image )
    // void    drawImage ( const QRectF & target, const QImage & image, const QRectF & source, Qt::ImageConversionFlags flags = Qt::AutoColor )
    if (lua::is_type<QRectF>(state, 2)) {
        switch (lua_gettop(state)) {
            case 3:
            {
                self->drawImage(
                    lua::get<const QRectF&>(state, 2),
                    lua::get<const QImage&>(state, 3)
                );
                return 0;
            }
            case 4:
            {
                self->drawImage(
                    lua::get<const QRectF&>(state, 2),
                    lua::get<const QImage&>(state, 3),
                    lua::get<const QRectF&>(state, 4)
                );
                return 0;
            }
            default:
            {
                self->drawImage(
                    lua::get<const QRectF&>(state, 2),
                    lua::get<const QImage&>(state, 3),
                    lua::get<const QRectF&>(state, 4),
                    lua::get<Qt::ImageConversionFlags>(state, 5)
                );
                return 0;
            }
        }
        return 0;
    }

    // void    drawImage ( const QRect & target, const QImage & image, const QRect & source, Qt::ImageConversionFlags flags = Qt::AutoColor )
    // void    drawImage ( const QRect & rectangle, const QImage & image )
    if (lua::is_type<QRect>(state, 2)) {
        switch (lua_gettop(state)) {
            case 3:
            {
                self->drawImage(
                    lua::get<const QRect&>(state, 2),
                    lua::get<const QImage&>(state, 3)
                );
                return 0;
            }
            case 4:
            {
                self->drawImage(
                    lua::get<const QRect&>(state, 2),
                    lua::get<const QImage&>(state, 3),
                    lua::get<const QRectF&>(state, 4)
                );
                return 0;
            }
            default:
            {
                self->drawImage(
                    lua::get<const QRect&>(state, 2),
                    lua::get<const QImage&>(state, 3),
                    lua::get<const QRectF&>(state, 4),
                    lua::get<Qt::ImageConversionFlags>(state, 5)
                );
                return 0;
            }
        }
        return 0;
    }

    // void    drawImage ( const QPointF & point, const QImage & image )
    // void    drawImage ( const QPointF & point, const QImage & image, const QRectF & source, Qt::ImageConversionFlags flags = Qt::AutoColor )
    if (lua::is_type<QPointF>(state, 2)) {
        switch (lua_gettop(state)) {
            case 3:
            {
                self->drawImage(
                    lua::get<const QPointF&>(state, 2),
                    lua::get<const QImage&>(state, 3)
                );
                return 0;
            }
            case 4:
            {
                self->drawImage(
                    lua::get<const QPointF&>(state, 2),
                    lua::get<const QImage&>(state, 3),
                    lua::get<const QRectF&>(state, 4)
                );
                return 0;
            }
            default:
            {
                self->drawImage(
                    lua::get<const QPointF&>(state, 2),
                    lua::get<const QImage&>(state, 3),
                    lua::get<const QRectF&>(state, 4),
                    lua::get<Qt::ImageConversionFlags>(state, 5)
                );
                return 0;
            }
        }
        return 0;
    }

    // void    drawImage ( const QPoint & point, const QImage & image )
    // void    drawImage ( const QPoint & point, const QImage & image, const QRect & source, Qt::ImageConversionFlags flags = Qt::AutoColor )
    if (lua::is_type<QPoint>(state, 2)) {
        switch (lua_gettop(state)) {
            case 3:
            {
                self->drawImage(
                    lua::get<const QPoint&>(state, 2),
                    lua::get<const QImage&>(state, 3)
                );
                return 0;
            }
            case 4:
            {
                self->drawImage(
                    lua::get<const QPoint&>(state, 2),
                    lua::get<const QImage&>(state, 3),
                    lua::get<const QRectF&>(state, 4)
                );
                return 0;
            }
            default:
            {
                self->drawImage(
                    lua::get<const QPoint&>(state, 2),
                    lua::get<const QImage&>(state, 3),
                    lua::get<const QRectF&>(state, 4),
                    lua::get<Qt::ImageConversionFlags>(state, 5)
                );
                return 0;
            }
        }
        return 0;
    }

    // void    drawImage ( int x, int y, const QImage & image, int sx = 0, int sy = 0, int sw = -1, int sh = -1, Qt::ImageConversionFlags flags = Qt::AutoColor )
    if (lua_gettop(state) == 8) {
        self->drawImage(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QImage&>(state, 4),
            lua::get<int>(state, 5),
            lua::get<int>(state, 6),
            lua::get<int>(state, 7),
            lua::get<int>(state, 8)
        );
    }

    self->drawImage(
        lua::get<int>(state, 2),
        lua::get<int>(state, 3),
        lua::get<const QImage&>(state, 4),
        lua::get<int>(state, 5),
        lua::get<int>(state, 6),
        lua::get<int>(state, 7),
        lua::get<int>(state, 8),
        lua::get<Qt::ImageConversionFlags>(state, 9)
    );
    return 0;
}

int QPainter_drawLine(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) == 2) {
        if (lua::is_type<QLineF>(state, 2)) {
            // void drawLine(const QLineF & line)
            self->drawLine(lua::get<const QLineF&>(state, 2));
            return 0;
        }

        // void drawLine(const QLine & line)
        self->drawLine(lua::get<const QLine&>(state, 2));
        return 0;
    }
    if (lua_gettop(state) == 3) {
        if (lua::is_type<QPointF>(state, 2)) {
            // void drawLine(const QPointF & p1, const QPointF & p2)
            self->drawLine(
                lua::get<const QPointF&>(state, 2),
                lua::get<const QPointF&>(state, 3)
            );
            return 0;
        }

        // void drawLine(const QPoint & p1, const QPoint & p2)
        self->drawLine(
            lua::get<const QPoint&>(state, 2),
            lua::get<const QPoint&>(state, 3)
        );
        return 0;
    }

    // void drawLine(int x1, int y1, int x2, int y2)
    self->drawLine(
        lua::get<int>(state, 2),
        lua::get<int>(state, 3),
        lua::get<int>(state, 4),
        lua::get<int>(state, 5)
    );
    return 0;
}

int QPainter_drawLines(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) > 2) {
        if (lua::is_type<QLineF>(state, 2)) {
            // void drawLines(const QLineF * lines, int lineCount)
            self->drawLines(
                lua::get<QLineF*>(state, 2),
                lua::get<int>(state, 3)
            );
            return 0;
        }

        if (lua::is_type<QLine>(state, 2)) {
            // void drawLines(const QLine * lines, int lineCount)
            self->drawLines(
                lua::get<QLine*>(state, 2),
                lua::get<int>(state, 3)
            );
            return 0;

        }

        if (lua::is_type<QPoint>(state, 2)) {
            // void drawLines(const QPoint * pointPairs, int lineCount)
            self->drawLines(
                lua::get<QPoint*>(state, 2),
                lua::get<int>(state, 3)
            );
            return 0;
        }

        // void drawLines(const QPointF * pointPairs, int lineCount)
        self->drawLines(
            lua::get<QPointF*>(state, 2),
            lua::get<int>(state, 3)
        );
        return 0;
    }

    return 0;
}

int QPainter_drawPicture(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) > 3) {
        // void drawPicture(int x, int y, const QPicture & picture)
        self->drawPicture(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QPicture&>(state, 4)
        );
        return 0;
    }

    if (lua::is_type<QPoint>(state, 2)) {
        // void drawPicture(const QPoint & point, const QPicture & picture)
        self->drawPicture(
            lua::get<const QPoint&>(state, 2),
            lua::get<const QPicture&>(state, 3)
        );
        return 0;
    }

    // void drawPicture(const QPointF & point, const QPicture & picture)
    self->drawPicture(
        lua::get<const QPointF&>(state, 2),
        lua::get<const QPicture&>(state, 3)
    );
    return 0;
}

int QPainter_drawPie(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) > 3) {
        // void drawPie(int x, int y, int width, int height, int startAngle, int spanAngle)
        self->drawPie(
            lua::get<int>(state, 2), // x
            lua::get<int>(state, 3), // y
            lua::get<int>(state, 4), // width
            lua::get<int>(state, 5), // height
            lua::get<int>(state, 6), // startAngle
            lua::get<int>(state, 7)  // spanAngle
        );
        return 0;
    }

    if (lua::is_type<QRect>(state, 2)) {
        // void drawPie(const QRect & rectangle, int startAngle, int spanAngle)
        self->drawPie(
            lua::get<const QRect&>(state, 2),
            lua::get<int>(state, 3), // startAngle
            lua::get<int>(state, 4)  // spanAngle
        );
        return 0;
    }

    // void drawPie(const QRectF & rectangle, int startAngle, int spanAngle)
    self->drawPie(
        lua::get<const QRectF&>(state, 2),
        lua::get<int>(state, 3), // startAngle
        lua::get<int>(state, 4)  // spanAngle
    );
    return 0;
}

int QPainter_drawPixmap(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_type(state, 2) == LUA_TNUMBER) {
        switch (lua_gettop(state)) {
        case 6: {
            // void drawPixmap(int x, int y, int width, int height, const QPixmap & pixmap)
            self->drawPixmap(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4),
                lua::get<int>(state, 5),
                lua::get<const QPixmap&>(state, 6)
            );
            return 0;
        }
        case 10:
        {
            // void drawPixmap(int x, int y, int w, int h, const QPixmap & pixmap, int sx, int sy, int sw, int sh)
            self->drawPixmap(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4),
                lua::get<int>(state, 5),
                lua::get<const QPixmap&>(state, 6),
                lua::get<int>(state, 7),
                lua::get<int>(state, 8),
                lua::get<int>(state, 9),
                lua::get<int>(state, 10)
            );
        }
        case 8:
        {
            // void drawPixmap(int x, int y, const QPixmap & pixmap, int sx, int sy, int sw, int sh)
            self->drawPixmap(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<const QPixmap&>(state, 4),
                lua::get<int>(state, 5),
                lua::get<int>(state, 6),
                lua::get<int>(state, 7),
                lua::get<int>(state, 8)
            );
        }
        default:
        {
            // void drawPixmap(int x, int y, const QPixmap & pixmap)
            self->drawPixmap(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<const QPixmap&>(state, 4)
            );
        }
        }
    }

    auto pixmap = lua::get<const QPixmap&>(state, 3);

    if (lua::is_type<QPointF>(state, 2)) {
        if (lua_gettop(state) > 3) {
            // void drawPixmap(const QPointF & point, const QPixmap & pixmap, const QRectF & source)
            self->drawPixmap(
                lua::get<const QPoint&>(state, 2),
                pixmap,
                lua::get<const QRectF&>(state, 4)
            );
            return 0;
        }

        // void drawPixmap(const QPointF & point, const QPixmap & pixmap)
        self->drawPixmap(
            lua::get<const QPoint&>(state, 2),
            pixmap
        );
        return 0;
    }

    if (lua::is_type<QPoint>(state, 2)) {
        if (lua_gettop(state) > 3) {
            // void drawPixmap(const QPoint & point, const QPixmap & pixmap, const QRect & source)
            self->drawPixmap(
                lua::get<const QPoint&>(state, 2),
                pixmap,
                lua::get<const QRect&>(state, 4)
            );
            return 0;
        }

        // void drawPixmap(const QPoint & point, const QPixmap & pixmap)
        self->drawPixmap(
            lua::get<const QPoint&>(state, 2),
            pixmap
        );
        return 0;
    }

    if (lua::is_type<QRect>(state, 2)) {
        if (lua_gettop(state) > 3) {
            // void drawPixmap(const QRect & point, const QPixmap & pixmap, const QRectF & source)
            self->drawPixmap(
                lua::get<const QRect&>(state, 2),
                pixmap,
                lua::get<const QRect&>(state, 4)
            );
            return 0;
        }

        // void drawPixmap(const QRect & point, const QPixmap & pixmap)
        self->drawPixmap(
            lua::get<const QRect&>(state, 2),
            pixmap
        );
        return 0;
    }

    if (lua::is_type<QRectF>(state, 2)) {
        // void drawPixmap(const QRectF & target, const QPixmap & pixmap, const QRectF & source)
        self->drawPixmap(
            lua::get<const QRectF&>(state, 2),
            pixmap,
            lua::get<const QRectF&>(state, 4)
        );
        return 0;
    }

    return 0;
}

int QPainter_drawPixmapFragments(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) >= 5) {
        // void drawPixmapFragments(const PixmapFragment * fragments, int fragmentCount, const QPixmap & pixmap, PixmapFragmentHints hints)
        self->drawPixmapFragments(
            lua::get<QPainter::PixmapFragment*>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QPixmap&>(state, 4),
            lua::get<QPainter::PixmapFragmentHints>(state, 5)
        );
        return 0;
    }

    // void drawPixmapFragments(const PixmapFragment * fragments, int fragmentCount, const QPixmap & pixmap)
    self->drawPixmapFragments(
        lua::get<QPainter::PixmapFragment*>(state, 2),
        lua::get<int>(state, 3),
        lua::get<const QPixmap&>(state, 4)
    );
    return 0;
}

int QPainter_drawPoint(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) > 2) {
        // void drawPoint(int x, int y)
        self->drawPoint(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        );
        return 0;
    }

    if (lua::is_type<QPoint>(state, 2)) {
        // void drawPoint(const QPoint & position)
        self->drawPoint(
            lua::get<const QPoint&>(state, 2)
        );
        return 0;
    }

    // void drawPoint(const QPointF & position)
    self->drawPoint(
        lua::get<const QPointF&>(state, 2)
    );
    return 0;
}

int QPainter_drawPoints(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);
    if (lua_gettop(state) > 2) {
        if (lua::is_type<QPointF>(state, 2)) {
            // void drawPoints(const QPointF * points, int pointCount)
            self->drawPoints(
                lua::get<const QPointF*>(state, 2),
                lua::get<int>(state, 3)
            );
        }
        // void drawPoints(const QPoint * points, int pointCount)
        self->drawPoints(
            lua::get<const QPoint*>(state, 2),
            lua::get<int>(state, 3)
        );
    }

    if (lua_type(state, 2) == LUA_TTABLE) {
        lua_rawgeti(state, 2, 1);
        if (lua::is_type<QPointF>(state, -1)) {
            std::vector<QPointF> points;
            lua::store(points, state, 2);
            self->drawPoints(
                &points[0],
                points.size()
            );
        } else {
            std::vector<QPoint> points;
            lua::store(points, state, 2);
            self->drawPoints(
                &points[0],
                points.size()
            );
        }
        return 0;
    }

    if (lua::is_type<QPolygon>(state, 2)) {
        self->drawPoints(lua::get<const QPolygon&>(state, 2));
        return 0;
    }

    self->drawPoints(lua::get<const QPolygonF&>(state, 2));
    return 0;
}

int QPainter_drawPolygon(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_type(state, 2) == LUA_TTABLE) {
        lua_rawgeti(state, 2, 1);
        if (lua::is_type<QPointF>(state, -1)) {
            // void drawPolygon(const QPointF* points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill)
            std::vector<QPointF> points;
            lua::store(points, state, 2);
            if (lua_gettop(state) == 3) {
                self->drawPolygon(
                    &points[0],
                    points.size(),
                    lua::get<Qt::FillRule>(state, 3)
                );
            } else {
                self->drawPolygon(
                    &points[0],
                    points.size()
                );
            }
            return 0;
        }

        // void drawPolygon(const QPoint* points, int pointCount, Qt::FillRule fillRule = Qt::OddEvenFill)
        std::vector<QPoint> points;
        lua::store(points, state, 2);
        if (lua_gettop(state) == 3) {
            self->drawPolygon(
                &points[0],
                points.size(),
                lua::get<Qt::FillRule>(state, 3)
            );
        } else {
            self->drawPolygon(
                &points[0],
                points.size()
            );
        }
        return 0;
    }

    if (lua::is_type<QPolygonF>(state, 2)) {
        // void drawPolygon(const QPolygonF & points, Qt::FillRule fillRule = Qt::OddEvenFill)
        if (lua_gettop(state) == 3) {
            self->drawPolygon(
                lua::get<const QPolygonF&>(state, 2),
                lua::get<Qt::FillRule>(state, 3)
            );
        } else {
            self->drawPolygon(lua::get<const QPolygonF&>(state, 2));
        }

        return 0;
    }

    // void drawPolygon(const QPolygon & points, Qt::FillRule fillRule = Qt::OddEvenFill)
    if (lua_gettop(state) == 3) {
        self->drawPolygon(
            lua::get<const QPolygon&>(state, 2),
            lua::get<Qt::FillRule>(state, 3)
        );
    } else {
        self->drawPolygon(lua::get<const QPolygon&>(state, 2));
    }
    return 0;
}

int QPainter_drawPolyline(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_type(state, 2) == LUA_TTABLE) {
        lua_rawgeti(state, 2, 1);
        if (lua::is_type<QPointF>(state, -1)) {
            // void drawPolyline(const QPointF* points, int pointCount)
            std::vector<QPointF> points;
            lua::store(points, state, 2);
            self->drawPolyline(
                &points[0],
                points.size()
            );
            return 0;
        }

        // void drawPolyline(const QPoint* points, int pointCount)
        std::vector<QPoint> points;
        lua::store(points, state, 2);
        self->drawPolyline(
            &points[0],
            points.size()
        );
        return 0;
    }

    if (lua::is_type<QPolygonF>(state, 2)) {
        // void drawPolyline(const QPolygonF & points)
        self->drawPolyline(lua::get<const QPolygonF&>(state, 2));
        return 0;
    }

    if (lua_gettop(state) == 3) {
        // void drawPolyline(const QPolygon & points)
        self->drawPolyline(lua::get<const QPolygon&>(state, 2));
    }
    return 0;
}

int QPainter_drawRect(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) > 2) {
        // void drawRect(int x, int y, int width, int height)
        self->drawRect(
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5),
            lua::get<int>(state, 6)
        );
        return 0;
    }

    if (lua::is_type<QRectF>(state, 2)) {
        // void drawRect(const QRectF & rectangle)
        self->drawRect(
            lua::get<const QRectF&>(state, 2)
        );
        return 0;
    }

    // void drawRect(const QRect & rectangle)
    self->drawRect(
        lua::get<const QRect&>(state, 2)
    );
    return 0;
}

int QPainter_drawRects(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) > 2) {
        if (lua::is_type<QRectF>(state, 2)) {
            self->drawRects(
                lua::get<const QRectF*>(state, 2),
                lua::get<int>(state, 3)
            );
        } else {
            self->drawRects(
                lua::get<const QRect*>(state, 2),
                lua::get<int>(state, 3)
            );
        }
    }

    if (lua_type(state, 2) == LUA_TTABLE) {
        if (lua_rawlen(state, 2) == 0) {
            return 0;
        }
        lua_rawgeti(state, 2, 1);
        if (lua::is_type<QRectF>(state, -1)) {
            std::vector<QRectF> rectangles;
            lua::store(rectangles, state, 2);
            self->drawRects(&rectangles[0], rectangles.size());
        } else {
            std::vector<QRect> rectangles;
            lua::store(rectangles, state, 2);
            self->drawRects(&rectangles[0], rectangles.size());
        }
        return 0;
    }

    return 0;
}

int QPainter_drawRoundedRect(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_type(state, 2) == LUA_TNUMBER) {
        // void drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize)
        if (lua_gettop(state) > 7) {
            self->drawRoundedRect(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4),
                lua::get<int>(state, 5),
                lua::get<qreal>(state, 6),
                lua::get<qreal>(state, 7),
                lua::get<Qt::SizeMode>(state, 8)
            );
        }
        self->drawRoundedRect(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5),
            lua::get<qreal>(state, 6),
            lua::get<qreal>(state, 7)
        );
        return 0;
    }

    if (lua::is_type<QRect>(state, 2)) {
        // void drawRoundedRect(const QRect & rect, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize)
        if (lua_gettop(state) > 4) {
            self->drawRoundedRect(
                lua::get<const QRect&>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<Qt::SizeMode>(state, 5)
            );
        }
        self->drawRoundedRect(
            lua::get<const QRect&>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        );
        return 0;
    }

    if (lua::is_type<QRectF>(state, 2)) {
        // void drawRoundedRect(const QRectF & rect, qreal xRadius, qreal yRadius, Qt::SizeMode mode = Qt::AbsoluteSize)
        if (lua_gettop(state) > 4) {
            self->drawRoundedRect(
                lua::get<const QRectF&>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<Qt::SizeMode>(state, 5)
            );
        }
        self->drawRoundedRect(
            lua::get<const QRectF&>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        );
        return 0;
    }

    return 0;
}

int QPainter_drawStaticText(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) > 3) {
        // void drawStaticText(int left, int top, const QStaticText & staticText)
        self->drawStaticText(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const QStaticText&>(state, 4)
        );
        return 0;
    }

    if (lua::is_type<QPointF>(state, 2)) {
        // void drawStaticText(const QPointF & topLeftPosition, const QStaticText & staticText)
        self->drawStaticText(
            lua::get<const QPointF&>(state, 2),
            lua::get<const QStaticText&>(state, 3)
        );
        return 0;
    }

    // void drawStaticText(const QPoint & topLeftPosition, const QStaticText & staticText)
    self->drawStaticText(
        lua::get<const QPoint&>(state, 2),
        lua::get<const QStaticText&>(state, 3)
    );
    return 0;
}

int QPainter_drawText(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_type(state, 2) == LUA_TNUMBER) {
        // void drawText(int x, int y, int width, int height, int flags, const QString & text, QRect * boundingRect = 0)
        if (lua_gettop(state) > 4) {
            if (lua_gettop(state) == 8) {
                self->drawText(
                    lua::get<int>(state, 2),
                    lua::get<int>(state, 3),
                    lua::get<int>(state, 4),
                    lua::get<int>(state, 5),
                    lua::get<int>(state, 6),
                    lua::get<const char*>(state, 7),
                    lua::get<QRect*>(state, 8)
                );
            }

            self->drawText(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4),
                lua::get<int>(state, 5),
                lua::get<int>(state, 6),
                lua::get<const char*>(state, 7)
            );
            return 0;
        }

        // void drawText(int x, int y, const QString & text)
        self->drawText(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const char*>(state, 4)
        );
        return 0;
    }

    if (lua::is_type<QPointF>(state, 2)) {
        // void drawText(const QPointF & position, const QString & text)
        self->drawText(
            lua::get<const QPointF&>(state, 2),
            lua::get<const char*>(state, 3)
        );
        return 0;
    }

    if (lua::is_type<QPoint>(state, 2)) {
        // void drawText(const QPoint & position, const QString & text)
        self->drawText(
            lua::get<const QPoint&>(state, 2),
            lua::get<const char*>(state, 3)
        );
        return 0;
    }

    if (lua::is_type<QRect>(state, 2)) {
        // void drawText(const QRect & rectangle, int flags, const QString & text, QRect * boundingRect = 0)
        if (lua_gettop(state) == 5) {
            self->drawText(
                lua::get<const QRect&>(state, 2),
                lua::get<int>(state, 3),
                lua::get<const char*>(state, 4),
                lua::get<QRect*>(state, 5)
            );
            return 0;
        }
        self->drawText(
            lua::get<const QRect&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const char*>(state, 4)
        );
        return 0;
    }

    if (lua_type(state, 3) == LUA_TNUMBER) {
        // void drawText(const QRectF & rectangle, int flags, const QString & text, QRectF * boundingRect = 0)
        if (lua_gettop(state) == 5) {
            self->drawText(
                lua::get<const QRectF&>(state, 2),
                lua::get<int>(state, 3),
                lua::get<const char*>(state, 4),
                lua::get<QRectF*>(state, 5)
            );
            return 0;
        }
        self->drawText(
            lua::get<const QRectF&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<const char*>(state, 4)
        );
    }

    // void drawText(const QRectF & rectangle, const QString & text, const QTextOption & option = QTextOption())
    if (lua_gettop(state) == 4) {
        self->drawText(
            lua::get<const QRectF&>(state, 2),
            lua::get<const char*>(state, 3),
            lua::get<const QTextOption&>(state, 4)
        );
        return 0;
    }
    self->drawText(
        lua::get<const QRectF&>(state, 2),
        lua::get<const char*>(state, 3)
    );
    return 0;
}

int QPainter_drawTiledPixmap(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) > 5) {
        // void drawTiledPixmap(int x, int y, int width, int height, const QPixmap & pixmap, int sx = 0, int sy = 0)
        switch (lua_gettop(state)) {
        case 6:
            self->drawTiledPixmap(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4),
                lua::get<int>(state, 5),
                lua::get<const QPixmap&>(state, 6)
            );
            return 0;
        case 7:
            self->drawTiledPixmap(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4),
                lua::get<int>(state, 5),
                lua::get<const QPixmap&>(state, 6),
                lua::get<int>(state, 7) // sx
            );
            return 0;
        default:
            self->drawTiledPixmap(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4),
                lua::get<int>(state, 5),
                lua::get<const QPixmap&>(state, 6),
                lua::get<int>(state, 7), // sx
                lua::get<int>(state, 8) // sy
            );
            return 0;
        }
    }

    if (lua::is_type<QRect>(state, 2)) {
        if (lua_gettop(state) >= 4) {
            // void drawTiledPixmap(const QRect & rectangle, const QPixmap & pixmap, const QPoint & position)
            self->drawTiledPixmap(
                lua::get<const QRect&>(state, 2),
                lua::get<const QPixmap&>(state, 3),
                lua::get<const QPoint&>(state, 4)
            );
            return 0;
        }
        // void drawTiledPixmap(const QRect & rectangle, const QPixmap & pixmap)
        self->drawTiledPixmap(
            lua::get<const QRect&>(state, 2),
            lua::get<const QPixmap&>(state, 3)
        );
        return 0;
    }

    if (lua_gettop(state) >= 4) {
        // void drawTiledPixmap(const QRectF & rectangle, const QPixmap & pixmap, const QPointF & position)
        self->drawTiledPixmap(
            lua::get<const QRectF&>(state, 2),
            lua::get<const QPixmap&>(state, 3),
            lua::get<const QPointF&>(state, 4)
        );
        return 0;
    }
    // void drawTiledPixmap(const QRectF & rectangle, const QPixmap & pixmap)
    self->drawTiledPixmap(
        lua::get<const QRectF&>(state, 2),
        lua::get<const QPixmap&>(state, 3)
    );
    return 0;
}

int QPainter_eraseRect(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua::is_type<QRect>(state, 2)) {
        // void    eraseRect ( const QRect & rectangle )
        self->eraseRect(
            lua::get<const QRect&>(state, 2)
        );
        return 0;
    }

    if (lua::is_type<QRectF>(state, 3)) {
        // void    eraseRect ( const QRectF & rectangle )
        self->eraseRect(
            lua::get<const QRectF&>(state, 2)
        );
        return 0;
    }

    // void    eraseRect ( int x, int y, int width, int height )
    self->eraseRect(
        lua::get<int>(state, 2),
        lua::get<int>(state, 3),
        lua::get<int>(state, 4),
        lua::get<int>(state, 5)
    );
    return 0;
}

int QPainter_fillRect(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua::is_type<QRect>(state, 2)) {
        if (lua::is_type<QColor>(state, 3)) {
            // void    fillRect ( const QRect & rectangle, const QColor & color )
            self->fillRect(
                lua::get<const QRect&>(state, 2),
                lua::get<const QColor&>(state, 3)
            );
            return 0;
        }

        if (lua::is_type<QBrush>(state, 3)) {
            // void    fillRect ( const QRect & rectangle, const QBrush & brush )
            self->fillRect(
                lua::get<const QRect&>(state, 2),
                lua::get<const QBrush&>(state, 3)
            );
            return 0;
        }

        if (lua::is_type<Qt::GlobalColor>(state, 3)) {
            // void    fillRect ( const QRectF & rectangle, Qt::GlobalColor color )
            self->fillRect(
                lua::get<const QRectF&>(state, 2),
                lua::get<Qt::GlobalColor>(state, 3)
            );
            return 0;
        }

        // void    fillRect ( const QRect & rectangle, Qt::BrushStyle style )
        self->fillRect(
            lua::get<const QRect&>(state, 2),
            lua::get<Qt::BrushStyle>(state, 3)
        );
        return 0;
    }

    if (lua::is_type<QRectF>(state, 2)) {
        if (lua::is_type<QColor>(state, 3)) {
            // void    fillRect ( const QRectF & rectangle, const QColor & color )
            self->fillRect(
                lua::get<const QRectF&>(state, 2),
                lua::get<const QColor&>(state, 3)
            );
            return 0;
        }
        if (lua::is_type<Qt::GlobalColor>(state, 3)) {
            // void    fillRect ( const QRectF & rectangle, Qt::GlobalColor color )
            self->fillRect(
                lua::get<const QRectF&>(state, 2),
                lua::get<Qt::GlobalColor>(state, 3)
            );
            return 0;
        }

        // void    fillRect ( const QRectF & rectangle, Qt::BrushStyle style )
        self->fillRect(
            lua::get<const QRectF&>(state, 2),
            lua::get<Qt::BrushStyle>(state, 3)
        );
        return 0;
    }

    if (lua::is_type<QBrush>(state, 6)) {
        // void    fillRect ( int x, int y, int width, int height, const QBrush & brush )
        self->fillRect(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5),
            lua::get<const QBrush&>(state, 6)
        );
        return 0;
    }

    if (lua::is_type<QColor>(state, 6)) {
        // void    fillRect ( int x, int y, int width, int height, const QColor & color )
        self->fillRect(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5),
            lua::get<const QColor&>(state, 6)
        );
        return 0;
    }

    if (lua::is_type<Qt::GlobalColor>(state, 6)) {
        // void    fillRect ( int x, int y, int width, int height, Qt::BrushStyle style )
        self->fillRect(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5),
            lua::get<Qt::BrushStyle>(state, 6)
        );
        return 0;
    }

    self->fillRect(
        lua::get<int>(state, 2),
        lua::get<int>(state, 3),
        lua::get<int>(state, 4),
        lua::get<int>(state, 5),
        lua::get<Qt::GlobalColor>(state, 6)
    );
    return 0;
}

int QPainter_setBrush(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);
    if (lua::is_type<QBrush>(state, 2)) {
        // void setBrush(const QBrush & brush)
        self->setBrush(lua::get<const QBrush&>(state, 2));
        return 0;
    }
    self->setBrush(lua::get<Qt::BrushStyle>(state, 2));
    return 0;
}

int QPainter_setBrushOrigin(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);
    if (lua_gettop(state) == 2) {
        if (lua::is_type<QPointF>(state, 2)) {
            // void setBrushOrigin(const QPointF & position)
            self->setBrushOrigin(lua::get<const QPointF&>(state, 2));
            return 0;
        }
        // void setBrushOrigin(const QPoint & position)
        self->setBrushOrigin(lua::get<const QPoint&>(state, 2));
        return 0;
    }
    // void setBrushOrigin(int x, int y)
    self->setBrushOrigin(
        lua::get<int>(state, 2),
        lua::get<int>(state, 3)
    );
    return 0;
}

int QPainter_setClipPath(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);
    if (lua_gettop(state) == 2) {
        // void setClipPath(const QPainterPath & path)
        self->setClipPath(
            lua::get<const QPainterPath&>(state, 2)
        );
        return 0;
    }

    // void setClipPath(const QPainterPath & path, Qt::ClipOperation operation)
    self->setClipPath(
        lua::get<const QPainterPath&>(state, 2),
        lua::get<Qt::ClipOperation>(state, 3)
    );
    return 0;
}

int QPainter_setClipRect(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) == 5) {
        // void setClipRect(int x, int y, int width, int height)
        self->setClipRect(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5)
        );
        return 0;
    }
    if (lua_gettop(state) == 6) {
        // void setClipRect(int x, int y, int width, int height, Qt::ClipOperation operation)
        self->setClipRect(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5),
            lua::get<Qt::ClipOperation>(state, 6)
        );
        return 0;
    }

    if (lua::is_type<QRectF>(state, 2)) {
        if (lua_gettop(state) > 2) {
            // void setClipRect(const QRectF & rectangle, Qt::ClipOperation operation)
            self->setClipRect(
                lua::get<const QRectF&>(state, 2),
                lua::get<Qt::ClipOperation>(state, 3)
            );
            return 0;
        }
        // void setClipRect(const QRectF & rectangle)
        self->setClipRect(
            lua::get<const QRectF&>(state, 2)
        );
        return 0;
    }

    if (lua::is_type<QRect>(state, 2)) {
        if (lua_gettop(state) > 2) {
            // void setClipRect(const QRect & rectangle, Qt::ClipOperation operation)
            self->setClipRect(
                lua::get<const QRect&>(state, 2),
                lua::get<Qt::ClipOperation>(state, 3)
            );
            return 0;
        }
        // void setClipRect(const QRect & rectangle)
        self->setClipRect(
            lua::get<const QRect&>(state, 2)
        );
        return 0;
    }

    return 0;
}

int QPainter_setClipRegion(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);
    if (lua_gettop(state) == 2) {
        // void setClipRegion(const QRegion & region)
        self->setClipRegion(
            lua::get<const QRegion&>(state, 2)
        );
        return 0;
    }

    // void setClipRegion(const QRegion & region, Qt::ClipOperation operation)
    self->setClipRegion(
        lua::get<const QRegion&>(state, 2),
        lua::get<Qt::ClipOperation>(state, 3)
    );
    return 0;
}

int QPainter_setPen(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua::is_type<QPen>(state, 2)) {
        // void setPen(const QPen & pen)
        self->setPen(lua::get<const QPen&>(state, 2));
        return 0;
    }
    if (lua::is_type<QColor>(state, 2)) {
        // void setPen(const QColor & color)
        self->setPen(lua::get<const QColor&>(state, 2));
        return 0;
    }
    // void setPen(Qt::PenStyle style)
    self->setPen(lua::get<Qt::PenStyle>(state, 2));
    return 0;
}

int QPainter_setViewport(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) == 2) {
        // void setViewport(const QRect & rectangle)
        self->setViewport(lua::get<const QRect&>(state, 2));
        return 0;
    }

    // void setViewport(int x, int y, int width, int height)
    self->setViewport(
        lua::get<int>(state, 2),
        lua::get<int>(state, 3),
        lua::get<int>(state, 4),
        lua::get<int>(state, 5)
    );
    return 0;
}

int QPainter_setWindow(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) == 2) {
        // void setWindow(const QRect & rectangle)
        self->setWindow(lua::get<const QRect&>(state, 2));
        return 0;
    }

    // void setWindow(int x, int y, int width, int height)
    self->setWindow(
        lua::get<int>(state, 2),
        lua::get<int>(state, 3),
        lua::get<int>(state, 4),
        lua::get<int>(state, 5)
    );
    return 0;
}

int QPainter_translate(lua_State* const state)
{
    auto self = lua::get<QPainter*>(state, 1);

    if (lua_gettop(state) > 2) {
        // void translate(qreal dx, qreal dy)
        self->translate(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        );
        return 0;
    }

    if (lua::is_type<QPointF>(state, 2)) {
        // void translate(const QPointF & offset)
        self->translate(lua::get<const QPointF&>(state, 2));
        return 0;
    }

    if (lua::is_type<QPoint>(state, 2)) {
        // void translate(const QPoint& offset)
        self->translate(lua::get<const QPoint&>(state, 2));
        return 0;
    }

    return 0;
}

void lua::QPainter_metatable(const lua::index& mt)
{
    mt["background"] = &QPainter::background;
    mt["backgroundMode"] = &QPainter::backgroundMode;
    mt["begin"] = &QPainter::begin;
    mt["beginNativePainting"] = &QPainter::beginNativePainting;
    mt["boundingRect"] = QPainter_boundingRect;
    mt["brush"] = &QPainter::brush;
    mt["brushOrigin"] = &QPainter::brushOrigin;
    mt["clipBoundingRect"] = &QPainter::clipBoundingRect;
    mt["clipPath"] = &QPainter::clipPath;
    mt["clipRegion"] = &QPainter::clipRegion;
    mt["combinedTransform"] = &QPainter::combinedTransform;
    mt["compositionMode"] = &QPainter::compositionMode;
    mt["device"] = &QPainter::device;
    mt["deviceTransform"] = &QPainter::deviceTransform;
    mt["drawArc"] = QPainter_drawArc;
    mt["drawChord"] = QPainter_drawChord;
    mt["drawConvexPolygon"] = QPainter_drawConvexPolygon;
    mt["drawEllipse"] = QPainter_drawEllipse;
    mt["drawGlyphRun"] = &QPainter::drawGlyphRun;
    mt["drawImage"] = QPainter_drawImage;
    mt["drawLine"] = QPainter_drawLine;
    mt["drawLines"] = QPainter_drawLines;
    mt["drawPath"] = &QPainter::drawPath;
    mt["drawPicture"] = QPainter_drawPicture;
    mt["drawPie"] = QPainter_drawPie;
    mt["drawPixmap"] = QPainter_drawPixmap;
    mt["drawPixmapFragments"] = &QPainter::drawPixmapFragments;
    mt["drawPoint"] = QPainter_drawPoint;
    mt["drawPoints"] = QPainter_drawPoints;
    mt["drawPolygon"] = QPainter_drawPolygon;
    mt["drawPolyline"] = QPainter_drawPolyline;
    mt["drawRect"] = QPainter_drawRect;
    mt["drawRects"] = QPainter_drawRects;
    mt["drawRoundedRect"] = QPainter_drawRoundedRect;
    mt["drawStaticText"] = QPainter_drawStaticText;
    mt["drawText"] = QPainter_drawText;
    mt["drawTiledPixmap"] = QPainter_drawTiledPixmap;
    mt["end"] = &QPainter::end;
    mt["endPainting"] = &QPainter::end;
    mt["endNativePainting"] = &QPainter::endNativePainting;
    mt["eraseRect"] = QPainter_eraseRect;
    mt["fillPath"] = &QPainter::fillPath;
    mt["fillRect"] = QPainter_fillRect;
    mt["font"] = &QPainter::font;
    mt["fontInfo"] = &QPainter::fontInfo;
    mt["fontMetrics"] = &QPainter::fontMetrics;
    mt["hasClipping"] = &QPainter::hasClipping;
    mt["initFrom"] = &QPainter::initFrom;
    mt["isActive"] = &QPainter::isActive;
    mt["layoutDirection"] = &QPainter::layoutDirection;
    mt["opacity"] = &QPainter::opacity;
    mt["paintEngine"] = &QPainter::paintEngine;
    mt["pen"] = &QPainter::pen;
    mt["renderHints"] = &QPainter::renderHints;
    mt["resetTransform"] = &QPainter::resetTransform;
    mt["restore"] = &QPainter::restore;
    mt["rotate"] = &QPainter::rotate;
    mt["save"] = &QPainter::save;
    mt["scale"] = &QPainter::scale;
    mt["setBackground"] = &QPainter::setBackground;
    mt["setBackgroundMode"] = &QPainter::setBackgroundMode;
    mt["setBrush"] = QPainter_setBrush;
    mt["setBrushOrigin"] = QPainter_setBrushOrigin;
    mt["setClipPath"] = QPainter_setClipPath;
    mt["setClipRect"] = QPainter_setClipRect;
    mt["setClipRegion"] = QPainter_setClipRegion;
    mt["setClipping"] = &QPainter::setClipping;
    mt["setCompositionMode"] = &QPainter::setCompositionMode;
    mt["setFont"] = &QPainter::setFont;
    mt["setLayoutDirection"] = &QPainter::setLayoutDirection;
    mt["setOpacity"] = &QPainter::setOpacity;
    mt["setPen"] = QPainter_setPen;
    mt["setRenderHint"] = &QPainter::setRenderHint;
    mt["setRenderHints"] = &QPainter::setRenderHints;
    mt["setTransform"] = &QPainter::setTransform;
    mt["setViewTransformEnabled"] = &QPainter::setViewTransformEnabled;
    mt["setViewport"] = QPainter_setViewport;
    mt["setWindow"] = QPainter_setWindow;
    mt["setWorldMatrixEnabled"] = &QPainter::setWorldMatrixEnabled;
    mt["setWorldTransform"] = &QPainter::setWorldTransform;
    mt["shear"] = &QPainter::shear;
    mt["strokePath"] = &QPainter::strokePath;
    mt["testRenderHint"] = &QPainter::testRenderHint;
    mt["transform"] = &QPainter::transform;
    mt["translate"] = QPainter_translate;
    mt["viewTransformEnabled"] = &QPainter::viewTransformEnabled;
    mt["viewport"] = &QPainter::viewport;
    mt["window"] = &QPainter::window;
    mt["worldMatrixEnabled"] = &QPainter::worldMatrixEnabled;
    mt["worldTransform"] = &QPainter::worldTransform;
}

int QPainter_new(lua_State* const state)
{
    if (lua_gettop(state) > 1) {
        // QPainter ( QPaintDevice * device )
        lua::make<QPainter>(state, lua::get<QPaintDevice*>(state, 2));
    } else {
        // QPainter ()
        lua::make<QPainter>(state);
    }
    return 1;
}

int luaopen_Qt5Gui_QPainter(lua_State* const state)
{
    lua::thread env(state);

    env["QPainter"] = lua::value::table;
    env["QPainter"]["new"] = QPainter_new;

    // enum QPainter::CompositionMode
    env["QPainter"]["CompositionMode_SourceOver"] = QPainter::CompositionMode_SourceOver;
    env["QPainter"]["CompositionMode_DestinationOver"] = QPainter::CompositionMode_DestinationOver;
    env["QPainter"]["CompositionMode_Clear"] = QPainter::CompositionMode_Clear;
    env["QPainter"]["CompositionMode_Source"] = QPainter::CompositionMode_Source;
    env["QPainter"]["CompositionMode_Destination"] = QPainter::CompositionMode_Destination;
    env["QPainter"]["CompositionMode_SourceIn"] = QPainter::CompositionMode_SourceIn;
    env["QPainter"]["CompositionMode_DestinationIn"] = QPainter::CompositionMode_DestinationIn;
    env["QPainter"]["CompositionMode_SourceOut"] = QPainter::CompositionMode_SourceOut;
    env["QPainter"]["CompositionMode_DestinationOut"] = QPainter::CompositionMode_DestinationOut;
    env["QPainter"]["CompositionMode_SourceAtop"] = QPainter::CompositionMode_SourceAtop;
    env["QPainter"]["CompositionMode_DestinationAtop"] = QPainter::CompositionMode_DestinationAtop;
    env["QPainter"]["CompositionMode_Xor"] = QPainter::CompositionMode_Xor;
    env["QPainter"]["CompositionMode_Plus"] = QPainter::CompositionMode_Plus;
    env["QPainter"]["CompositionMode_Multiply"] = QPainter::CompositionMode_Multiply;
    env["QPainter"]["CompositionMode_Screen"] = QPainter::CompositionMode_Screen;
    env["QPainter"]["CompositionMode_Overlay"] = QPainter::CompositionMode_Overlay;
    env["QPainter"]["CompositionMode_Darken"] = QPainter::CompositionMode_Darken;
    env["QPainter"]["CompositionMode_Lighten"] = QPainter::CompositionMode_Lighten;
    env["QPainter"]["CompositionMode_ColorDodge"] = QPainter::CompositionMode_ColorDodge;
    env["QPainter"]["CompositionMode_ColorBurn"] = QPainter::CompositionMode_ColorBurn;
    env["QPainter"]["CompositionMode_HardLight"] = QPainter::CompositionMode_HardLight;
    env["QPainter"]["CompositionMode_SoftLight"] = QPainter::CompositionMode_SoftLight;
    env["QPainter"]["CompositionMode_Difference"] = QPainter::CompositionMode_Difference;
    env["QPainter"]["CompositionMode_Exclusion"] = QPainter::CompositionMode_Exclusion;
    env["QPainter"]["RasterOp_SourceOrDestination"] = QPainter::RasterOp_SourceOrDestination;
    env["QPainter"]["RasterOp_SourceAndDestination"] = QPainter::RasterOp_SourceAndDestination;
    env["QPainter"]["RasterOp_SourceXorDestination"] = QPainter::RasterOp_SourceXorDestination;
    env["QPainter"]["RasterOp_NotSourceAndNotDestination"] = QPainter::RasterOp_NotSourceAndNotDestination;
    env["QPainter"]["RasterOp_NotSourceOrNotDestination"] = QPainter::RasterOp_NotSourceOrNotDestination;
    env["QPainter"]["RasterOp_NotSourceXorDestination"] = QPainter::RasterOp_NotSourceXorDestination;
    env["QPainter"]["RasterOp_NotSource"] = QPainter::RasterOp_NotSource;
    env["QPainter"]["RasterOp_NotSourceAndDestination"] = QPainter::RasterOp_NotSourceAndDestination;
    env["QPainter"]["RasterOp_SourceAndNotDestination"] = QPainter::RasterOp_SourceAndNotDestination;
    env["QPainter"]["RasterOp_NotSourceOrDestination"] = QPainter::RasterOp_NotSourceOrDestination;
    env["QPainter"]["RasterOp_ClearDestination"] = QPainter::RasterOp_ClearDestination;
    env["QPainter"]["RasterOp_SetDestination"] = QPainter::RasterOp_SetDestination;
    env["QPainter"]["RasterOp_NotDestination"] = QPainter::RasterOp_NotDestination;
    env["QPainter"]["RasterOp_SourceOrNotDestination"] = QPainter::RasterOp_SourceOrNotDestination;

    // enum QPainter::PixmapFragmentHint
    env["QPainter"]["OpaqueHint"] = QPainter::OpaqueHint;

    // enum QPainter::RenderHint
    env["QPainter"]["Antialiasing"] = QPainter::Antialiasing;
    env["QPainter"]["TextAntialiasing"] = QPainter::TextAntialiasing;
    env["QPainter"]["SmoothPixmapTransform"] = QPainter::SmoothPixmapTransform;
    env["QPainter"]["HighQualityAntialiasing"] = QPainter::HighQualityAntialiasing;
    env["QPainter"]["NonCosmeticDefaultPen"] = QPainter::NonCosmeticDefaultPen;
    env["QPainter"]["Qt4CompatiblePainting"] = QPainter::Qt4CompatiblePainting;

    return 0;
}

#include "QPainter.hpp"
#include "../type/function.hpp"
#include "../type/numeric.hpp"
#include "../thread.hpp"
#include "QRect.hpp"
#include "QRectF.hpp"
#include "QTextOption.hpp"
#include "Qt.hpp"

#include <QPainter>
#include <QPaintEngine>

/*


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
            lua::get<QString>(state, 7)
        ));
        return 1;
    }

    if (lua::is_type<QRect>(state, 2)) {
        // QRect boundingRect(const QRect & rectangle, int flags, const QString & text)
        lua::push(state, self->boundingRect(
            lua::get<const QRect&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<QString>(state, 4)
        ));
        return 1;
    }
    if (lua_type(state, 3) == LUA_TNUMBER) {
        // QRectF boundingRect(const QRectF & rectangle, int flags, const QString & text)
        lua::push(state, self->boundingRect(
            lua::get<const QRectF&>(state, 2),
            lua::get<int>(state, 3),
            lua::get<QString>(state, 4)
        ));
        return 1;
    }

    // QRectF boundingRect(const QRectF & rectangle, const QString & text, const QTextOption & option = QTextOption())
    if (lua_gettop(state) > 3) {
        lua::push(state, self->boundingRect(
            lua::get<const QRectF&>(state, 2),
            lua::get<QString>(state, 3),
            lua::get<const QTextOption&>(state, 4)
        ));
        return 1;
    }

    lua::push(state, self->boundingRect(
        lua::get<const QRectF&>(state, 2),
        lua::get<QString>(state, 3)
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
    return 0;
}

int QPainter_drawLines(lua_State* const state)
{
    return 0;
}

int QPainter_drawPicture(lua_State* const state)
{
    return 0;
}

int QPainter_drawPie(lua_State* const state)
{
    return 0;
}

int QPainter_drawPixmap(lua_State* const state)
{
    return 0;
}

int QPainter_drawPixmapFragments(lua_State* const state)
{
    return 0;
}

int QPainter_drawPoint(lua_State* const state)
{
    return 0;
}

int QPainter_drawPoints(lua_State* const state)
{
    return 0;
}

int QPainter_drawPolygon(lua_State* const state)
{
    return 0;
}

int QPainter_drawPolyline(lua_State* const state)
{
    return 0;
}

int QPainter_drawRect(lua_State* const state)
{
    return 0;
}

int QPainter_drawRects(lua_State* const state)
{
    return 0;
}

int QPainter_drawRoundedRect(lua_State* const state)
{
    return 0;
}

int QPainter_drawStaticText(lua_State* const state)
{
    return 0;
}

int QPainter_drawText(lua_State* const state)
{
    auto painter = lua::get<QPainter*>(state, 1);
    painter->drawText(
        lua::get<int>(state, 2),
        lua::get<int>(state, 3),
        lua::get<QString>(state, 4)
    );
    return 0;
}

int QPainter_drawTiledPixmap(lua_State* const state)
{
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
    return 0;
}

int QPainter_setBrushOrigin(lua_State* const state)
{
    return 0;
}

int QPainter_setClipRect(lua_State* const state)
{
    return 0;
}

int QPainter_setPen(lua_State* const state)
{
    return 0;
}

int QPainter_setViewport(lua_State* const state)
{
    return 0;
}

int QPainter_setWindow(lua_State* const state)
{
    return 0;
}

int QPainter_translate(lua_State* const state)
{
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
    mt["setClipPath"] = &QPainter::setClipPath;
    mt["setClipRect"] = QPainter_setClipRect;
    mt["setClipRegion"] = &QPainter::setClipRegion;
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
    // QPainter ()
    // QPainter ( QPaintDevice * device )
    if (lua_gettop(state) > 1) {
        lua::make<QPainter>(state, lua::get<QPaintDevice*>(state, 2));
    } else {
        lua::make<QPainter>(state);
    }
    return 1;
}

int luaopen_luacxx_QPainter(lua_State* const state)
{
    lua::thread env(state);

    env["QPainter"] = lua::value::table;
    env["QPainter"]["new"] = QPainter_new;

    return 0;
}

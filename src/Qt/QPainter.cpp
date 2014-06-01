#include "QPainter.hpp"
#include "../type/function.hpp"
#include "../type/numeric.hpp"
#include "../thread.hpp"

#include <QPainter>
#include <QPaintEngine>

int QPainter_boundingRect(lua::state* const state)
{
    return 0;
}

int QPainter_drawArc(lua::state* const state)
{
    return 0;
}

int QPainter_drawChord(lua::state* const state)
{
    return 0;
}

int QPainter_drawConvexPolygon(lua::state* const state)
{
    return 0;
}

int QPainter_drawEllipse(lua::state* const state)
{
    return 0;
}

int QPainter_drawGlyphRun(lua::state* const state)
{
    return 0;
}

int QPainter_drawImage(lua::state* const state)
{
    return 0;
}

int QPainter_drawLine(lua::state* const state)
{
    return 0;
}

int QPainter_drawLines(lua::state* const state)
{
    return 0;
}

int QPainter_drawPicture(lua::state* const state)
{
    return 0;
}

int QPainter_drawPie(lua::state* const state)
{
    return 0;
}

int QPainter_drawPixmap(lua::state* const state)
{
    return 0;
}

int QPainter_drawPixmapFragments(lua::state* const state)
{
    return 0;
}

int QPainter_drawPoint(lua::state* const state)
{
    return 0;
}

int QPainter_drawPoints(lua::state* const state)
{
    return 0;
}

int QPainter_drawPolygon(lua::state* const state)
{
    return 0;
}

int QPainter_drawPolyline(lua::state* const state)
{
    return 0;
}

int QPainter_drawRect(lua::state* const state)
{
    return 0;
}

int QPainter_drawRects(lua::state* const state)
{
    return 0;
}

int QPainter_drawRoundedRect(lua::state* const state)
{
    return 0;
}

int QPainter_drawStaticText(lua::state* const state)
{
    return 0;
}

int QPainter_drawText(lua::state* const state)
{
    auto painter = lua::get<QPainter*>(state, 1);
    painter->drawText(
        lua::get<int>(state, 2),
        lua::get<int>(state, 3),
        lua::get<QString>(state, 4)
    );
    return 0;
}

int QPainter_drawTiledPixmap(lua::state* const state)
{
    return 0;
}

int QPainter_eraseRect(lua::state* const state)
{
    return 0;
}

int QPainter_fillRect(lua::state* const state)
{
    auto painter = lua::get<QPainter*>(state, 1);

    int x, y, width, height;
    x = lua::get<int>(state, 2),
    y = lua::get<int>(state, 3),
    width = lua::get<int>(state, 4),
    height = lua::get<int>(state, 5);

    painter->fillRect(x, y, width, height, Qt::white);
    return 0;
}

int QPainter_setBrush(lua::state* const state)
{
    return 0;
}

int QPainter_setBrushOrigin(lua::state* const state)
{
    return 0;
}

int QPainter_setClipRect(lua::state* const state)
{
    return 0;
}

int QPainter_setPen(lua::state* const state)
{
    return 0;
}

int QPainter_setViewport(lua::state* const state)
{
    return 0;
}

int QPainter_setWindow(lua::state* const state)
{
    return 0;
}

int QPainter_translate(lua::state* const state)
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

int QPainter_new(lua::state* const state)
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

int luaopen_luacxx_QPainter(lua::state* const state)
{
    lua::thread env(state);

    env["QPainter"] = lua::value::table;
    env["QPainter"]["new"] = QPainter_new;

    return 0;
}

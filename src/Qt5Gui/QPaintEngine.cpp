#include "QPaintEngine.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "QPainterPath.hpp"
#include "QPixmap.hpp"
#include "QPainter.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "QPaintDevice.hpp"
#include "QTextItem.hpp"
#include "QPaintEngineState.hpp"
#include "../Qt5Core/QFlags.hpp"

int QPaintEngine_drawEllipse(lua_State* const state)
{
    return 0;
}
int QPaintEngine_drawImage(lua_State* const state)
{
    return 0;
}
int QPaintEngine_drawLines(lua_State* const state)
{
    return 0;
}
int QPaintEngine_drawPoints(lua_State* const state)
{
    return 0;
}
int QPaintEngine_drawPolygon(lua_State* const state)
{
    return 0;
}
int QPaintEngine_drawRects(lua_State* const state)
{
    return 0;
}

namespace lua {

void QPaintEngine_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["begin"] = &QPaintEngine::begin;
    mt["drawEllipse"] = QPaintEngine_drawEllipse;
    mt["drawImage"] = QPaintEngine_drawImage;
    mt["drawLines"] = QPaintEngine_drawLines;
    mt["drawPath"] = &QPaintEngine::drawPath;
    mt["drawPixmap"] = &QPaintEngine::drawPixmap;
    mt["drawPoints"] = QPaintEngine_drawPoints;
    mt["drawPolygon"] = QPaintEngine_drawPolygon;
    mt["drawRects"] = QPaintEngine_drawRects;
    mt["drawTextItem"] = &QPaintEngine::drawTextItem;
    mt["drawTiledPixmap"] = &QPaintEngine::drawTiledPixmap;
    mt["end"] = &QPaintEngine::end;
    mt["hasFeature"] = &QPaintEngine::hasFeature;
    mt["isActive"] = &QPaintEngine::isActive;
    mt["paintDevice"] = &QPaintEngine::paintDevice;
    mt["painter"] = &QPaintEngine::painter;
    mt["setActive"] = &QPaintEngine::setActive;
    mt["type"] = &QPaintEngine::type;
    mt["updateState"] = &QPaintEngine::updateState;
}

} // namespace lua

int luaopen_Qt5Gui_QPaintEngine(lua_State* const state)
{
    lua::thread env(state);

    env["QPaintEngine"] = lua::value::table;
    auto t = env["QPaintEngine"];

    // enum QPaintEngine::DirtyFlag
    t["DirtyFlags"] = lua::QFlags_new<QPaintEngine::DirtyFlags>;
    t["DirtyPen"] = QPaintEngine::DirtyPen;
    t["DirtyBrush"] = QPaintEngine::DirtyBrush;
    t["DirtyBrushOrigin"] = QPaintEngine::DirtyBrushOrigin;
    t["DirtyFont"] = QPaintEngine::DirtyFont;
    t["DirtyBackground"] = QPaintEngine::DirtyBackground;
    t["DirtyBackgroundMode"] = QPaintEngine::DirtyBackgroundMode;
    t["DirtyTransform"] = QPaintEngine::DirtyTransform;
    t["DirtyClipRegion"] = QPaintEngine::DirtyClipRegion;
    t["DirtyClipPath"] = QPaintEngine::DirtyClipPath;
    t["DirtyHints"] = QPaintEngine::DirtyHints;
    t["DirtyCompositionMode"] = QPaintEngine::DirtyCompositionMode;
    t["DirtyClipEnabled"] = QPaintEngine::DirtyClipEnabled;
    t["DirtyOpacity"] = QPaintEngine::DirtyOpacity;
    t["AllDirty"] = QPaintEngine::AllDirty;

    // enum QPaintEngine::PaintEngineFeature
    t["PaintEngineFeatures"] = lua::QFlags_new<QPaintEngine::PaintEngineFeatures>;
    t["AlphaBlend"] = QPaintEngine::AlphaBlend;
    t["Antialiasing"] = QPaintEngine::Antialiasing;
    t["BlendModes"] = QPaintEngine::BlendModes;
    t["BrushStroke"] = QPaintEngine::BrushStroke;
    t["ConicalGradientFill"] = QPaintEngine::ConicalGradientFill;
    t["ConstantOpacity"] = QPaintEngine::ConstantOpacity;
    t["LinearGradientFill"] = QPaintEngine::LinearGradientFill;
    t["MaskedBrush"] = QPaintEngine::MaskedBrush;
    t["ObjectBoundingModeGradients"] = QPaintEngine::ObjectBoundingModeGradients;
    t["PainterPaths"] = QPaintEngine::PainterPaths;
    t["PaintOutsidePaintEvent"] = QPaintEngine::PaintOutsidePaintEvent;
    t["PatternBrush"] = QPaintEngine::PatternBrush;
    t["PatternTransform"] = QPaintEngine::PatternTransform;
    t["PerspectiveTransform"] = QPaintEngine::PerspectiveTransform;
    t["PixmapTransform"] = QPaintEngine::PixmapTransform;
    t["PorterDuff"] = QPaintEngine::PorterDuff;
    t["PrimitiveTransform"] = QPaintEngine::PrimitiveTransform;
    t["RadialGradientFill"] = QPaintEngine::RadialGradientFill;
    t["RasterOpModes"] = QPaintEngine::RasterOpModes;
    t["AllFeatures"] = QPaintEngine::AllFeatures;

    // enum QPaintEngine::PolygonDrawMode
    t["OddEvenMode"] = QPaintEngine::OddEvenMode;
    t["WindingMode"] = QPaintEngine::WindingMode;
    t["ConvexMode"] = QPaintEngine::ConvexMode;
    t["PolylineMode"] = QPaintEngine::PolylineMode;

    // enum QPaintEngine::Type
    t["X11"] = QPaintEngine::X11;
    t["Windows"] = QPaintEngine::Windows;
    t["MacPrinter"] = QPaintEngine::MacPrinter;
    t["CoreGraphics"] = QPaintEngine::CoreGraphics;
    t["QuickDraw"] = QPaintEngine::QuickDraw;
    t["QWindowSystem"] = QPaintEngine::QWindowSystem;
    t["PostScript"] = QPaintEngine::PostScript;
    t["OpenGL"] = QPaintEngine::OpenGL;
    t["Picture"] = QPaintEngine::Picture;
    t["SVG"] = QPaintEngine::SVG;
    t["Raster"] = QPaintEngine::Raster;
    t["Direct3D"] = QPaintEngine::Direct3D;
    t["Pdf"] = QPaintEngine::Pdf;
    t["OpenVG"] = QPaintEngine::OpenVG;
    t["User"] = QPaintEngine::User;
    t["MaxUser"] = QPaintEngine::MaxUser;
    t["OpenGL2"] = QPaintEngine::OpenGL2;
    t["PaintBuffer"] = QPaintEngine::PaintBuffer;
    t["Blitter"] = QPaintEngine::Blitter;
    t["Direct2D"] = QPaintEngine::Direct2D;

    return 0;
}

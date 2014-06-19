#include "QScreen.hpp"
#include "../type/function.hpp"
#include "../type/numeric.hpp"
#include "../thread.hpp"
#include "QRect.hpp"
#include "QSize.hpp"
#include "QPixmap.hpp"
#include "QTransform.hpp"
#include "QObject.hpp"

#include <QScreen>

void lua::QScreen_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);

    mt["angleBetween"] = &QScreen::angleBetween;
    mt["availableGeometry"] = &QScreen::availableGeometry;
    mt["availableSize"] = &QScreen::availableSize;
    mt["availableVirtualGeometry"] = &QScreen::availableVirtualGeometry;
    mt["availableVirtualSize"] = &QScreen::availableVirtualSize;
    mt["depth"] = &QScreen::depth;
    mt["devicePixelRatio"] = &QScreen::devicePixelRatio;
    mt["geometry"] = &QScreen::geometry;
    //mt["grabWindow"] = &QScreen::grabWindow;
    mt["isLandscape"] = &QScreen::isLandscape;
    mt["isPortrait"] = &QScreen::isPortrait;
    mt["logicalDotsPerInch"] = &QScreen::logicalDotsPerInch;
    mt["logicalDotsPerInchX"] = &QScreen::logicalDotsPerInchX;
    mt["logicalDotsPerInchY"] = &QScreen::logicalDotsPerInchY;
    mt["mapBetween"] = &QScreen::mapBetween;
    mt["name"] = &QScreen::name;
    mt["nativeOrientation"] = &QScreen::nativeOrientation;
    mt["orientation"] = &QScreen::orientation;
    mt["orientationUpdateMask"] = &QScreen::orientationUpdateMask;
    mt["physicalDotsPerInch"] = &QScreen::physicalDotsPerInch;
    mt["physicalDotsPerInchX"] = &QScreen::physicalDotsPerInchX;
    mt["physicalDotsPerInchY"] = &QScreen::physicalDotsPerInchY;
    mt["physicalSize"] = &QScreen::physicalSize;
    mt["primaryOrientation"] = &QScreen::primaryOrientation;
    mt["refreshRate"] = &QScreen::refreshRate;
    mt["setOrientationUpdateMask"] = &QScreen::setOrientationUpdateMask;
    mt["size"] = &QScreen::size;
    mt["transformBetween"] = &QScreen::transformBetween;
    mt["virtualGeometry"] = &QScreen::virtualGeometry;
    mt["virtualSiblings"] = &QScreen::virtualSiblings;
    mt["virtualSize"] = &QScreen::virtualSize;
}

int luaopen_luacxx_QScreen(lua_State* const state)
{
    lua::thread env(state);

    env["QScreen"] = lua::value::table;

    return 0;
}

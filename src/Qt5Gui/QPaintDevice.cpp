#include "QPaintDevice.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QPaintDevice>

void lua::QPaintDevice_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["colorCount"] = &QPaintDevice::colorCount;
    mt["depth"] = &QPaintDevice::depth;
    mt["devicePixelRatio"] = &QPaintDevice::devicePixelRatio;
    mt["height"] = &QPaintDevice::height;
    mt["heightMM"] = &QPaintDevice::heightMM;
    mt["logicalDpiX"] = &QPaintDevice::logicalDpiX;
    mt["logicalDpiY"] = &QPaintDevice::logicalDpiY;
    mt["paintingActive"] = &QPaintDevice::paintingActive;
    mt["physicalDpiX"] = &QPaintDevice::physicalDpiX;
    mt["physicalDpiY"] = &QPaintDevice::physicalDpiY;
    mt["width"] = &QPaintDevice::width;
    mt["widthMM"] = &QPaintDevice::widthMM;
}

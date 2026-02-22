#ifndef luacxx_QTouchDevice_INCLUDED
#define luacxx_QTouchDevice_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QTouchDevice>

// http://qt-project.org/doc/qt-5/qtouchdevice.html

LUA_METATABLE_BUILT(QTouchDevice)
LUA_METATABLE_ENUM(QTouchDevice::CapabilityFlag)
LUA_METATABLE_ENUM(QTouchDevice::DeviceType)

extern "C" int luaopen_Qt5Gui_QTouchDevice(lua_State* const);

#endif // luacxx_QTouchDevice_INCLUDED

#include "QTouchDevice.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QList.hpp"

// http://qt-project.org/doc/qt-5/qtouchdevice.html

namespace lua {

void QTouchDevice_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["capabilities"] = &QTouchDevice::capabilities;
    mt["maximumTouchPoints"] = &QTouchDevice::maximumTouchPoints;
    mt["name"] = &QTouchDevice::name;
    mt["setCapabilities"] = &QTouchDevice::setCapabilities;
    mt["setMaximumTouchPoints"] = &QTouchDevice::setMaximumTouchPoints;
    mt["setName"] = &QTouchDevice::setName;
    mt["setType"] = &QTouchDevice::setType;
    mt["type"] = &QTouchDevice::type;
}

} // namespace lua

int QTouchDevice_new(lua_State* const state)
{
    lua::make<QTouchDevice>(state);

    return 1;
}

int luaopen_Qt5Gui_QTouchDevice(lua_State* const state)
{
    lua::thread env(state);

    env["QTouchDevice"] = lua::value::table;
    env["QTouchDevice"]["new"] = QTouchDevice_new;
    auto t = env["QTouchDevice"];

    t["devices"] = QTouchDevice::devices;

    // enum QTouchDevice::CapabilityFlag
    t["Capabilities"] = lua::QFlags_new<QTouchDevice::Capabilities>;

    t["Position"] = QTouchDevice::Position;
    t["Area"] = QTouchDevice::Area;
    t["Pressure"] = QTouchDevice::Pressure;
    t["Velocity"] = QTouchDevice::Velocity;
    t["RawPositions"] = QTouchDevice::RawPositions;
    t["NormalizedPosition"] = QTouchDevice::NormalizedPosition;

    // enum QTouchDevice::DeviceType
    t["TouchScreen"] = QTouchDevice::TouchScreen;
    t["TouchPad"] = QTouchDevice::TouchPad;

    return 0;
}

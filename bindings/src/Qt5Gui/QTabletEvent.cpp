#include "QTabletEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/QPoint.hpp"

// http://qt-project.org/doc/qt-5/qtabletevent.html

namespace lua {

void QTabletEvent_metatable(lua_State* const state, const int pos)
{
    lua::QInputEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["device"] = &QTabletEvent::device;
    mt["globalPos"] = &QTabletEvent::globalPos;
    mt["globalPosF"] = &QTabletEvent::globalPosF;
    mt["globalX"] = &QTabletEvent::globalX;
    mt["globalY"] = &QTabletEvent::globalY;
    mt["hiResGlobalX"] = &QTabletEvent::hiResGlobalX;
    mt["hiResGlobalY"] = &QTabletEvent::hiResGlobalY;
    mt["pointerType"] = &QTabletEvent::pointerType;
    mt["pos"] = &QTabletEvent::pos;
    mt["posF"] = &QTabletEvent::posF;
    mt["pressure"] = &QTabletEvent::pressure;
    mt["rotation"] = &QTabletEvent::rotation;
    mt["tangentialPressure"] = &QTabletEvent::tangentialPressure;
    mt["uniqueId"] = &QTabletEvent::uniqueId;
    mt["x"] = &QTabletEvent::x;
    mt["xTilt"] = &QTabletEvent::xTilt;
    mt["y"] = &QTabletEvent::y;
    mt["yTilt"] = &QTabletEvent::yTilt;
    mt["z"] = &QTabletEvent::z;
}

} // namespace lua

int QTabletEvent_new(lua_State* const state)
{
    // QTabletEvent(Type type, const QPointF & pos, const QPointF & globalPos, int device, int pointerType, qreal pressure, int xTilt, int yTilt, qreal tangentialPressure, qreal rotation, int z, Qt::KeyboardModifiers keyState, qint64 uniqueID)
    lua::make<QTabletEvent>(state,
        lua::get<QEvent::Type>(state, 1),
        lua::get<const QPointF&>(state, 2),
        lua::get<const QPointF&>(state, 3),
        lua::get<int>(state, 4),
        lua::get<int>(state, 5),
        lua::get<qreal>(state, 6),
        lua::get<int>(state, 7),
        lua::get<int>(state, 8),
        lua::get<qreal>(state, 9),
        lua::get<qreal>(state, 10),
        lua::get<int>(state, 11),
        lua::get<Qt::KeyboardModifiers>(state, 12),
        lua::get<qint64>(state, 13)
    );

    return 1;
}

int luaopen_Qt5Gui_QTabletEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QTabletEvent"] = lua::value::table;
    env["QTabletEvent"]["new"] = QTabletEvent_new;
    auto t = env["QTabletEvent"];

    // enum QTabletEvent::PointerType
    t["UnknownPointer"] = QTabletEvent::UnknownPointer;
    t["Pen"] = QTabletEvent::Pen;
    t["Cursor"] = QTabletEvent::Cursor;
    t["Eraser"] = QTabletEvent::Eraser;

    // enum QTabletEvent::TabletDevice
    t["NoDevice"] = QTabletEvent::NoDevice;
    t["Puck"] = QTabletEvent::Puck;
    t["Stylus"] = QTabletEvent::Stylus;
    t["Airbrush"] = QTabletEvent::Airbrush;
    t["FourDMouse"] = QTabletEvent::FourDMouse;
    t["RotationStylus"] = QTabletEvent::RotationStylus;

    return 0;
}

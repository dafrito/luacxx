#include "QGraphicsEffect.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QGraphicsEffect>

#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QRectF.hpp"

void lua::QGraphicsEffect_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);

    mt["boundingRect"] = &QGraphicsEffect::boundingRect;
    mt["boundingRectFor"] = &QGraphicsEffect::boundingRectFor;
    mt["isEnabled"] = &QGraphicsEffect::isEnabled;
}

int luaopen_Qt5Widgets_QGraphicsEffect(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsEffect"] = lua::value::table;
    auto t = env["QGraphicsEffect"];

    // enum QGraphicsEffect::ChangeFlag
    t["SourceAttached"] = QGraphicsEffect::SourceAttached;
    t["SourceDetached"] = QGraphicsEffect::SourceDetached;
    t["SourceBoundingRectChanged"] = QGraphicsEffect::SourceBoundingRectChanged;
    t["SourceInvalidated"] = QGraphicsEffect::SourceInvalidated;

    // enum QGraphicsEffect::PixmapPadMode
    t["NoPad"] = QGraphicsEffect::NoPad;
    t["PadToTransparentBorder"] = QGraphicsEffect::PadToTransparentBorder;
    t["PadToEffectiveBoundingRect"] = QGraphicsEffect::PadToEffectiveBoundingRect;

    return 0;
}

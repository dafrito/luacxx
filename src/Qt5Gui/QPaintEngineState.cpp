#include "QPaintEngineState.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QBrush.hpp"
#include "QTransform.hpp"
#include "QPainterPath.hpp"
#include "QFont.hpp"
#include "QPainter.hpp"
#include "QPaintEngine.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "QRegion.hpp"
#include "QPen.hpp"
#include "../Qt5Core/QFlags.hpp"

namespace lua {

void QPaintEngineState_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["backgroundBrush"] = &QPaintEngineState::backgroundBrush;
    mt["backgroundMode"] = &QPaintEngineState::backgroundMode;
    mt["brush"] = &QPaintEngineState::brush;
    mt["brushNeedsResolving"] = &QPaintEngineState::brushNeedsResolving;
    mt["brushOrigin"] = &QPaintEngineState::brushOrigin;
    mt["clipOperation"] = &QPaintEngineState::clipOperation;
    mt["clipPath"] = &QPaintEngineState::clipPath;
    mt["clipRegion"] = &QPaintEngineState::clipRegion;
    mt["compositionMode"] = &QPaintEngineState::compositionMode;
    mt["font"] = &QPaintEngineState::font;
    mt["isClipEnabled"] = &QPaintEngineState::isClipEnabled;
    mt["opacity"] = &QPaintEngineState::opacity;
    mt["painter"] = &QPaintEngineState::painter;
    mt["pen"] = &QPaintEngineState::pen;
    mt["penNeedsResolving"] = &QPaintEngineState::penNeedsResolving;
    mt["renderHints"] = &QPaintEngineState::renderHints;
    mt["state"] = &QPaintEngineState::state;
    mt["transform"] = &QPaintEngineState::transform;
}

} // namespace lua

int QPaintEngineState_new(lua_State* const state)
{
    lua::make<QPaintEngineState>(state);
    return 1;
}

int luaopen_luacxx_QPaintEngineState(lua_State* const state)
{
    lua::thread env(state);

    env["QPaintEngineState"] = lua::value::table;
    env["QPaintEngineState"]["new"] = QPaintEngineState_new;
    auto t = env["QPaintEngineState"];

    return 0;
}

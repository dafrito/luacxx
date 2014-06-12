#include "QPainterPathStroker.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QPainterPath.hpp"
#include "QVector.hpp"
#include "QPen.hpp"

#include <QPainterPathStroker>

// http://qt-project.org/doc/qt-5/qpainterpathstroker.html

int QPainterPathStroker_setDashPattern(lua_State* const state)
{
    return 0;
}

void lua::QPainterPathStroker_metatable(const lua::index& mt)
{
    mt["capStyle"] = &QPainterPathStroker::capStyle;
    mt["createStroke"] = &QPainterPathStroker::createStroke;
    mt["curveThreshold"] = &QPainterPathStroker::curveThreshold;
    mt["dashOffset"] = &QPainterPathStroker::dashOffset;
    mt["dashPattern"] = &QPainterPathStroker::dashPattern;
    mt["joinStyle"] = &QPainterPathStroker::joinStyle;
    mt["miterLimit"] = &QPainterPathStroker::miterLimit;
    mt["setCapStyle"] = &QPainterPathStroker::setCapStyle;
    mt["setCurveThreshold"] = &QPainterPathStroker::setCurveThreshold;
    mt["setDashOffset"] = &QPainterPathStroker::setDashOffset;
    mt["setDashPattern"] = QPainterPathStroker_setDashPattern;
    mt["setJoinStyle"] = &QPainterPathStroker::setJoinStyle;
    mt["setMiterLimit"] = &QPainterPathStroker::setMiterLimit;
    mt["setWidth"] = &QPainterPathStroker::setWidth;
    mt["width"] = &QPainterPathStroker::width;
}

int QPainterPathStroker_new(lua::state* const state)
{
    switch (lua_gettop(state)) {
    case 1:
        lua::make<QPainterPathStroker>(state);
        break;
    case 2:
    default:
        lua::make<QPainterPathStroker>(state, lua::get<const QPen&>(state, 2));
    }

    return 1;
}

int luaopen_luacxx_QPainterPathStroker(lua::state* const state)
{
    lua::thread env(state);

    env["QPainterPathStroker"] = lua::value::table;
    env["QPainterPathStroker"]["new"] = QPainterPathStroker_new;

    return 0;
}

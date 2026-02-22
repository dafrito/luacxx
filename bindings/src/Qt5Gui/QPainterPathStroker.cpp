#include "QPainterPathStroker.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QPainterPath.hpp"
#include "QVector.hpp"
#include "QPen.hpp"

int QPainterPathStroker_setDashPattern(lua_State* const state)
{
    auto self = lua::get<QPainterPathStroker*>(state, 1);

    // void QPen::setDashPattern(const QVector<qreal> & pattern)
    if (lua_type(state, 2) == LUA_TTABLE) {
        QVector<qreal> pattern;
        for (int i = 1; i <= lua_rawlen(state, 2); ++i) {
            pattern.push_back(lua::table::get<qreal>(lua::index(state, 2), i));
        }
        self->setDashPattern(pattern);
    }
    self->setDashPattern(lua::get<const QVector<qreal>&>(state, 2));
    return 0;
}

void lua::QPainterPathStroker_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
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

int QPainterPathStroker_new(lua_State* const state)
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

int luaopen_Qt5Gui_QPainterPathStroker(lua_State* const state)
{
    lua::thread env(state);

    env["QPainterPathStroker"] = lua::value::table;
    env["QPainterPathStroker"]["new"] = QPainterPathStroker_new;

    return 0;
}

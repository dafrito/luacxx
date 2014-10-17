#include "QTime.hpp"
#include "../thread.hpp"

int QTime_setHMS(lua_State* const state)
{
    return 0;
}
int QTime_toString(lua_State* const state)
{
    return 0;
}
int QTime_isValid(lua_State* const state)
{
    return 0;
}

void lua::QTime_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["addMSecs"] = &QTime::addMSecs;
    mt["addSecs"] = &QTime::addSecs;
    mt["elapsed"] = &QTime::elapsed;
    mt["hour"] = &QTime::hour;
    mt["isNull"] = &QTime::isNull;
    mt["isValid"] = QTime_isValid;
    mt["minute"] = &QTime::minute;
    mt["msec"] = &QTime::msec;
    mt["msecsSinceStartOfDay"] = &QTime::msecsSinceStartOfDay;
    mt["msecsTo"] = &QTime::msecsTo;
    mt["restart"] = &QTime::restart;
    mt["second"] = &QTime::second;
    mt["secsTo"] = &QTime::secsTo;
    mt["setHMS"] = QTime_setHMS;
    mt["toString"] = QTime_toString;
    mt["start"] = &QTime::start;
}

int QTime_new(lua_State* const state)
{
    switch (lua::size(state)) {
    case 0:
    case 1:
        lua::make<QTime>(state);
        break;
    case 3:
        lua::make<QTime>(state,
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        );
        break;
    case 4:
        lua::make<QTime>(state,
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4)
        );
        break;
    case 5:
    default:
        lua::make<QTime>(state,
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5)
        );
        break;
    }

    return 1;
}

int QTime_fromString(lua_State* const state)
{
    return 0;
}
int QTime_isValid_static(lua_State* const state)
{
    return 0;
}

int luaopen_luacxx_QTime(lua_State* const state)
{
    lua::thread env(state);

    env["QTime"] = lua::value::table;
    env["QTime"]["new"] = QTime_new;
    auto t = env["QTime"];

    t["currentTime"] = &QTime::currentTime;
    t["fromMSecsSinceStartOfDay"] = &QTime::fromMSecsSinceStartOfDay;
    t["fromString"] = QTime_fromString;
    t["isValid"] = QTime_isValid_static;

    return 0;
}

#include "QElapsedTimer.hpp"
#include "../luacxx/convert/callable.hpp"
#include "../luacxx/convert/numeric.hpp"
#include "../luacxx/thread.hpp"

#include <QElapsedTimer>

void lua::QElapsedTimer_metatable(const lua::index& mt)
{
    mt["elapsed"] = &QElapsedTimer::elapsed;
    mt["hasExpired"] = &QElapsedTimer::hasExpired;
    mt["invalidate"] = &QElapsedTimer::invalidate;
    mt["isValid"] = &QElapsedTimer::isValid;
    mt["msecsSinceReference"] = &QElapsedTimer::msecsSinceReference;
    mt["msecsTo"] = &QElapsedTimer::msecsTo;
    mt["nsecsElapsed"] = &QElapsedTimer::nsecsElapsed;
    mt["restart"] = &QElapsedTimer::restart;
    mt["secsTo"] = &QElapsedTimer::secsTo;
    mt["start"] = &QElapsedTimer::start;
}

int QElapsedTimer_new(lua_State* const state)
{
    lua::make<QElapsedTimer>(state);
    return 1;
}

int luaopen_Qt5Core_QElapsedTimer(lua_State* const state)
{
    lua::thread env(state);

    env["QElapsedTimer"] = lua::value::table;
    env["QElapsedTimer"]["new"] = QElapsedTimer_new;
    env["QElapsedTimer"]["isMonotonic"] = &QElapsedTimer::isMonotonic;
    //env["QElapsedTimer"]["clockType"] = &QElapsedTimer::clockType;

    return 0;
}

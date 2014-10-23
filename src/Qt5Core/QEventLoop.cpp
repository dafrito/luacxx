#include "QEventLoop.hpp"
#include <QEventLoop>

#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QObject.hpp"
#include "QFlags.hpp"

int QEventLoop_processEvents(lua_State* const state)
{
    return 0;
}

void lua::QEventLoop_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["exec"] = &QEventLoop::exec;
    mt["exit"] = &QEventLoop::exit;
    mt["isRunning"] = &QEventLoop::isRunning;
    mt["processEvents"] = QEventLoop_processEvents;
    mt["wakeUp"] = &QEventLoop::wakeUp;
}

int QEventLoop_new(lua_State* const state)
{
    lua::make<QEventLoop>(state);
    return 1;
}

int luaopen_Qt5Core_QEventLoop(lua_State* const state)
{
    lua::thread env(state);

    env["QEventLoop"] = lua::value::table;
    env["QEventLoop"]["new"] = QEventLoop_new;
    auto t = env["QEventLoop"];

    // enum QEventLoop::ProcessEventsFlag
    t["ProcessEventsFlags"] = lua::QFlags_new<QEventLoop::ProcessEventsFlag>;
    t["AllEvents"] = QEventLoop::AllEvents;
    t["ExcludeUserInputEvents"] = QEventLoop::ExcludeUserInputEvents;
    t["ExcludeSocketNotifiers"] = QEventLoop::ExcludeSocketNotifiers;
    t["WaitForMoreEvents"] = QEventLoop::WaitForMoreEvents;

    return 0;
}

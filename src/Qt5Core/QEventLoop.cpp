#include "QEventLoop.hpp"
#include <QEventLoop>

#include "../luacxx/convert/callable.hpp"
#include "../luacxx/thread.hpp"
#include "QObject.hpp"

int QEventLoop_processEvents(lua_State* const state)
{
    return 0;
}

void lua::QEventLoop_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);

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

    // enum QEventLoop::ProcessEventsFlag
    // flags QEventLoop::ProcessEventsFlags
    env["QEventLoop"]["AllEvents"] = QEventLoop::AllEvents;
    env["QEventLoop"]["ExcludeUserInputEvents"] = QEventLoop::ExcludeUserInputEvents;
    env["QEventLoop"]["ExcludeSocketNotifiers"] = QEventLoop::ExcludeSocketNotifiers;
    env["QEventLoop"]["WaitForMoreEvents"] = QEventLoop::WaitForMoreEvents;

    return 0;
}

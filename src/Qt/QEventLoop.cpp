#include "QEventLoop.hpp"
#include <QEventLoop>

#include "../type/function.hpp"
#include "../thread.hpp"
#include <iostream>

void lua::QEventLoop_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int QEventLoop_new(lua_State* const state)
{
    lua::make<QEventLoop>(state);
    return 1;
}

int luaopen_luacxx_QEventLoop(lua_State* const state)
{
    lua::thread env(state);

    env["QEventLoop"] = lua::value::table;
    env["QEventLoop"]["new"] = QEventLoop_new;

    env["QEventLoop"]["AllEvents"] = QEventLoop::AllEvents;
    env["QEventLoop"]["ExcludeUserInputEvents"] = QEventLoop::ExcludeUserInputEvents;
    env["QEventLoop"]["ExcludeSocketNotifiers"] = QEventLoop::ExcludeSocketNotifiers;
    env["QEventLoop"]["WaitForMoreEvents"] = QEventLoop::WaitForMoreEvents;

    return 0;
}

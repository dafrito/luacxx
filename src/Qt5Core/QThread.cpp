#include "QThread.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QAbstractEventDispatcher.hpp"
#include "QObject.hpp"

int QThread_exit(lua_State* const state)
{
    return 0;
}
int QThread_wait(lua_State* const state)
{
    return 0;
}

namespace lua {

void QThread_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["eventDispatcher"] = &QThread::eventDispatcher;
    mt["exit"] = QThread_exit;
    mt["isFinished"] = &QThread::isFinished;
    mt["isInterruptionRequested"] = &QThread::isInterruptionRequested;
    mt["isRunning"] = &QThread::isRunning;
    mt["priority"] = &QThread::priority;
    mt["requestInterruption"] = &QThread::requestInterruption;
    mt["setEventDispatcher"] = &QThread::setEventDispatcher;
    mt["setPriority"] = &QThread::setPriority;
    mt["setStackSize"] = &QThread::setStackSize;
    mt["stackSize"] = &QThread::stackSize;
    mt["wait"] = QThread_wait;
}

} // namespace lua

int QThread_new(lua_State* const state)
{
    // QThread(QObject * parent = 0)
    lua::make<QThread>(state);

    return 1;
}

int luaopen_Qt5Core_QThread(lua_State* const state)
{
    lua::thread env(state);

    env["QThread"] = lua::value::table;
    env["QThread"]["new"] = QThread_new;
    auto t = env["QThread"];

    t["currentThread"] = QThread::currentThread;
    t["currentThreadId"] = QThread::currentThreadId;
    t["idealThreadCount"] = QThread::idealThreadCount;
    t["msleep"] = QThread::msleep;
    t["sleep"] = QThread::sleep;
    t["usleep"] = QThread::usleep;
    t["yieldCurrentThread"] = QThread::yieldCurrentThread;

    // enum QThread::Priority
    t["IdlePriority"] = QThread::IdlePriority;
    t["LowestPriority"] = QThread::LowestPriority;
    t["LowPriority"] = QThread::LowPriority;
    t["NormalPriority"] = QThread::NormalPriority;
    t["HighPriority"] = QThread::HighPriority;
    t["HighestPriority"] = QThread::HighestPriority;
    t["TimeCriticalPriority"] = QThread::TimeCriticalPriority;
    t["InheritPriority"] = QThread::InheritPriority;

    return 0;
}

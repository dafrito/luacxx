#include "QAbstractEventDispatcher.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../convert/const_char_p.hpp"
#include "QObject.hpp"
#include "QByteArray.hpp"
#include "QEventLoop.hpp"
#include "Qt.hpp"
#include "QList.hpp"
#include "QAbstractNativeEventFilter.hpp"
#include "QFlags.hpp"
#include "QSocketNotifier.hpp"
#include "QThread.hpp"

int QAbstractEventDispatcher_registerTimer(lua_State* const state)
{
    return 0;
}

namespace lua {

void QAbstractEventDispatcher_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["filterNativeEvent"] = &QAbstractEventDispatcher::filterNativeEvent;
    mt["flush"] = &QAbstractEventDispatcher::flush;
    mt["installNativeEventFilter"] = &QAbstractEventDispatcher::installNativeEventFilter;
    mt["interrupt"] = &QAbstractEventDispatcher::interrupt;
    mt["processEvents"] = &QAbstractEventDispatcher::processEvents;
    //virtual bool    registerEventNotifier(QWinEventNotifier * notifier) = 0
    mt["registerSocketNotifier"] = &QAbstractEventDispatcher::registerSocketNotifier;
    mt["registerTimer"] = QAbstractEventDispatcher_registerTimer;
    //mt["registeredTimers"] = &QAbstractEventDispatcher::registeredTimers;
    mt["remainingTime"] = &QAbstractEventDispatcher::remainingTime;
    mt["removeNativeEventFilter"] = &QAbstractEventDispatcher::removeNativeEventFilter;
    //virtual void    unregisterEventNotifier(QWinEventNotifier * notifier) = 0
    mt["unregisterSocketNotifier"] = &QAbstractEventDispatcher::unregisterSocketNotifier;
    mt["unregisterTimer"] = &QAbstractEventDispatcher::unregisterTimer;
    mt["unregisterTimers"] = &QAbstractEventDispatcher::unregisterTimers;
    mt["wakeUp"] = &QAbstractEventDispatcher::wakeUp;
}

} // namespace lua

int QAbstractEventDispatcher_instance(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::push(state, QAbstractEventDispatcher::instance());
    } else {
        lua::push(state, QAbstractEventDispatcher::instance(lua::get<QThread*>(state, 1)));
    }
    return 1;
}

int luaopen_Qt5Core_QAbstractEventDispatcher(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractEventDispatcher"] = lua::value::table;
    auto t = env["QAbstractEventDispatcher"];

    t["instance"] = QAbstractEventDispatcher_instance;

    return 0;
}


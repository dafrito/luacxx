#include "QObjectObserver.hpp"

namespace lua {

QObjectObserver::QObjectObserver(
        const QObject* const object,
        LuaUserdata* const userdata) :
    object(object),
    userdata(userdata),
    _destroyOnGC(false)
{
    // Watch for destruction from C++
    connect(object, SIGNAL(destroyed(QObject*)), this, SLOT(destroyedFromC()));

    // Watch for destruction from Lua
    userdata->setManager([this]() { destroyedFromLua(); });
}

void QObjectObserver::destroyedFromC()
{
    object = nullptr;
    if (userdata) {
        userdata->reset();
        userdata = nullptr;
    }
}

void QObjectObserver::destroyedFromLua()
{
    userdata = nullptr;
    if (_destroyOnGC && object) {
        delete object;
        object = nullptr;
    }
}

QObjectObserver::~QObjectObserver()
{
    destroyedFromC();
}

} // namespace lua

// vim: set ts=4 sw=4 :

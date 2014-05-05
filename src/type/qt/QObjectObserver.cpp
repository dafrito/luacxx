#include "QObjectObserver.hpp"

#include <iostream>
#include <cassert>

namespace lua {

QObjectObserver::QObjectObserver(
        const QObject* const object,
        LuaUserdata* const userdata) :
    object(object),
    userdata(userdata),
    _destroyOnGC(false)
{
    if (!userdata->managed()) {
        throw std::logic_error("Refusing to manage a non-managed userdata");
    }

    // Watch for destruction from C++
    connect(object, SIGNAL(destroyed(QObject*)), this, SLOT(destroyedFromC()));

    // Watch for destruction from Lua
    userdata->setManager([this]() { destroyedFromLua(); });
}

void QObjectObserver::destroyedFromC()
{
    if (!userdata) {
        // Already destroyed from Lua
        assert(!object);
        return;
    }
    //std::cout << userdata->dataType() << " destroyed from C++" << std::endl;
    object = nullptr;
    if (userdata) {
        auto tmp = userdata;
        userdata = nullptr;
        tmp->reset();
    }
}

void QObjectObserver::destroyedFromLua()
{
    if (!object) {
        // Already destroyed from C++
        assert(!userdata);
        return;
    }
    //std::cout << userdata->dataType() << " destroyed from Lua" << std::endl;
    userdata = nullptr;
    if (_destroyOnGC && object) {
        auto tmp = object;
        object = nullptr;
        delete tmp;
    }
}

void QObjectObserver::setDestroyOnGC(const bool destroy)
{
    _destroyOnGC = destroy;
    if (!userdata) {
        destroyedFromLua();
    }
}

QObjectObserver::~QObjectObserver()
{
    destroyedFromC();
}

} // namespace lua

// vim: set ts=4 sw=4 :

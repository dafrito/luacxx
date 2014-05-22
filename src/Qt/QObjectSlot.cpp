#include "Qt/QObjectSlot.hpp"
#include "Qt/QVariant.hpp"

#include "../algorithm.hpp"

#include <iostream>

lua::QObjectSlot::QObjectSlot(QObject* const parent, const QMetaMethod& signal, const lua::index& slot) :
    QObject(parent),
    _signal(signal),
    _slot(slot)
{
}

int lua::QObjectSlot::qt_metacall(QMetaObject::Call call, int id, void **arguments)
{
    auto state = _slot.state();
    auto callable = lua::push(state, _slot);

    QList<QByteArray> params = _signal.parameterTypes();
    for (int i = 0; i < params.count(); ++i) {
        lua::push(state, QVariant(
            QMetaType::type(params.at(i)),
            arguments[1 + i]
        ));
    }

    try {
        lua::invoke(callable);
    } catch (lua::error& ex) {
        std::cerr << "lua::QObjectSlot::qt_metacall: Error caught during slot invocation: " << ex.what() << std::endl;
    }

    return -1;
}

/**
 * This connect/disconnect stuff works around the fact that our returned
 * function from connect() can't modify the pointer's value. As a result,
 * I need some arbitrary place to have information regarding the liveness
 * of a slot.
 *
 * Note that Qt's signal/slot invocation doesn't need this. We only need
 * it to ensure the Lua side can safely disconnect from a slot.
 */
static std::unordered_set<lua::QObjectSlot*> activeSlots;

lua::QObjectSlot::~QObjectSlot()
{
    activeSlots.erase(this);
}

void lua::QObjectSlot::connect(lua::QObjectSlot* const slot)
{
    activeSlots.insert(slot);
}

void lua::QObjectSlot::disconnect(lua::QObjectSlot* const slot)
{
    if (activeSlots.find(slot) != activeSlots.end()) {
        delete slot;
    }
}

#include "QObjectSlot.hpp"

#include <iostream>
#include "type/QVariant.hpp"

lua::QObjectSlot::QObjectSlot(QObject* const parent, const QMetaMethod& signal, const LuaReference& slot) :
    QObject(parent),
    _signal(signal),
    _slot(slot)
{
}

int lua::QObjectSlot::qt_metacall(QMetaObject::Call call, int id, void **arguments)
{
    LuaStack stack(_slot.luaState());
    _slot.push(stack);

    stack.setAcceptsStackUserdata(true);

    QList<QByteArray> params = _signal.parameterTypes();
    for (int i = 0; i < params.count(); ++i) {
        lua::push(stack, QVariant(
            QMetaType::type(params.at(i)),
            arguments[1 + i]
        ));
    }

    try {
        stack.pushedInvoke(params.count());
    } catch(LuaException& ex) {
        std::cerr << "A Lua exception occurred while invoking a Qt slot:\n\t" << ex.what() << std::endl;
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

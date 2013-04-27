#include "QObjectSlot.hpp"
#include <iostream>
#include <QVariant>

int lua::QObjectSlot::qt_metacall(QMetaObject::Call call, int id, void **arguments)
{
    LuaStack stack(_slot.lua());
    _slot.push(stack);

    stack.setAcceptsStackUserdata(true);

    QList<QByteArray> params = _signal.parameterTypes();
    for (int i = 0; i < params.count(); ++i) {
        lua::push(stack, QVariant(
            QMetaType::type(params.at(i)),
            arguments[1 + i]
        ));
    }

    stack.pushedInvoke(params.count());

    return -1;
}

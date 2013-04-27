#ifndef QOBJECTSLOT_HEADER
#define QOBJECTSLOT_HEADER

#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>

#include "LuaStack.hpp"
#include "LuaEnvironment.hpp"
#include "LuaValue.hpp"

namespace lua {

class QObjectSlot : public QObject
{
    QMetaMethod _signal;
    LuaReference _slot;
public:
    QObjectSlot(QObject* const parent, const QMetaMethod& signal, const LuaReference& slot) :
        QObject(parent),
        _signal(signal),
        _slot(slot)
    {
    }

    int qt_metacall(QMetaObject::Call call, int id, void **arguments);

    virtual ~QObjectSlot()
    {
    }
};

} // namespace lua

#endif // QOBJECTSLOT_HEADER

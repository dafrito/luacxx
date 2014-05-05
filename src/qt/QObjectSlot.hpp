#ifndef QOBJECTSLOT_HEADER
#define QOBJECTSLOT_HEADER

#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>
#include <memory>
#include <unordered_set>

#include "LuaStack.hpp"
#include "LuaEnvironment.hpp"
#include "LuaValue.hpp"
#include "qobject.hpp"

namespace lua {

class QObjectSlot : public QObject
{
    QMetaMethod _signal;
    LuaReference _slot;
public:
    QObjectSlot(QObject* const parent, const QMetaMethod& signal, const LuaReference& slot);

    int qt_metacall(QMetaObject::Call call, int id, void **arguments);

    virtual ~QObjectSlot();

    static void disconnect(QObjectSlot* const slot);
    static void connect(QObjectSlot* const slot);
};

} // namespace lua

#endif // QOBJECTSLOT_HEADER

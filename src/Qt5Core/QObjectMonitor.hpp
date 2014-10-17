#ifndef LUACXX_QOBJECTMONITOR_INCLUDED
#define LUACXX_QOBJECTMONITOR_INCLUDED

#include "Qt5Core.hpp"

#include <QObject>

namespace lua {

class QObjectMonitor : public QObject
{
    Q_OBJECT

    const QObject* object;
    LuaUserdata* userdata;
    bool _destroyOnGC;
public:
    QObjectMonitor(const QObject* const object, LuaUserdata* const userdata);

    void setDestroyOnGC(const bool destroy);

    ~QObjectMonitor();

public slots:
    void destroyedFromLua();
    void destroyedFromC();
};

} // namespace lua

#endif // LUACXX_QOBJECTMONITOR_INCLUDED

// vim: set ts=4 sw=4 :

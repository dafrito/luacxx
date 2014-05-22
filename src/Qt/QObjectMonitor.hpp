#ifndef LUA_CXX_QOBJECTMONITOR_HEADER
#define LUA_CXX_QOBJECTMONITOR_HEADER

#include "../stack.hpp"

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

#endif // LUA_CXX_QOBJECTMONITOR_HEADER

// vim: set ts=4 sw=4 :

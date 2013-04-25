#ifndef LUA_CXX_QOBJECTOBSERVER_HEADER
#define LUA_CXX_QOBJECTOBSERVER_HEADER

#include <QObject>
#include "LuaUserdata.hpp"

namespace lua {

class QObjectObserver : public QObject
{
    Q_OBJECT

    const QObject* object;
    LuaUserdata* userdata;
    bool _destroyOnGC;
public:
    QObjectObserver(const QObject* const object, LuaUserdata* const userdata);

    void setDestroyOnGC(const bool destroy)
    {
        _destroyOnGC = destroy;
    }

    ~QObjectObserver();

public slots:
    void destroyedFromLua();
    void destroyedFromC();
};

}


#endif // LUA_CXX_QOBJECTOBSERVER_HEADER

// vim: set ts=4 sw=4 :

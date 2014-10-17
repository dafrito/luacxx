#ifndef LUACXX_tests_Qt5Core_INCLUDED
#define LUACXX_tests_Qt5Core_INCLUDED

#include "Qt5Core/QObject.hpp"

#include <QObject>
#include <QPoint>

class QtPoint : public QObject
{
    Q_OBJECT

    int _x;
    int _y;

    Q_PROPERTY(int x READ getX WRITE setX)
    Q_PROPERTY(int y READ getY WRITE setY)
public:

    QtPoint() :
        _x(),
        _y()
    {
    }

    QtPoint(const int x, const int y) :
        _x(x),
        _y(y)
    {
    }

    Q_INVOKABLE void setX(const int x)
    {
        _x = x;
        emit xChanged();
    }

    Q_INVOKABLE const int getX() const
    {
        return _x;
    }

    Q_INVOKABLE void setY(const int y)
    {
        _y = y;
        emit yChanged();
    }

    Q_INVOKABLE const int getY() const
    {
        return _y;
    }

    Q_INVOKABLE int values(lua_State* const state)
    {
        lua::push(state, _x, _y);
        return 2;
    }

signals:
    void xChanged() const;
    void yChanged() const;
};

LUA_METATABLE_QOBJECT(QtPoint)

#endif // LUACXX_tests_Qt5Core_INCLUDED

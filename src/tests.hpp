#ifndef LUACXX_TESTS_INCLUDED
#define LUACXX_TESTS_INCLUDED

#include <boost/test/unit_test.hpp>

#include <functional>

#include "luacxx/range.hpp"
#include "Qt5Core/QObject.hpp"

#include <QObject>
#include <QPoint>

#include <sstream>

class Counter
{
    int _count;

public:
    Counter(const int count) :
        _count(count)
    {}

    Counter() :
        _count()
    {}

    int get() const
    {
        return _count;
    }

    void set(const int& value)
    {
        _count = value;
    }

    template <class Exception>
    void check(const int& expected)
    {
        if (_count != expected) {
            std::stringstream str;
            str << expected << " expected, but count was " << _count;
            throw Exception(str.str());
        }
    }
};

template <class T>
class Point {
    T _x;
    T _y;

public:
    Point(const T& x, const T& y) :
        _x(x),
        _y(y)
    {
    }

    Point() :
        _x(),
        _y()
    {
    }

    void setX(const int x)
    {
        _x = x;
    }

    const int x() const
    {
        return _x;
    }

    void setY(const int y)
    {
        _y = y;
    }

    const int y() const
    {
        return _y;
    }

};

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

signals:
    void xChanged() const;
    void yChanged() const;
};

namespace lua {

template <>
struct Metatable<QtPoint>
{
    static constexpr const char* name = "QtPoint";

    static bool metatable(const lua::index& mt, const QtPoint* const)
    {
        lua::QObject_metatable(mt);
        return true;
    }
};

}; // namespace lua

#endif // LUACXX_TESTS_INCLUDED

// vim: set ts=4 sw=4 :

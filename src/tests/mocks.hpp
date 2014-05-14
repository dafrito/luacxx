#ifndef LUA_CXX_TESTS_MOCKS_HEADER
#define LUA_CXX_TESTS_MOCKS_HEADER

#include <QObject>
#include <QPoint>

#include "range.hpp"

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

/*
class Sum : public QObject
{
    Q_OBJECT

    std::vector<int> _parts;

    Q_PROPERTY(int value READ getValue WRITE setValue);
    Q_PROPERTY(QPoint point READ getPoint WRITE setPoint);

public:

    void setValue(const int value) {
        if (this->value != value) {
            this->value = value;
            emit valueChanged(value);
            emit stringEmitted("Hello!");
            emit pointEmitted(getPoint());
        }
    }

    void setAddedValue(const int x, const int y)
    {
        setValue(x + y);
    }

    int getValue() const { return value; }

    void set(const Counter& other)
    {
        setValue(other.getValue());
    }

    int addAll(lua::state* const state)
    {
        for (auto i : lua::range<decltype(value)>(state)) {
            value += i;
        }
        return 0;
    }

    int summed(lua::state* const state)
    {
        // Be sure not to touch the stack here, so we can ensure
        // our caller cleans everything up for us.
        auto total = getValue();
        for (auto value : lua::range<int>(state)) {
            total += value;
        }
        return total;
    }
    void stringEmitted(const QString& value) const;
    void pointEmitted(const QPoint& value) const;
public:
    Counter(int value = 0) : value(value) {}
};
*/

namespace {

int addToMagicNumber(int v)
{
    return 42 + v;
}

double addNumbers(int a, int b)
{
    return a + b;
}

double addBonanza(int a, long b, float c, double d, short e)
{
    return a + b + c + d + e;
}

int luaAdd(lua::state* const state)
{
    auto a = lua::get<int>(state, 1);
    auto b = lua::get<int>(state, 2);
    lua_settop(state, 0);
    lua::push(state, a + b);
    return 1;
}

int getMagicNumber()
{
    return 42;
}

void noop(int)
{
}

} // namespace anonymous

#endif // LUA_CXX_TESTS_MOCKS_HEADER

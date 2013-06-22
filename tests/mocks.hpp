#ifndef MOCKS_HPP
#define MOCKS_HPP

#include <QObject>
#include <QPoint>
#include "LuaEnvironment.hpp"
#include "LuaStack.hpp"

class Blank
{
    int _count;

public:
    Blank(const int count) :
        _count(count)
    {}

    int count() const
    {
        return _count;
    }
};

class Square : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int x READ getX WRITE setX)
    Q_PROPERTY(int y READ getY WRITE setY)
public:
    int x, y;

    Square() :
        x(),
        y()
    {
    }

    void setX(int x)
    {
        this->x = x;
    }
    const int getX() const
    {
        return x;
    }
    void setY(int y)
    {
        this->y = y;
    }
    const int getY() const
    {
        return y;
    }
};

class Counter : public QObject
{
    Q_OBJECT
    int value;
    QPoint point;

    Q_PROPERTY(int value READ getValue WRITE setValue);
    Q_PROPERTY(QPoint point READ getPoint WRITE setPoint);

public:
    QPoint getPoint()
    {
        return point;
    }

    void setPoint(const QPoint& point)
    {
        this->point = point;
    }
public slots:
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

    void addAll(LuaStack& stack)
    {
        while (!stack.empty()) {
            value += stack.as<decltype(value)>(1);
            stack.shift();
        }
    }

    int summed(LuaStack& stack)
    {
        // Be sure not to touch the stack here, so we can ensure
        // our caller cleans everything up for us.
        auto total = getValue();
        for (unsigned int i = 0; i < stack.size(); ++i) {
            total += stack.as<int>(i + 1);
        }
        return total;
    }
signals:
    void valueChanged(int value) const;
    void stringEmitted(const QString& value) const;
    void pointEmitted(const QPoint& value) const;
public:
    Counter(int value = 0) : value(value) {}
};

#endif // MOCKS_HPP

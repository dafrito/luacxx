#ifndef LUACXX_TESTS_INCLUDED
#define LUACXX_TESTS_INCLUDED

#include <boost/test/unit_test.hpp>

#include <functional>

#include "range.hpp"

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

#endif // LUACXX_TESTS_INCLUDED

// vim: set ts=4 sw=4 :

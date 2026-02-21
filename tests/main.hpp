#ifndef LUACXX_TESTS_INCLUDED
#define LUACXX_TESTS_INCLUDED

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <functional>

#include "luacxx/stack.hpp"

#include "luacxx/convert/const_char_p.hpp"
#include "luacxx/convert/numeric.hpp"
#include "luacxx/convert/string.hpp"
#include "luacxx/convert/char.hpp"
#include "luacxx/convert/callable.hpp"
#include "luacxx/convert/shared_ptr.hpp"

#include "luacxx/range.hpp"
#include "luacxx/thread.hpp"
#include "luacxx/algorithm.hpp"
#include "luacxx/load.hpp"
#include "luacxx/reference.hpp"

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

LUA_METATABLE_NAMED(Counter);

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

    int x() const
    {
        return _x;
    }

    void setY(const int y)
    {
        _y = y;
    }

    int y() const
    {
        return _y;
    }

};

template <class T>
struct lua::Metatable<Point<T>> {

    static const userdata_type& info()
    {
        static userdata_type _info;
        if (!_info.has_name()) {
            std::string name = "Point<";
            name += lua::Metatable<T>::info().name();
            name += ">";
            _info.set_name(name);

            _info.add_cast<Point<T>>();
        }
        return _info;
    }

    static bool metatable(lua_State* const, const int, const void* const)
    {
        return true;
    }
};

#endif // LUACXX_TESTS_INCLUDED

// vim: set ts=4 sw=4 :

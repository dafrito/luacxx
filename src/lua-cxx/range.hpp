#ifndef LUA_CXX_RANGE_HEADER
#define LUA_CXX_RANGE_HEADER

#include "stack.hpp"

/*

=head1 NAME

lua::range - iterable Lua stacks

=head1 SYNOPSIS

    #include <luacxx/range.hpp>

    int foo_sum(lua_State* const state)
    {
        int sum = 0;
        for (int value : lua::range<int>(state)) {
            sum += value;
        }
        lua_settop(state, 0);
        lua::push(state, sum);
        return 1;
    }

    int luaopen_Foo(lua_State* const state)
    {
        lua::thread env(state);
        env["Foo"] = lua::value::table;

        env["Foo"]["Sum"] = foo_sum;

        return 0;
    }

=head1 DESCRIPTION

=head2 lua::range<Value>(state)

Constructs an iterable that can be used in a for-loop. A range has a
begin() and an end() that will return iterators.

    int string_join(lua_State* const state)
    {
        std::stringstream str;
        bool first = true;
        for (std::string name : lua::range<std::string>(state)) {
            str << (first ? "" : " ") << name;
        }
    }

The above example is equivalent to the following code:

    int string_join(lua_State* const state)
    {
        std::stringstream str;
        bool first = true;
        for (lua::iterator iter(state); iter; ++i) {
            auto name = iter.get<std::string>();
            str << (first ? "" : " ") << str;
        }
    }
*/

namespace lua {

template <class T>
class iterator {
    lua_State* const _state;
    int _pos;

public:
    iterator(lua_State* const state) :
        iterator(state, 1)
    {
    }

    iterator(lua_State* const state, int pos) :
        _state(state),
        _pos(pos)
    {
    }

    lua_State* const state() const
    {
        return _state;
    }

    int pos() const
    {
        return _pos;
    }

    T operator*()
    {
        return lua::get<T>(_state, _pos);
    }

    T get() const
    {
        return lua::get<T>(_state, _pos);
    }

    explicit operator bool() const
    {
        return _pos >= 1 && _pos <= lua_gettop(_state);
    }

    iterator& operator=(const iterator& other)
    {
        _state = other._state;
        _pos = other._pos;
        return *this;
    }

    template <class U>
    bool operator==(const iterator<U>& other)
    {
        return _state == other._state && _pos == other._pos;
    }

    template <class U>
    bool operator!=(const iterator<U>& other)
    {
        return !(*this == other);
    }

    // Postfix (e.g. i++)
    iterator<T> operator++(int)
    {
        lua::iterator<T> rv(*this);
        ++(*this);
        return rv;
    }

    // Prefix (e.g. ++i)
    iterator<T>& operator++()
    {
        ++_pos;
        return *this;
    }

    // Postfix (e.g. i--)
    iterator<T> operator--(int)
    {
        lua::iterator<T> rv(*this);
        --(*this);
        return rv;
    }

    // Prefix (e.g. --i)
    iterator<T>& operator--()
    {
        --_pos;
        return *this;
    }
};

template <class T>
class range {
    lua_State* const _state;

public:
    range(lua_State* const state) :
        _state(state)
    {
    }

    lua_State* const state() const
    {
        return _state;
    }

    lua::iterator<T> begin()
    {
        return lua::iterator<T>(_state, 1);
    }

    lua::iterator<T> end()
    {
        return lua::iterator<T>(_state, lua_gettop(_state) + 1);
    }
};

} // namespace lua

#endif // LUA_CXX_RANGE_HEADER

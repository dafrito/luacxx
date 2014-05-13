#ifndef LUA_CXX_RANGE_HEADER
#define LUA_CXX_RANGE_HEADER

#include "push.hpp"
#include "store.hpp"

namespace lua {

template <class T>
class iterator {
    lua::state* const _state;
    int _pos;

public:
    iterator(lua::state* const state) :
        iterator(state, 1)
    {
    }

    iterator(lua::state* const state, int pos) :
        _state(state),
        _pos(pos)
    {
    }

    lua::state* const state() const
    {
        return _state;
    }

    T operator*()
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
    lua::state* const _state;

public:
    range(lua::state* const state) :
        _state(state)
    {
    }

    lua::state* const state() const
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

#ifndef luacxx_range_INCLUDED
#define luacxx_range_INCLUDED

#include "stack.hpp"

// `lua::range<T>` and `lua::iterator<T>` provide typed iteration across the
// current Lua stack. See docs/guide/iterating-stack-values.md for examples.

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

    lua_State* state() const
    {
        return _state;
    }

    int pos() const
    {
        return _pos;
    }

    T operator*()
    {
        return lua::Get<T>::get(_state, _pos);
    }

    T get() const
    {
        return lua::Get<T>::get(_state, _pos);
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

    lua_State* state() const
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

#endif // luacxx_range_INCLUDED

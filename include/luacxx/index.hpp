#ifndef luacxx_index_INCLUDED
#define luacxx_index_INCLUDED

#include "stack.hpp"
#include "link.hpp"

// `lua::index` is a lightweight wrapper around a Lua stack slot. For
// usage patterns and stack-lifetime notes, see
// docs/guide/working-with-index.md.

namespace lua {

class index
{
    lua_State* _state;
    int _pos;

public:
    index(lua_State* const state, const int pos) :
        _state(state),
        _pos(lua_absindex(state, pos))
    {
    }

    index(const lua::index& other) :
        _state(other._state),
        _pos(other._pos)
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

    void set(const int pos)
    {
        _pos = pos;
    }

    void set(const index& other)
    {
        _pos = other.pos();
    }

    lua::type_info type() const
    {
        return lua::type_info(
            static_cast<lua::type>(lua_type(state(), pos()))
        );
    }

    explicit operator bool() const
    {
        return _pos >= 1 && _pos <= lua_gettop(_state);
    }

    template <class T>
    const index& operator=(const T& source) const;

    template <class T>
    T get() const;

    template <class T>
    lua::link<lua::index, T> operator[](T name) const
    {
        return lua::link<lua::index, T>(*this, name);
    }

    // Postfix (e.g. i++)
    lua::index operator++(int)
    {
        lua::index rv(*this);
        ++(*this);
        return rv;
    }

    // Prefix (e.g. ++i)
    lua::index& operator++()
    {
        ++_pos;
        return *this;
    }

    // Postfix (e.g. i--)
    lua::index operator--(int)
    {
        lua::index rv(*this);
        --(*this);
        return rv;
    }

    // Prefix (e.g. --i)
    lua::index& operator--()
    {
        --_pos;
        return *this;
    }

    template <class Destination>
    lua::index& operator>>(Destination& destination)
    {
        lua::Store<Destination>::store(destination, state(), pos());
        return ++(*this);
    }
};

// `lua::push(...)` returns a `lua::index` pointing at the topmost pushed
// value. See docs/guide/working-with-index.md for examples and guidance on
// when `index.get<T>()` is appropriate.

template <class T>
lua::index push(lua_State* const state, T value)
{
    // Forward to the struct
    lua::Push<T>::push(state, value);
    return lua::index(state, -1);
}

// Allows noop invocations from variadic templates
lua::index push(lua_State* const state);

template <class T, class... Rest>
lua::index push(lua_State* const state, T value, Rest... values)
{
    // Forward everything to the struct
    lua::Push<T>::push(state, value);
    return push(state, values...);
}

// Push a Lua-facing object, such as `lua::index`, `lua::global`, or
// `lua::link`, onto the stack.

template <class Value>
lua::index push(Value value)
{
    // Assume the value is some sort of Lua object.
    lua::Push<Value>::push(value.state(), value);
    return lua::index(value.state(), -1);
}

template <>
struct Push<lua::index>
{
    static void push(lua_State* const state, const lua::index& source)
    {
        // Push a copy of the value stored at source.pos()
        lua_pushvalue(state, source.pos());
    }
};

template <>
struct Store<const lua::index>
{
    static void store(const lua::index& destination, const lua::index& source)
    {
        lua_pushvalue(source.state(), source.pos());
        lua_replace(destination.state(), destination.pos());
    }
};

} // namespace lua

template <class T>
T lua::index::get() const
{
    T rv = lua::Get<T>::get(state(), pos());
    lua_pop(state(), 1);
    return rv;
};

template <class T>
const lua::index& lua::index::operator=(const T& source) const
{
    lua::Push<T>::push(state(), source);
    lua_replace(state(), pos());
    return *this;
}

#endif // luacxx_index_INCLUDED

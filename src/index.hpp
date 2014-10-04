#ifndef luacxx_index_INCLUDED
#define luacxx_index_INCLUDED

#include "stack.hpp"
#include "link.hpp"

/*

=head2 class lua::index

A reference to a stack position.

    #include <stack.hpp>

    // Concatenate all strings together
    int strict_concat(lua_State* const state)
    {
        std::stringstream full_string;
        lua::index value(state, 1);

        while (value) {
            if (value.type() != lua::type::string) {
                std::stringstream str;
                str << "Argument at index "<< value.pos();
                str << " must be a string, but a ";
                str << value.type().name() << " was given.";

                throw lua::error(str.str());
            }

            // Add this value to the working total
            full_string << lua_tostring(value.state(), value.pos());

            // Go to the next value
            ++value;
        }

        // Clear the stack and push the final string
        lua_settop(state, 0);
        lua_pushstring(state, full_string.str().c_str());
        return 1;
    }

lua::index is a simple class, designed to give a more object-oriented
approach to working with stack values. This is especially useful if
you're iterating over the stack or were given a stack value from an
external source.  The stack value's position is absolute, so external
changes will not cause the index's value to move. This inflexibilty
allows the index to optimize for speed.

=head4 lua_State* index.state(), int index.pos()

Return the underlying data for this index.

    lua_replace(index.state(), index.pos());

=head4 lua::type index.type();

Returns the type of the value at this index. Refer to lua::type for
more information.

    switch (index.type().get()) {
        case lua::type::nil:
            // Handle nil
            break;
        case lua::type::number:
        case lua::type::boolean:
        case lua::type::string:
            // Handle primitives
            break;
        case lua::type::function:
            // Handle functions
            break;
        default:
            // Handle tables, userdata, and special types
            break;
    }

=head4 operator bool(), operator++(), operator--(), ...

The index behaves as a smart pointer. operator bool() will return false
if the index is out of range of the underlying state. The index is always
positive, so increment and decrement work as expected.

    #include <luacxx/convert/numeric.hpp>

    int sum = 0;
    while (index) {
        sum += index.get<int>();
        ++index;
    }

=head4 operator=(const T& source);

Replace the value at this index's position with the given value, similar
to lua_replace.

    #include <luacxx/convert/numeric.hpp>

    lua_pushnil(state);
    lua::index index(state, -1);
    assert(0 == index.get<int>());

    // ... get other_index ...
    other_index = 42;
    index = other_index;
    assert(42 == index.get<int>());

=head4 operator[](T name);

    #include <luacxx/convert/numeric.hpp>

    auto id = index["id"];
    assert(2 == id.get<int>());

Creates a link using this index as a source, and the given value as the
name. This does not modify the stack.

=head4 T index.get<T>()

Returns the stack value as the specified type. This method uses
lua::get<T> internally, so refer to that method for more information.

*/

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

    lua_State* const state() const
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

/*

=head2 lua::index push(state, T value, Rest... values)

    #include <luacxx/convert/string.hpp>
    #include <luacxx/convert/numeric.hpp>

    auto table = lua::push(state, lua::value::table);
    table["Foo"] = 42;
    table["Bar"] = 24;
    assert(42 == table["Foo"].get<int>());

Pushes the specified values onto the stack, and returns an index referring to
the topmost value. Internally, lua::push just calls the Push struct, like so:

    lua::Push<T>::push(state, value);

Specialize the lua::Push struct if you wish for your type to be handled
specially. For instance, the struct for lua::index looks like this:

    template <>
    struct Push<lua::index>
    {
        static void push(lua_State* const state, const lua::index& source)
        {
            // Push a copy of the value stored at source.pos()
            lua_pushvalue(state, source.pos());
        }
    };

*/

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

/*

=head2 lua::index push(T value)

Push a Lua object, like a lua::index, lua::global, or lua::link, onto the stack. This
is defined as:

    return lua::push(value.state(), value);

*/

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

#ifndef luacxx_link_INCLUDED
#define luacxx_link_INCLUDED

#include "stack.hpp"

/*

=head2 class lua::link<Source, Name>

Plumbing for representing symbolic paths to Lua values.

    // Get a symbolic link to package.searchers
    auto searchers = lua::make_link(lua::global(state, "package"), "searchers");
    assert(searchers.type().table());

    // lua::thread provides access (though lua::global is actually used here)
    lua::thread env;
    assert(env["package"]["searchers"].type().table());

lua::link is useful solely for its operator[] overloading, which allows
arbitrary nesting of Lua accesses to retrieve a value. Such nesting occurs
very naturally when calling Lua, so it's very convenient to have an object
that represents such addresses. You can use lua::make_link to quickly create a
link; this function allows the compiler to deduce template parameters.

lua::link's public API mimics that of lua::index, so refer to the
documentation for that class for more information.

*/

namespace lua {

template <class Source, class Name>
class link
{
    lua_State* _state;
    Source _source;
    Name _name;

public:
    link(const Source& source, const Name& name) :
        _state(source.state()),
        _source(source),
        _name(name)
    {
    }

    link(const lua::link<Source, Name>& value) :
        _state(value.state()),
        _source(value.source()),
        _name(value.name())
    {
    }

    lua::type_info type() const;

    lua_State* state() const
    {
        return _state;
    }

    const Source& source() const
    {
        return _source;
    }

    const Name& name() const
    {
        return _name;
    }

    template <class T>
    lua::link<lua::link<Source, Name>, T> operator[](T name) const
    {
        return lua::link<lua::link<Source, Name>, T>(*this, name);
    }

    template <class T>
    const link& operator=(T value) const;

    const link& operator=(const link& value) const;

    template <class T>
    void operator>>(T& destination);

    template <class Destination>
    auto get() -> decltype(lua::Get<Destination>::get(state(), -1));

    template <class T>
    operator T() const
    {
        return get<T>();
    }
};

template <class Source, class Name>
struct Push<lua::link<Source, Name>>
{
    static void push(lua_State* const state, const lua::link<Source, Name>& source)
    {
        lua::Push<Source>::push(state, source.source());
        lua::Push<Name>::push(state, source.name());
        lua_gettable(state, -2);
        lua_replace(state, -2);
    }
};

template <class Source, class Name>
struct Push<const lua::link<Source, Name>>
{
    static void push(lua_State* const state, const lua::link<Source, Name>& source)
    {
        lua::Push<Source>::push(state, source.source());
        lua::Push<Name>::push(state, source.name());
        lua_gettable(state, -2);
        lua_replace(state, -2);
    }
};

template <class Destination, class Name>
struct Store<lua::link<Destination, Name>>
{
    static void store(lua::link<Destination, Name>& destination, lua_State* const state, const int source)
    {
        lua::Push<Destination>::push(state, destination.source());
        lua::Push<Name>::push(state, destination.name());
        lua_pushvalue(state, source);
        lua_settable(state, -3);
        lua_pop(state, 1);
    }
};

template <class Source, class Name>
lua::link<Source, Name> make_link(const Source& source, const Name& name)
{
    return lua::link<Source, Name>(source, name);
}

} // namespace lua

template <class Source, class Name>
template <class Destination>
const lua::link<Source, Name>& lua::link<Source, Name>::operator=(Destination value) const
{
    lua::Push<Source>::push(state(), _source);
    lua::Push<Name>::push(state(), _name);
    lua::Push<Destination>::push(state(), value);
    lua_settable(state(), -3);
    lua_pop(state(), 1);

    return *this;
}

template <class Source, class Name>
const lua::link<Source, Name>& lua::link<Source, Name>::operator=(const lua::link<Source, Name>& value) const
{
    lua::Push<Source>::push(state(), _source);
    lua::Push<Name>::push(state(), _name);
    lua::Push<lua::link<Source, Name>>::push(state(), value);
    lua_settable(state(), -3);
    lua_pop(state(), 1);

    return *this;
}

template <class Source, class Name>
lua::type_info lua::link<Source, Name>::type() const
{
    lua::Push<const lua::link<Source, Name>>::push(state(), *this);
    lua::type_info rv(lua_type(state(), -1));
    lua_pop(state(), 1);
    return rv;
}

template <class Source, class Name>
template <class Destination>
void lua::link<Source, Name>::operator>>(Destination& destination)
{
    lua::Store<Destination>::store(destination, *this);
}

template <class Source, class Name>
template <class Destination>
auto lua::link<Source, Name>::get() -> decltype(lua::Get<Destination>::get(state(), -1))
{
    lua::Push<const lua::link<Source, Name>>::push(state(), *this);
    auto&& dest = lua::Get<Destination>::get(state(), -1);
    lua_pop(state(), 1);
    return dest;
};

#endif // luacxx_link_INCLUDED

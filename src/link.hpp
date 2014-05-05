#ifndef LUA_CXX_LINK_HEADER
#define LUA_CXX_LINK_HEADER

#include "stack.hpp"

namespace lua {

template <class Source, class Name>
class link
{
    lua::state* const _state;
    Source _source;
    Name _name;

public:
    link(const Source& source, const Name& name) :
        _state(source.state()),
        _source(source),
        _name(name)
    {
    }

    template <class T>
    link& operator=(T source)
    {
        lua::push(state(), _source);
        lua::push(state(), _name);
        lua::push(state(), source);
        lua_settable(state(), -3);
        lua_pop(state(), 1);

        return *this;
    }

    template <class T>
    lua::link<lua::link<Source, Name>, T> operator[](T&& name) const
    {
        return lua::link<lua::link<Source, Name>, T>(*this, name);
    }

    lua::type type() const
    {
        auto rv = lua::push(state(), *this).type();
        lua_pop(state(), 1);
        return rv;
    }

    lua::state* const state() const
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
};

template <class Source, class Name>
lua::link<Source, Name> make_link(const Source& source, const Name& name)
{
    return lua::link<Source, Name>(source, name);
}

template <class Source, class Name>
struct Push<lua::link<Source, Name>>
{
    static void push(lua::state* const state, lua::link<Source, Name>& source)
    {
        lua::push(state, source.source());
        lua::push(state, source.name());
        lua_gettable(state, -2);
        lua_replace(state, -2);
    }
};

template <class Source, class Name>
struct Store<lua::link<Source, Name>>
{
    static void store(lua::link<Source, Name>& destination, lua::index& source)
    {
        auto state = source.state();
        lua::push(state, destination.source());
        lua::push(state, destination.name());
        lua::push(state, source);
        lua_settable(state, -3);
        lua_pop(state, 1);
    }
};

template <class T, class Source, class Name>
typename std::remove_const<typename std::remove_reference<T>::type>::type
get(const lua::link<Source, Name>& source)
{
    typename std::remove_const<typename std::remove_reference<T>::type>::type destination;
    auto link_value = lua::push(source);
    lua::store(destination, link_value);
    return destination;
}

} // namespace lua

#endif // LUA_CXX_LINK_HEADER

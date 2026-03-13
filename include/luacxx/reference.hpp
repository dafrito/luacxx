#ifndef LUACXX_REFERENCE_INCLUDED
#define LUACXX_REFERENCE_INCLUDED

#include "stack.hpp"
#include "link.hpp"
#include "index.hpp"
#include "algorithm.hpp"

// `lua::reference` is a registry-backed handle for keeping a Lua value alive
// across C++ calls. For usage patterns and lifetime notes, see
// docs/guide/working-with-reference.md.

namespace {
    void* NIL_REFERENCE = reinterpret_cast<void*>(0xdeaddead);
}

namespace lua {

class thread;

class reference
{

lua_State* _state;
int _id;

public:

reference() :
    _state(nullptr),
    _id(LUA_NOREF)
{
}

reference(lua_State* state) :
    _state(state),
    _id(LUA_NOREF)
{
}

reference(lua::thread& env);

reference(const lua::reference& other) :
    _state(other.state()),
    _id(LUA_NOREF)
{
    if (other) {
        lua_rawgeti(state(), LUA_REGISTRYINDEX, other.id());
        _id = luaL_ref(state(), LUA_REGISTRYINDEX);
    }
}

template <class Value>
reference(Value value) :
    _state(value.state()),
    _id(LUA_NOREF)
{
    *this = value;
}

template <class Value>
reference(lua_State* const state, Value value) :
    _state(state),
    _id(LUA_NOREF)
{
    *this = value;
}

reference(lua_State* const state, const int pos) :
    _state(state),
    _id(LUA_NOREF)
{
    *this = lua::index(state, pos);
}

lua_State* state() const
{
    return _state;
}

void set_state(lua_State* const state)
{
    _state = state;
}

int id() const
{
    return _id;
}

explicit operator bool() const
{
    return _state && _id != LUA_NOREF && _id != LUA_REFNIL;
}

lua::type_info type() const
{
    if (*this) {
        lua_rawgeti(state(), LUA_REGISTRYINDEX, _id);
        auto type = lua::index(state(), -1).type();
        lua_pop(state(), 1);
        return type;
    }

    return lua::type_info(lua::type::nil);
}

void acquire()
{
    if (!state()) {
        return;
    }
    if (!*this) {
        lua_pushlightuserdata(state(), NIL_REFERENCE);
        _id = luaL_ref(state(), LUA_REGISTRYINDEX);
    }
}

void release()
{
    if (!state()) {
        return;
    }
    if (*this) {
        luaL_unref(state(), LUA_REGISTRYINDEX, _id);
        _id = LUA_NOREF;
    }
}

template <class Type>
auto get() const -> decltype(lua::Get<Type>::get(state(), -1));

template <class Source>
reference& operator=(Source source);

template <class Name>
lua::link<lua::reference, Name> operator[](Name name)
{
    return lua::link<lua::reference, Name>(*this, name);
}

template <class T>
operator T() const
{
  return get<T>();
}

~reference()
{
    release();
}

};

template <>
struct Push<lua::reference>
{
    static void push(lua_State* const state, const lua::reference& source)
    {
        if (!source) {
            lua_pushnil(state);
            return;
        }
        lua_rawgeti(state, LUA_REGISTRYINDEX, source.id());
    }
};

template <>
struct Store<lua::reference>
{
    static void store(lua::reference& destination, lua_State* const state, const int source)
    {
        if (lua_type(state, source) == LUA_TNIL) {
            destination.release();
            return;
        }
        destination.set_state(state);
        destination.acquire();
        lua_pushvalue(state, source);
        lua_rawseti(state, LUA_REGISTRYINDEX, destination.id());
    }
};

template <class Type>
auto lua::reference::get() const -> decltype(lua::Get<Type>::get(state(), -1))
{
    lua::Push<lua::reference>::push(state(), *this);
    auto rv = lua::Get<Type>::get(state(), -1);
    lua_pop(state(), 1);
    return rv;
}

template <class Source>
reference& lua::reference::operator=(Source source)
{
    if (!state()) {
        throw lua::error("lua::reference: This reference does not have a Lua state");
    }
    lua::Push<Source>::push(state(), source);
    lua::Store<lua::reference>::store(*this, state(), -1);
    lua_pop(state(), 1);
    return *this;
}

} // namespace lua

LUA_METATABLE_NAMED(lua::reference);

#endif // LUACXX_REFERENCE_INCLUDED

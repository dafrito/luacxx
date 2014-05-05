#ifndef LUA_CXX_REFERENCE_HEADER
#define LUA_CXX_REFERENCE_HEADER

#include "exception.hpp"
#include "algorithm.hpp"
#include "type/standard.hpp"

namespace {
    void* NIL_REFERENCE = reinterpret_cast<void*>(0xdeaddead);
}

namespace lua {

class reference
{
    lua::state* const _state;
    int _id;

public:
    reference(const lua::index& value) :
        _state(value.state())
    {
        if (state() == nullptr) {
            throw lua::exception("Reference state must not be null");
        }
        if (value.type().nil()) {
            lua::push(value.state(), NIL_REFERENCE);
            _id = luaL_ref(state(), LUA_REGISTRYINDEX);

            lua::push(state(), lua::value::nil);
            lua_rawseti(value.state(), LUA_REGISTRYINDEX, _id);
        } else {
            lua::push(value.state(), value);
            _id = luaL_ref(state(), LUA_REGISTRYINDEX);
        }
    }

    lua::state* const state() const
    {
        return _state;
    }

    const int id() const
    {
        return _id;
    }

    template <class T>
    reference& operator=(T source)
    {
        lua::store(*this, source);
        return *this;
    }

    ~reference()
    {
        luaL_unref(state(), LUA_REGISTRYINDEX, _id);
    }
};

template <>
struct Push<lua::reference>
{
    static void push(lua::state* const state, const lua::reference& source)
    {
        lua_rawgeti(state, LUA_REGISTRYINDEX, source.id());
    }
};

template <>
struct Store<lua::reference>
{
    static void store(lua::reference& destination, const lua::index& source)
    {
        lua_pushvalue(source.state(), source.pos());
        lua_rawseti(source.state(), LUA_REGISTRYINDEX, destination.id());
    }
};

} // namespace lua

#endif // LUA_CXX_REFERENCE_HEADER

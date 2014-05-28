#ifndef LUA_CXX_REFERENCE_HEADER
#define LUA_CXX_REFERENCE_HEADER

#include "stack.hpp"

/*

=head1 NAME

lua::reference - a slot for C to save Lua values

=head1 SYNOPSIS

    #include <luacxx/reference.hpp>

    struct MyData {
        lua::reference target;
    };

    int MyData_new(lua::state* const state)
    {
        MyData* data = lua::make<MyData>(state);
        data->target = lua::index(state, 2);

        // Move the data to the first position and return
        lua_replace(state, 1);
        return 1;
    }

    int luaopen_MyData(lua::state* const state)
    {
        lua::thread env(state);

        env["MyData"] = lua::value::table;
        env["MyData"]["new"] = MyData_new;

        return 0;
    }

=head1 DESCRIPTION

*/

namespace {
    void* NIL_REFERENCE = reinterpret_cast<void*>(0xdeaddead);
}

namespace lua {

class reference
{

lua::state* const _state;
int _id;

public:

/*

=head4 lua::reference(state)

*/

reference(lua::state* const $state) :
    _state($state)
{
    // No initial value, so fake it with nil
    lua_pushlightuserdata(state(), NIL_REFERENCE);
    _id = luaL_ref(state(), LUA_REGISTRYINDEX);

    lua_pushnil(state());
    lua_rawseti(state(), LUA_REGISTRYINDEX, _id);
}

/*

=head4 lua::reference(lua::index)

*/

reference(const lua::index& value) :
    _state(value.state())
{
    if (value.type().nil()) {
        // No initial value, so fake it with nil
        lua_pushlightuserdata(state(), NIL_REFERENCE);
        _id = luaL_ref(state(), LUA_REGISTRYINDEX);

        lua_pushnil(state());
        lua_rawseti(value.state(), LUA_REGISTRYINDEX, _id);
    } else {
        // The index refers to a non-nil value, so create a reference directly
        lua_pushvalue(state(), value.pos());
        _id = luaL_ref(state(), LUA_REGISTRYINDEX);
    }
}

/*

=head4 lua::reference(lua::state, int pos)

*/

reference(lua::state* const state, int pos) :
    reference(lua::index(state, pos))
{
}

lua::state* const state() const
{
    return _state;
}

const int id() const
{
    return _id;
}

/*

=head4 operator=(T source)

*/

template <class T>
reference& operator=(T source)
{
    lua::store(*this, source);
    return *this;
}

/*

=head4 ~reference()

Unreference this value.

*/

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

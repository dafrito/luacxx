#ifndef LUA_CXX_REFERENCE_HEADER
#define LUA_CXX_REFERENCE_HEADER

#include "stack.hpp"
#include "algorithm.hpp"

/*

=head1 NAME

lua::reference - a slot for C to save Lua values

=head1 SYNOPSIS

    #include <luacxx/reference.hpp>

    struct MyData {
        lua::reference target;
    };

    int MyData_new(lua_State* const state)
    {
        MyData* data = lua::make<MyData>(state);
        data->target = lua::index(state, 2);

        // Move the data to the first position and return
        lua_replace(state, 1);
        return 1;
    }

    int MyData_call(lua_State* const state)
    {
        auto data = lua::get<MyData*>(state, 1);
        lua::call(data->target, lua::get<const char*>(state, 2));
        return 0;
    }

    int luaopen_MyData(lua_State* const state)
    {
        lua::thread env(state);

        env["MyData"] = lua::value::table;
        env["MyData"]["new"] = MyData_new;
        env["MyData"]["call"] = MyData_call;

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

lua_State* const _state;
int _id;

public:

/*

=head4 lua::reference(state)

*/

reference(lua_State* const $state) :
    _state($state),
    _id(LUA_NOREF)
{
}

reference(const lua::reference& other)=delete;
reference(lua::reference& other) :
    _state(other.state()),
    _id(LUA_NOREF)
{
    if (other) {
        lua_rawgeti(state(), LUA_REGISTRYINDEX, other.id());
        _id = luaL_ref(state(), LUA_REGISTRYINDEX);
    }
}

lua_State* const state() const
{
    return _state;
}

const int id() const
{
    return _id;
}

explicit operator bool() const
{
    return _id != LUA_NOREF && _id != LUA_REFNIL;
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
    if (!*this) {
        lua_pushlightuserdata(state(), NIL_REFERENCE);
        _id = luaL_ref(state(), LUA_REGISTRYINDEX);
    }
}

void release()
{
    if (*this) {
        luaL_unref(state(), LUA_REGISTRYINDEX, _id);
        _id = LUA_NOREF;
    }
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
    static void store(lua::reference& destination, const lua::index& source)
    {
        if (source.type().nil()) {
            destination.release();
            return;
        }
        destination.acquire();
        lua_pushvalue(source.state(), source.pos());
        lua_rawseti(source.state(), LUA_REGISTRYINDEX, destination.id());
    }
};

} // namespace lua

#endif // LUA_CXX_REFERENCE_HEADER

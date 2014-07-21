#ifndef LUACXX_CONVERT_BUILTIN_INCLUDED
#define LUACXX_CONVERT_BUILTIN_INCLUDED

#include "../stack.hpp"

/*

=head1 NAME

convert/builtin.hpp - support for fundamental types

=head1 SYNOPSIS

    #include <luacxx/convert/builtin.hpp>

=head1 DESCRIPTION

This header provides support for all of the core
Lua types, like lua::index, lua::value::*, as well
as the Lua primitive types, like lua_Number and
const char*.

=head4 lua_pushnil(state), lua::value::nil

Pushes a nil value onto the stack.

    #include <luacxx/convert/builtin.hpp>

    lua::push(state, lua::value::nil);
    lua_pushnil(state);

=head4 lua_pushvalue(state, int source), lua::push<lua::index>

Pushes a copy of the stack value at the given source index onto the stack.

    #include <luacxx/convert/builtin.hpp>

    lua::push(state, lua::index(state, 1));
    lua_pushvalue(state, 1);

=head4 lua_pushboolean(state, value), lua::push<bool>

Pushes a boolean value onto the stack.

    #include <luacxx/convert/numeric.hpp>

    lua::push(state, false);
    lua_pushboolean(state, 0);

=head4 lua_newtable(state), lua::value::table

Pushes a new empty table onto the stack.

    #include <luacxx/convert/builtin.hpp>

    lua_newtable(state);
    lua::push(state, lua::value::table);

=head4 lua_pushglobaltable(state), lua::value::globals

Pushes the global environment table onto the stack.

    #include <luacxx/convert/build.hpp>

    lua_pushglobaltable(state);
    lua::push(state, lua::value::globals);

=head4 lua_pushvalue(state, LUA_REGISTRYINDEX), lua::value::registry

Pushes the registry onto the stack.

    #include <luacxx/convert/builtin.hpp>

    lua_pushvalue(state, LUA_REGISTRYINDEX);
    lua::push(state, lua::value::registry);

=head4 lua_pushstring(state, const char*), lua::push<const char*>

    #include <luacxx/convert/string.hpp>

    lua_pushstring(state, "No time");
    lua::push(state, "No time");

*/

namespace lua {

enum class value {
    nil = LUA_TNIL,
    table = LUA_TTABLE,
    globals = LUA_RIDX_MAINTHREAD,
    thread = LUA_TTHREAD,
    registry = LUA_REGISTRYINDEX
};

template <>
struct Push<lua::value>
{
    static void push(lua_State* const state, const lua::value& value)
    {
        switch (value) {
            case lua::value::table:
                lua_newtable(state);
                break;
            case lua::value::globals:
                lua_pushglobaltable(state);
                break;
            case lua::value::nil:
                lua_pushnil(state);
                break;
            case lua::value::thread:
                lua_newthread(state);
                break;
            case lua::value::registry:
                lua_pushvalue(state, LUA_REGISTRYINDEX);
                break;
        }
    }
};

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

template <class Source, class Name>
struct Push<lua::link<Source, Name>>
{
    static void push(lua_State* const state, lua::link<Source, Name>& source)
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

template <>
struct Store<lua::userdata_block*>
{
    static void store(lua::userdata_block*& destination, const lua::index& source)
    {
        char* block = static_cast<char*>(lua_touserdata(source.state(), source.pos()));
        if (!block) {
            destination = nullptr;
            return;
        }

        destination = reinterpret_cast<lua::userdata_block*>(
            block + lua_rawlen(source.state(), source.pos()) - sizeof(lua::userdata_block)
        );
    }
};

} // namespace lua

#endif // LUACXX_TYPE_BUILTIN_INCLUDED

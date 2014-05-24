#ifndef LUA_CXX_TYPE_STANDARD_HEADER
#define LUA_CXX_TYPE_STANDARD_HEADER

#include "../stack.hpp"

#include <string>
#include <sstream>
#include <memory>

/*

=head1 NAME

type/standard.hpp - support for fundamental types

=head1 SYNOPSIS

    #include <luacxx/type/standard.hpp>

=head1 DESCRIPTION

This header provides support for all of the core
Lua types, like lua::index, lua::value::*, as well
as the Lua primitive types, like lua_Number and
const char*.

=head4 lua_pushnil(state), lua::value::nil

Pushes a nil value onto the stack.

    #include <luacxx/type/standard.hpp>

    lua::push(state, lua::value::nil);
    lua_pushnil(state);

=head4 lua_pushvalue(state, int source), lua::push<lua::index>

Pushes a copy of the stack value at the given source index onto the stack.

    #include <luacxx/type/standard.hpp>

    lua::push(state, lua::index(state, 1));
    lua_pushvalue(state, 1);

=head4 lua_pushboolean(state, value), lua::push<bool>

Pushes a boolean value onto the stack.

    #include <luacxx/type/standard.hpp>

    lua::push(state, false);
    lua_pushboolean(state, 0);

=head4 lua_newtable(state), lua::value::table

Pushes a new empty table onto the stack.

    #include <luacxx/type/standard.hpp>

    lua_newtable(state);
    lua::push(state, lua::value::table);

=head4 lua_pushglobaltable(state), lua::value::globals

Pushes the global environment table onto the stack.

    #include <luacxx/type/standard.hpp>

    lua_pushglobaltable(state);
    lua::push(state, lua::value::globals);

=head4 lua_pushvalue(state, LUA_REGISTRYINDEX), lua::value::registry

Pushes the registry onto the stack.

    #include <luacxx/type/standard.hpp>

    lua_pushvalue(state, LUA_REGISTRYINDEX);
    lua::push(state, lua::value::registry);

=head4 lua_pushstring(state, const char*), lua::push<const char*>

    #include <luacxx/type/standard.hpp>

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
    static void push(lua::state* const state, const lua::value& value)
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
    static void push(lua::state* const state, const lua::index& source)
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

template <>
struct Push<lua_Number>
{
    static void push(lua::state* const state, const lua_Number& value)
    {
        lua_pushnumber(state, value);
    }
};

template <>
struct Store<lua_Number>
{
    static void store(lua_Number& destination, const lua::index& source)
    {
        destination = lua_tonumber(source.state(), source.pos());
    }
};

template <>
struct Push<lua_Integer>
{
    static void push(lua::state* const state, const lua_Integer& source)
    {
        lua_pushinteger(state, source);
    }
};

template <>
struct Store<lua_Integer>
{
    static void store(lua_Integer& destination, const lua::index& source)
    {
        int isnum;
        destination = lua_tointegerx(source.state(), source.pos(), &isnum);
        if (!isnum) {
            std::stringstream str;
            str << "lua::store<lua_Integer>: Numeric conversion failed for ";
            str << source.type().name() << " value at Lua stack index " << source.pos();
            throw lua::error(str.str());
        }
    }
};

template <>
struct Push<bool>
{
    static void push(lua::state* const state, const bool& source)
    {
        lua_pushboolean(state, source);
    }
};

template <>
struct Store<bool>
{
    static void store(bool& destination, const lua::index& source)
    {
        destination = lua_toboolean(source.state(), source.pos());
    }
};

template <>
struct Push<char*>
{
    static void push(lua::state* const state, const char* const source)
    {
        lua::push(state, source);
    }
};

template <>
struct Push<const char*>
{
    static void push(lua::state* const state, const char* const source)
    {
        lua_pushstring(state, source);
    }
};

template <>
struct Store<const char*>
{
    static void store(const char*& destination, const lua::index& source)
    {
        if (source.type().string()) {
            destination = lua_tostring(source.state(), source.pos());
        } else if (source.type().number()) {
            lua_pushvalue(source.state(), source.pos());
            destination = lua_tolstring(source.state(), -1, nullptr);
            lua_pop(source.state(), 1);
        }
        if (!destination) {
            destination = "";
        }
    }
};

template <>
struct Push<std::string>
{
    static void push(lua::state* const state, std::string& source)
    {
        lua::push(state, source.c_str());
    }
};

template <>
struct Store<std::string>
{
    static void store(std::string& destination, const lua::index& source)
    {
        destination = lua::get<const char*>(source);
    }
};

template <>
struct Get<const std::string&>
{
    static std::string get(const lua::index& source)
    {
        return lua::Get<std::string>::get(source);
    }
};

template <>
struct Push<void*>
{
    static void push(lua::state* const state, void* const source)
    {
        lua_pushlightuserdata(state, source);
    }
};

template <>
struct Store<void*>
{
    static void store(void*& destination, const lua::index& source)
    {
        if (lua_islightuserdata(source.state(), source.pos())) {
            destination = lua_touserdata(source.state(), source.pos());
            return;
        }

        // It's a full userdata, so retrieve the underlying value
        char* block = static_cast<char*>(lua_touserdata(source.state(), source.pos()));
        if (!block) {
            destination = nullptr;
            return;
        }
        auto userdata = reinterpret_cast<lua::userdata_block*>(block);

        switch (userdata->storage) {
        case lua::userdata_storage::value:
            destination = block + sizeof(lua::userdata_block);
            break;
        case lua::userdata_storage::pointer:
            destination = *reinterpret_cast<void**>(block + sizeof(lua::userdata_block));
            break;
        case lua::userdata_storage::shared_ptr:
            throw std::logic_error("shared_ptr's cannot be safely converted to void pointers");
        }
    }
};

template <>
struct Push<char>
{
    static void push(lua::state* const state, char& source)
    {
        lua_pushlstring(state, &source, 1);
    }
};

template <>
struct Store<char>
{
    static void store(char& destination, const lua::index& source)
    {
        if (source.type().string()) {
            size_t len = 1;
            destination = *lua_tolstring(source.state(), source.pos(), &len);
        } else {
            destination = lua_tonumber(source.state(), source.pos());
        }
    }
};

template <class T>
struct Metatable<std::shared_ptr<T>>
{
    static constexpr const char* name = Metatable<T>::name;

    static bool metatable(const lua::index& mt, std::shared_ptr<T>* const source)
    {
        if (source != nullptr) {
            Metatable<T>::metatable(mt, source->get());
        } else {
            Metatable<T>::metatable(mt, nullptr);
        }
        return false;
    }
};

} // namespace lua

#endif // LUA_CXX_TYPE_STANDARD_HEADER

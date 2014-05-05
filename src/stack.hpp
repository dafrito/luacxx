#ifndef LUA_CXX_STACK_HEADER
#define LUA_CXX_STACK_HEADER

#include <new>
#include <type_traits>
#include <iostream>

#include "type.hpp"
#include "state.hpp"

namespace lua {

enum class userdata_storage {
    value,
    pointer
};

struct userdata {
    const userdata_storage storage_type;
    bool(*is_type)(void* const, const char* const);
    void(*destroy)(void* const);

public:
    userdata(bool is_pointer) :
        userdata(is_pointer ? userdata_storage::pointer : userdata_storage::value)
    {
    }

    userdata(userdata_storage storage) :
        storage_type(storage)
    {
    }
};

int __gc(lua::state* const state);

template <class T>
static void push_userdata(lua::state* const state, const T& orig)
{
    char* block = static_cast<char*>(lua_newuserdata(state, sizeof(lua::userdata) + sizeof(T)));
    auto userdata = new (block) lua::userdata(std::is_pointer<T>::value);
    auto value = new (block + sizeof(lua::userdata)) T(orig);

    userdata->is_type = [](void* const, const char* const) {
        return true;
    };

    userdata->destroy = [](void* const block) {
        auto value = static_cast<T*>(block);
        value->~T();
    };

    lua_newtable(state);
    lua_pushstring(state, "__gc");
    lua_pushcclosure(state, __gc, 0);
    lua_settable(state, -3);
    lua_setmetatable(state, -2);
}

/**
 * Pushes the specified C++ value onto the Lua stack.
 *
 * Please feel free to specialize this template in order to have your types
 * supported by Lua-cxx's algorithms.
 */
template <class T>
struct Push
{
    static void push(lua::state* const state, const T& orig)
    {
        push_userdata(state, orig);
    }
};

class index
{
    lua::state* _state;
    int _pos;

public:
    index(lua::state* const state, const int pos) :
        _state(state),
        _pos(lua_absindex(state, pos))
    {
    }

    index(const lua::index& other) :
        _state(other._state),
        _pos(other._pos)
    {
    }

    lua::state* const state() const
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

    lua::type type() const
    {
        return lua::type(lua_type(state(), pos()));
    }

    operator bool() const
    {
        return _pos >= 1 && _pos <= lua_gettop(_state);
    }

    template <class T>
    const index& operator=(T source) const
    {
        lua::Push<T>::push(state(), source);
        lua_replace(state(), pos());
        return *this;
    }

    template <class T>
    index operator[](T&& name) const
    {
        lua::Push<T>::push(state(), name);
        lua_gettable(state(), pos());
        return lua::index(state(), -1);
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
};

template <class T>
lua::index push(lua::state* const state, T value)
{
    lua::Push<T>::push(state, value);
    return lua::index(state, -1);
}

template <class T, class... Rest>
lua::index push(lua::state* const state, T value, Rest&&... values)
{
    lua::Push<T>::push(state, value);
    return push(state, values...);
}

template <typename T, typename std::enable_if<std::is_pointer<T>::value, int>::type = 0>
static void inner_store(T& destination, lua::userdata* userdata, char* data)
{
    if (userdata->storage_type == userdata_storage::pointer) {
        destination = *reinterpret_cast<T*>(data);
    } else {
        destination = reinterpret_cast<T>(data);
    }
}

template <typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
static void inner_store(T& destination, lua::userdata* userdata, char* data)
{
    if (userdata->storage_type == userdata_storage::pointer) {
        destination = **reinterpret_cast<typename std::remove_reference<T>::type**>(data);
    } else {
        destination = *reinterpret_cast<typename std::remove_reference<T>::type*>(data);
    }
}

template <typename T>
static void store_userdata(T& destination, const lua::index& source)
{
    char* block = static_cast<char*>(lua_touserdata(source.state(), source.pos()));

    /*if (!userdata->is_type(value, name)) {
        throw lua::exception("Unrecognized type name");
    }*/

    inner_store(
        destination,
        reinterpret_cast<lua::userdata*>(block),
        block + sizeof(lua::userdata)
    );
}

template <typename T>
struct Store
{
    static void store(T& destination, const lua::index& source)
    {
        store_userdata(destination, source);
    }
};

template <class T>
void store(T& destination, const lua::index& source)
{
    lua::Store<T>::store(destination, source);
}

template <class T>
typename std::remove_const<typename std::remove_reference<T>::type>::type get(const lua::index& source)
{
    typename std::remove_const<typename std::remove_reference<T>::type>::type destination;
    lua::store(destination, source);
    return destination;
}

template <>
void get<void>(const lua::index& source);

template <class T>
T get(lua::state* const state, const int pos)
{
    return lua::get<T>(lua::index(state, pos));
}

} // namespace lua

#endif // LUA_CXX_STACK_HEADER

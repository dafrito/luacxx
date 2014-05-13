#ifndef LUA_CXX_PUSH_HEADER
#define LUA_CXX_PUSH_HEADER

#include "index.hpp"

#include <type_traits>
#include <new>

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
    static void push(lua::state* const state, T value)
    {
        push_userdata(state, value);
    }
};

template <class T>
lua::index push(lua::state* const state, T value)
{
    lua::Push<T>::push(state, value);
    return lua::index(state, -1);
}

// Allows noop invocations from variadic templates
lua::index push(lua::state* const state);

template <class Value>
lua::index push(Value value)
{
    return lua::push(value.state(), value);
}

template <class T, class... Rest>
lua::index push(lua::state* const state, T value, Rest... values)
{
    lua::Push<T>::push(state, value);
    return push(state, values...);
}

} // namespace lua

#endif // LUA_CXX_PUSH_HEADER

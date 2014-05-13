#ifndef LUA_CXX_STORE_HEADER
#define LUA_CXX_STORE_HEADER

#include "index.hpp"
#include "userdata.hpp"
#include "assert.hpp"

namespace lua {

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
    lua::assert_type("store_userdata", lua::type::userdata, source);
    auto block = static_cast<char*>(lua_touserdata(source.state(), source.pos()));

    /*if (!userdata->is_type(value, name)) {
        throw lua::error("Unrecognized type name");
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

template <typename T>
struct Get
{
    static T get(const lua::index& source)
    {
        T destination;
        lua::store(destination, source);
        return destination;
    }
};

template <typename T>
struct Get<const T&>
{
    static T& get(const lua::index& source)
    {
        return lua::Get<T&>::get(source);
    }
};

template <typename T>
struct Get<T&>
{
    static T& get(const lua::index& source)
    {
        typename std::remove_reference<T>::type* destination;
        lua::store(destination, source);
        return *destination;
    }
};

template <class T>
auto get(const lua::index& source) -> decltype(lua::Get<T>::get(source))
{
    return lua::Get<T>::get(source);
}

template <>
void get<void>(const lua::index& source);

template <class T>
T get(lua::state* const state, const int pos)
{
    return lua::get<T>(lua::index(state, pos));
}

} // namespace lua

template <class T>
lua::index& operator>>(lua::index& source, T& destination)
{
    lua::store(destination, source);
    return ++source;
}

template <class T>
lua::index operator>>(const lua::index& source, T& destination)
{
    lua::store(destination, source);
    return ++lua::index(source);
}

#endif // LUA_CXX_STORE_HEADER

#ifndef LUA_CXX_STORE_HEADER
#define LUA_CXX_STORE_HEADER

#include "index.hpp"
#include "userdata.hpp"
#include "assert.hpp"

#include <memory>

namespace lua {

template <lua::userdata_storage storage, class T,
    typename std::enable_if<storage == lua::userdata_storage::value, int>::type = 0>
static void inner_store_userdata(T& destination, lua::userdata_block* userdata, void* data)
{
    switch (userdata->storage) {
    case lua::userdata_storage::value:
        destination = *static_cast<T*>(data);
        break;
    case lua::userdata_storage::pointer:
        destination = **static_cast<T**>(data);
        break;
    case lua::userdata_storage::shared_ptr:
        destination = **static_cast<std::shared_ptr<T>*>(data);
        break;
    }
}

template <lua::userdata_storage storage, class T,
    typename std::enable_if<storage == lua::userdata_storage::pointer, int>::type = 0>
static void inner_store_userdata(T*& destination, lua::userdata_block* userdata, void* data)
{
    switch (userdata->storage) {
    case lua::userdata_storage::value:
        destination = static_cast<T*>(data);
        break;
    case lua::userdata_storage::pointer:
        destination = *static_cast<T**>(data);
        break;
    case lua::userdata_storage::shared_ptr:
        destination = static_cast<std::shared_ptr<T>*>(data)->get();
        break;
    }
}

template <lua::userdata_storage storage, class T,
    typename std::enable_if<storage == lua::userdata_storage::shared_ptr, int>::type = 0>
static void inner_store_userdata(T& destination, lua::userdata_block* userdata, void* data)
{
    switch (userdata->storage) {
    case lua::userdata_storage::shared_ptr:
    {
        destination = *reinterpret_cast<T*>(data);
        break;
    }
    case lua::userdata_storage::pointer:
    case lua::userdata_storage::value:
        throw lua::error("The provided Lua userdata does not hold a shared_ptr");
    }
}

template <lua::userdata_storage storage, class T>
static void store_userdata(T& destination, const lua::index& source)
{
    lua::assert_type("store_userdata", lua::type::userdata, source);
    auto block = static_cast<char*>(lua_touserdata(source.state(), source.pos()));
    inner_store_userdata<storage>(
        destination,
        reinterpret_cast<lua::userdata_block*>(block),
        block + sizeof(lua::userdata_block)
    );
}

template <typename T>
struct Store
{
    static void store(T& destination, const lua::index& source)
    {
        store_userdata<lua::userdata_storage::value>(destination, source);
    }
};

template <typename T>
struct Store<T*>
{
    static void store(T*& destination, const lua::index& source)
    {
        store_userdata<lua::userdata_storage::pointer>(destination, source);
    }
};

template <typename T>
struct Store<std::shared_ptr<T>>
{
    static void store(std::shared_ptr<T>& destination, const lua::index& source)
    {
        store_userdata<lua::userdata_storage::shared_ptr>(destination, source);
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

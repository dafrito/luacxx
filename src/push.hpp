#ifndef LUA_CXX_PUSH_HEADER
#define LUA_CXX_PUSH_HEADER

#include "index.hpp"
#include "userdata.hpp"

#include "config.hpp"
#include <type_traits>
#include <new>
#include <memory>
#include <string>
#include <stdexcept>

class QObject;

namespace lua {

template <class T>
struct Metatable
{
    static constexpr const char* name = "";

    static bool metatable(const lua::index& table, T* value)
    {
        #ifdef HAVE_QT_CORE
        return Metatable<typename std::conditional<
            std::is_base_of<QObject, T>::value,
            QObject,
            void
        >::type>::metatable(table, value);
        #else
        return false;
        #endif
    }
};

template <>
struct Metatable<void>
{
    static constexpr const char* name = "";

    static bool metatable(const lua::index& table, void* const value)
    {
        return false;
    }
};

int __gc(lua::state* const state);

template <class Stored>
int destroy(lua::state* const state)
{
    char* block = static_cast<char*>(lua_touserdata(state, 1));
    auto value = reinterpret_cast<Stored*>(block + sizeof(lua::userdata_block));
    if (value != nullptr) {
        value->~Stored();
    }
    return 0;
}

template <class T, class Stored = T>
void push_metatable(lua::state* const state, T* const value)
{
    auto class_name = Metatable<T>::name;
    if (std::char_traits<char>::length(class_name) > 0) {
        lua_getfield(state, LUA_REGISTRYINDEX, class_name);
    } else {
        lua_pushnil(state);
    }
    lua::index mt(state, -1);
    if (mt.type() != lua::type::nil) {
        // Use the cached value if we have one
        return;
    }

    // Otherwise, clean up
    lua_pop(state, 1);
    lua_newtable(state);

    // And set up how we destroy the object
    lua_pushstring(state, "__gc");
    lua_pushcclosure(state, __gc, 0);
    lua_settable(state, mt.pos());

    lua_pushstring(state, "Destroy");
    lua_pushcfunction(state, destroy<Stored>);
    lua_settable(state, mt.pos());

    // Use the metatable as the index
    auto set_metatable_as_default_table_for = [&](const char* name) {
        lua_pushstring(state, name);
        lua_pushvalue(state, mt.pos());
        lua_settable(state, mt.pos());
    };
    set_metatable_as_default_table_for("__index");
    set_metatable_as_default_table_for("__newindex");

    // Let downstream set up their type-specific metatable.
    if (Metatable<T>::metatable(mt, value) && std::char_traits<char>::length(class_name) > 0) {
        // Cache it for the future
        lua_pushvalue(state, mt.pos());
        lua_setfield(state, LUA_REGISTRYINDEX, class_name);
    }
}

template <class Stored>
char* construct_userdata(lua::state* const state, lua::userdata_storage storage)
{
    // Get and push a chunk of memory from Lua to hold our metadata, as well as
    // the underlying value.
    char* block = static_cast<char*>(lua_newuserdata(state,
        sizeof(lua::userdata_block) + sizeof(Stored)
    ));

    // Create the metadata
    new (block) lua::userdata_block(storage);

    // Return a pointer to the data block
    return block + sizeof(lua::userdata_block);
}

template <class Value, lua::userdata_storage storage = lua::userdata_storage::value>
struct Construct
{
    static void construct(lua::state* const state, const Value& original)
    {
        // Create a Lua userdata block
        auto block = construct_userdata<Value>(state, storage);

        // Create a value in-place
        auto value = new (block) Value(original);

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value, Value>(state, value);
        lua_setmetatable(state, -2);
    }
};

template <class Value>
struct Construct<Value, lua::userdata_storage::pointer>
{
    static void construct(lua::state* const state, Value* original)
    {
        // Create a Lua userdata block
        auto block = construct_userdata<Value*>(state, lua::userdata_storage::pointer);

        // Create a value in-place
        auto value = new (block) Value*(original);

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value, Value*>(state, *value);
        lua_setmetatable(state, -2);
    }
};

template <class Value>
struct Construct<Value, lua::userdata_storage::shared_ptr>
{
    static void construct(lua::state* const state, const std::shared_ptr<Value>& original)
    {
        // Create a Lua userdata block
        auto block = construct_userdata<std::shared_ptr<Value>>(state, lua::userdata_storage::shared_ptr);

        // Create a value in-place
        auto value = new (block) std::shared_ptr<Value>(original);

        // Get the metatable for this type and set it for our userdata.
        lua::push_metatable<Value, std::shared_ptr<Value>>(state, value->get());
        lua_setmetatable(state, -2);
    }
};

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
        Construct<T>::construct(state, value);
    }
};

template <class T>
struct Push<T*>
{
    static void push(lua::state* const state, T* value)
    {
        Construct<T, lua::userdata_storage::pointer>::construct(state, value);
    }
};

template <class T>
struct Push<std::shared_ptr<T>>
{
    static void push(lua::state* const state, const std::shared_ptr<T>& value)
    {
        Construct<T, lua::userdata_storage::shared_ptr>::construct(state, value);
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

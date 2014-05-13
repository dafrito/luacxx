#ifndef LUA_CXX_ALGORITHM_HEADER
#define LUA_CXX_ALGORITHM_HEADER

#include "push.hpp"
#include "store.hpp"
#include "assert.hpp"
#include "type/standard.hpp"

#include <stdexcept>
#include <string>
#include <vector>

namespace lua {

std::string traceback(lua::state* const state, const int toplevel);
std::string dump(lua::state* const state);

lua::index invoke(const lua::index& callable);

lua::index top(lua::state* const state);

int size(lua::state* const state);
int size(const lua::index& index);

template <class T>
int size(T reference)
{
    auto rv = size(lua::push(reference.state(), reference));
    lua_pop(reference.state(), 1);
    return rv;
}

template <class T>
bool empty(T value)
{
    return lua::size(value) == 0;
}

void remove(const lua::index& target);
void clear(lua::state* const state);
void pop(lua::state* const state, const int num);

void swap(const lua::index& a, const lua::index& b);

template <class T>
void get_all(std::vector<T>& results, lua::index index)
{
    while (index) {
        results.push_back(lua::get<T>(index++));
    }
}

template <class T>
lua::index global(lua::state* const state, const T&& name)
{
    auto globals = lua::push(state, lua::value::globals);
    auto rv = globals[name];
    lua::remove(globals);
    return --rv;
}

// All this stuff involves calling Lua from C++. This means converting C++
// arguments into Lua values, handling errors during invocation, and
// converting the returned value into something useful.

template <typename RV, typename Callable, typename... Args>
RV call(Callable source, Args... args)
{
    lua::index callable(lua::push(source.state(), source));
    lua::assert_type("lua::call", lua::type::function, callable);
    lua::push(callable.state(), args...);
    return lua::get<RV>(lua::invoke(callable));
}

template <typename Callable, typename... Args>
void call(Callable source, Args... args)
{
    lua::index callable(lua::push(source.state(), source));
    lua::assert_type("lua::call", lua::type::function, callable);
    lua::push(callable.state(), args...);
    lua::invoke(callable);
}

namespace table {

int length(const lua::index& index);

template <typename Table, typename Value>
void insert(Table destination, Value value)
{
    auto table = lua::push(destination);
    lua::assert_type("lua::table::insert", lua::type::table, table);
    lua::push(table.state(), lua::table::length(table) + 1);
    lua::push(table.state(), value);

    lua_settable(table.state(), table.pos());

    lua_pop(table.state(), 1);
}

template <typename Value, typename Table, typename Key>
Value get(Table source, Key key)
{
    auto table = lua::push(source);
    lua::assert_type("lua::table::get", lua::type::table, table);

    lua::push(table.state(), key);
    lua_gettable(table.state(), table.pos());
    lua_replace(table.state(), table.pos());

    auto rv = lua::get<Value>(table.state(), -1);
    lua_pop(table.state(), 1);
    return rv;
}

template <typename Table, typename Key>
lua::index get(Table source, Key key)
{
    auto table = lua::push(source);
    lua::assert_type("lua::table::get", lua::type::table, table);

    lua::push(table.state(), key);
    lua_gettable(table.state(), table.pos());
    lua_replace(table.state(), table.pos());

    return lua::index(table.state(), -1);
}

template <typename Table, typename Key, typename Value>
void set(Table source, Key key, Value value)
{
    auto table = lua::push(source);
    lua::assert_type("lua::table::set", lua::type::table, table);

    lua::push(table.state(), key);
    lua::push(table.state(), value);
    lua_settable(table.state(), table.pos());

    lua_pop(table.state(), 1);
}

} // namespace table

} // namespace lua

#endif // LUA_CXX_ALGORITHM_HEADER

#ifndef LUA_CXX_ALGORITHM_HEADER
#define LUA_CXX_ALGORITHM_HEADER

#include "stack.hpp"
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
int length(const lua::index& index);

template <class T>
bool empty(T value)
{
    return lua::size(value) == 0;
}

void remove(const lua::index& target);
void clear(lua::state* const state);
void pop(lua::state* const state, const int num);

void swap(const lua::index& a, const lua::index& b);
lua::index copy(const lua::index& source);

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
RV call(Callable source, Args&&... args)
{
    lua::index callable(lua::push(source.state(), source));
    if (!callable.type().function()) {
        throw std::logic_error(
            std::string("A function must be at the top of the stack, not a ") + callable.type().name()
        );
    }
    lua::push(callable.state(), args...);
    return lua::get<RV>(lua::invoke(callable));
}

template <typename Callable, typename... Args>
void call(Callable source, Args&&... args)
{
    lua::index callable(lua::push(source.state(), source));
    if (!callable.type().function()) {
        throw std::logic_error(
            std::string("A function must be at the top of the stack, not a ") + callable.type().name()
        );
    }
    lua::push(callable.state(), args...);
    lua::invoke(callable);
}

namespace table {

template <typename Table, typename Value>
void insert(Table destination, Value value)
{
    lua::index table(lua::push(destination.state(), destination));
    if (!table.type().table()) {
        throw std::logic_error(
            std::string("A table must be provided")
        );
    }

    lua::push(table.state(), lua::size(table) + 1);
    lua::push(table.state(), value);
    lua_settable(table.state(), table.pos());

    lua_pop(table.state(), 1);
}

template <typename Table, typename Key>
lua::index get(Table source, Key key)
{
    lua::index table(lua::push(source.state(), source));
    if (!table.type().table()) {
        throw std::logic_error(
            std::string("A table must be provided")
        );
    }

    lua::push(table.state(), key);
    lua_gettable(table.state(), table.pos());
    lua_replace(table.state(), table.pos());

    return lua::index(table.state(), -1);
}

} // namespace table

} // namespace lua

#endif // LUA_CXX_ALGORITHM_HEADER

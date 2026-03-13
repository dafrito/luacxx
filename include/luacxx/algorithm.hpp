#ifndef luacxx_algorithm_INCLUDED
#define luacxx_algorithm_INCLUDED

#include "stack.hpp"
#include "index.hpp"
#include "value.hpp"

#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

// Higher-level helpers for stack manipulation, conversion, userdata
// construction, and Lua invocation. See docs/reference/thread-and-algorithms.md
// for extended usage notes.

namespace lua {

std::string dump(lua_State* const state);

std::string class_name(const lua::index& index);
std::string class_name(lua_State* const state, int pos);

const userdata_type* get_type_info(const lua::index& index);
const userdata_type* get_type_info(lua_State* const state, int pos);

template <class Required>
struct is_type
{
    bool _result;

    is_type(const lua::index& index)
    {
        auto info = lua::get_type_info(index);
        if (info == nullptr) {
            _result = false;
            return;
        }
        _result = info->has_cast<Required>();
    }

    is_type(lua_State* const state, const int pos) :
        is_type(lua::index(state, pos))
    {
    }

    const userdata_type& required_type() const
    {
        return lua::Metatable<Required>::info();
    }

    operator bool() const
    {
        return _result;
    }
};

std::string memory_address(const lua::index& index);

template <class Error = lua::error>
void assert_type(const char* category, const lua::type& expected, const lua::index& given)
{
    if (given.type() == expected) {
        return;
    }
    std::stringstream str;
    str << category;
    str << ": ";
    str << "Lua stack value at index " << given.pos() << " must be a ";
    str << lua::type_info(expected).name();
    str << " but a " << given.type().name() << " was given instead.";
    throw Error(str.str());
}

template <>
void assert_type<lua::error>(const char* category, const lua::type& expected, const lua::index& given);

lua::index top(lua_State* const state);

unsigned int size(lua_State* const state);

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

void clear(lua_State* const state);

void swap(const lua::index& a, const lua::index& b);

template <class T>
void store(T& destination, const lua::value& value)
{
    lua::Store<T>::store(destination, lua::push(destination.state(), value));
    lua_pop(destination.state(), 1);
}

template <class T>
void store(T& destination, const lua::index& source)
{
    // Forward to the struct (for convenience)
    lua::Store<T>::store(destination, source.state(), source.pos());
}

template <class T>
void store(T& destination, lua_State* const state, const int pos)
{
    lua::Store<T>::store(destination, state, pos);
}

template <class T, class Source>
T get(Source source)
{
    auto index = lua::push(source);
    decltype(lua::Get<T>::get(source.state(), -1)) rv = lua::Get<T>::get(index.state(), -1);
    lua_pop(index.state(), 1);
    return rv;
}

template <class T>
auto get(const lua::index& source) -> decltype(lua::Get<T>::get(source.state(), source.pos()))
{
    return lua::Get<T>::get(source.state(), source.pos());
}

template <>
void get<void>(const lua::index& source);

template <class T>
auto get(lua_State* const state, const int pos) -> decltype(lua::Get<T>::get(state, pos))
{
    return lua::Get<T>::get(state, pos);
}

template <class T, class... Args>
T* make(lua_State* const state, Args&&... args)
{
    Construct<T>::construct(state, args...);
    return lua::get<T*>(state, -1);
}

template <class T>
void get_all(std::vector<T>& results, lua::index index)
{
    while (index) {
        results.push_back(lua::get<T>(index++));
    }
}

template <class T>
void get_all(std::vector<T>& results, lua_State* const state, const int pos)
{
    return lua::get_all(results, lua::index(state, pos));
}

void invoke(const lua::index& callable);

void invoke(const int nresults, const lua::index& callable);

void invoke(lua_State* const state, const int pos);

void invoke(const int nresults, lua_State* const state, const int pos);

template <typename RV, typename Callable, typename... Args>
auto call(Callable source, Args... args) -> decltype(lua::get<RV>(source.state(), 0))
{
    lua::index callable(lua::push(source.state(), source));
    if (lua::is_type<std::function<RV(Args...)>>(callable)) {
        auto saved_function = callable.get<std::function<RV(Args...)>*>();
        lua_pop(source.state(), 1);
        return (*saved_function)(args...);
    }
    lua::push(callable.state(), args...);
    lua::invoke(1, callable);
    return lua::get<RV>(callable.state(), callable.pos());
}

template <typename RV, typename Callable>
auto call(Callable source) -> decltype(lua::get<RV>(source.state(), 0))
{
    lua::index callable(lua::push(source.state(), source));
    if (lua::is_type<std::function<RV()>>(callable)) {
        auto saved_function = callable.get<std::function<RV()>*>();
        lua_pop(source.state(), 1);
        return (*saved_function)();
    }
    lua::invoke(1, callable);
    return lua::get<RV>(callable.state(), callable.pos());
}

template <typename Callable, typename... Args>
void call(Callable source, Args... args)
{
    lua::index callable(lua::push(source.state(), source));
    lua::assert_type("lua::call", lua::type::function, callable);
    lua::push(callable.state(), args...);
    lua::invoke(0, callable);
}

template <typename Callable>
void call(Callable source)
{
    lua::index callable(lua::push(source.state(), source));
    lua::assert_type("lua::call", lua::type::function, callable);
    lua::invoke(0, callable);
}

template <int returned, typename Callable, typename... Args>
void call(Callable source, Args... args)
{
    lua::index callable(lua::push(source.state(), source));
    lua::assert_type("lua::call", lua::type::function, callable);
    lua::push(callable.state(), args...);
    lua::invoke(returned, callable);
}

template <int returned, typename Callable>
void call(Callable source)
{
    lua::index callable(lua::push(source.state(), source));
    lua::assert_type("lua::call", lua::type::function, callable);
    lua::invoke(returned, callable);
}

template <class T>
lua::index push_global(lua_State* const state, const T&& name)
{
    auto globals = lua::push(state, lua::value::globals);
    auto rv = globals[name];
    lua::remove(globals);
    return --rv;
}

/*

=head4 int lua::make_malloc<T>(state)

Creates a new userdata and pushed it on the stack. The userdata's size is
determined by the specified type.

This returns 1, so it can be used directly as a callable Lua function for
simple C types, as shown in the example:

    env["chtype"] = lua::value::table;
    env["chtype"]["new"] = lua::make_malloc<chtype>;

*/

template <class Value>
int make_malloc(lua_State* const state)
{
    Construct<Value>::construct(state);
    return 1;
}

namespace table {

/*

=head4 lua::table::length(index)

Returns the size of the table at the given index.

*/

int length(const lua::index& index);

int length(lua_State* const state, const int pos);

/*

=head4 lua::table::insert(destination, value)

Inserts a new value into the table at the given destination index.

    lua::table::insert(env["package"]["searchers"], my_search_function);

*/

template <typename Value>
void insert(lua_State* const state, const int pos, Value value)
{
    lua::push(state, lua::table::length(state, pos) + 1);
    lua::push(state, value);
    lua_settable(state, pos);
}

template <typename Table, typename Value>
void insert(Table destination, Value value)
{
    auto table = lua::push(destination);
    lua::assert_type("lua::table::insert", lua::type::table, table);
    lua::table::insert(table.state(), table.pos(), value);
    lua_pop(table.state(), 1);
}

/*

=head4 Value lua::table::get<Value>(source, key)

Returns source[key] as a value of the given type. The Lua stack
is unaffected.

=head4 lua::index lua::table::get(source, key)

Pushes source[key] onto the Lua stack.

*/

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

/*

=head4 lua::table::set(source, key, value)

Sets source[key] to the given value.

*/

template <typename Value, typename Key, typename Table>
void set(Table source, Key key, Value value)
{
    auto table = lua::push(source);
    lua::assert_type("lua::table::set", lua::type::table, table);

    lua::push(table.state(), key);
    lua::push(table.state(), value);
    lua_settable(table.state(), table.pos());

    lua_pop(table.state(), 1);
}

template <class Value, class Callable>
void each(lua_State* const state, const int pos, const Callable& callable)
{
    auto len = lua_rawlen(state, pos);
    for (lua_Unsigned i = 1; i <= len; ++i) {
        lua_rawgeti(state, pos, i);
        callable(lua::get<Value>(state, -1));
        lua_pop(state, 1);
    }
}

template <class Callable>
void each(lua_State* const state, const int pos, const Callable& callable)
{
    auto len = lua_rawlen(state, pos);
    for (lua_Unsigned i = 1; i <= len; ++i) {
        lua_rawgeti(state, pos, i);
        callable(state, -1);
        lua_pop(state, 1);
    }
}

template <class Table, class Callable>
void each(Table table, const Callable& callable)
{
    auto t = lua::push(table);
    lua::table::each(t.state(), t.pos(), callable);
}

template <class Value, class Table, class Callable>
void each(Table table, const Callable& callable)
{
    auto t = lua::push(table);
    lua::table::each<Value>(t.state(), t.pos(), callable);
}

template <class... Args>
void call_each(lua_State* const state, const int pos, Args... args)
{
    lua::table::each(state, pos, [args...](lua_State* const state, const int pos) {
        lua::call(lua::index(state, pos), args...);
    });
}

/*

=head4 lua::type_info rv = lua::table::get_type(source, key)

Returns the type of source[key], same as lua::index::type()

*/

template <typename Table, typename Key>
lua::type_info get_type(Table source, Key key)
{
    auto value = lua::table::get(source, key);
    auto rv = value.type();
    lua_pop(value.state(), 1);
    return rv;
}

} // namespace table

/*

=head4 lua::setfield(source, key, value)

Identical to lua::table::set(source, key, value)

*/

template <typename Value, typename Key, typename Table>
void setfield(Table source, Key key, Value value)
{
    lua::table::set(source, key, value);
}

/*

=head4 lua::setglobal<Value>(state, const char* name, Value value)

*/

template <typename Value>
void setglobal(lua_State* const state, const char* name, Value value)
{
    lua::push(state, value);
    lua_setglobal(state, name);
}

} // namespace lua

#endif // luacxx_algorithm_INCLUDED

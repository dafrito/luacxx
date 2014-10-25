#include "algorithm.hpp"

#include "error.hpp"
#include "convert/const_char_p.hpp"
#include "convert/string.hpp"
#include "convert/numeric.hpp"
#include "convert/callable.hpp"

#include <cassert>
#include <string>
#include <sstream>

static int on_error(lua_State* const state)
{
    if (lua::size(state) > 0) {
        if (!lua::index(state, 1).type().userdata()) {
            lua::error ex(lua::get<const char*>(state, 1));
            lua::clear(state);
            lua::push(state, ex);
        }
    } else {
        lua::push(state, lua::error("An unspecified runtime error occurred during the execution of Lua code"));
    }
    auto ex = lua::get<lua::error*>(state, 1);
    ex->set_traceback(lua::traceback(state, 2));

    return 1;
}

template <>
void lua::assert_type<lua::error>(const char* category, const lua::type& expected, const lua::index& given)
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
    throw lua::error(given.state(), str.str());
}

void lua::invoke(const lua::index& callable)
{
    auto state = callable.state();
    int nargs = lua::top(callable.state()).pos() - callable.pos();

    lua::assert_type("invoke", lua::type::function, callable);

    // Call Lua function. LUA_MULTRET ensures all arguments are returned
    // Subtract one from the size to ignore the function itself and pass
    // the correct number of arguments
    lua::push(state, on_error);
    lua_insert(state, callable.pos());

    int result = lua_pcall(state, nargs, LUA_MULTRET, callable.pos());

    // Be sure to remove the error handler
    lua_remove(state, callable.pos());

    switch (result) {
        case LUA_OK:
            return;
        case LUA_ERRGCMM:
            throw std::runtime_error("Lua garbage collector error");
        case LUA_ERRMEM:
            throw std::runtime_error("Lua memory error");
        case LUA_ERRERR:
            throw std::runtime_error("Lua error within error handler");
        case LUA_ERRRUN:
            throw lua::get<lua::error>(state, -1);
    }

    std::stringstream str;
    str << "Unexpected Lua pcall result of " << result;
    throw std::logic_error(str.str());
}

const lua::userdata_type* lua::get_type_info(const lua::index& index)
{
    return lua::get_type_info(index.state(), index.pos());
}

const lua::userdata_type* lua::get_type_info(lua_State* const state, int pos)
{
    auto userdata_block = lua::get_userdata_block(state, pos);
    if (!userdata_block) {
        return nullptr;
    }
    return userdata_block->info();
}

std::string lua::class_name(const lua::index& index)
{
    return lua::class_name(index.state(), index.pos());
}

std::string lua::class_name(lua_State* const state, int pos)
{
    auto info = lua::get_type_info(state, pos);
    if (info) {
        return info->name();
    }
    return std::string();
}

std::string memory_address(const lua::index& index)
{
    std::stringstream str;
    str << lua_topointer(index.state(), index.pos());
    return str.str();
}

lua::index lua::top(lua_State* const state)
{
    return lua::index(state, lua_gettop(state));
}

unsigned int lua::size(lua_State* const state)
{
    return static_cast<unsigned int>(lua_gettop(state));
}

int lua::size(const lua::index& index)
{
    return luaL_len(index.state(), index.pos());
}

int lua::table::length(lua_State* const state, const int pos)
{
    return lua_rawlen(state, pos);
}

int lua::table::length(const lua::index& index)
{
    return lua::table::length(index.state(), index.pos());
}

void lua::swap(const lua::index& a, const lua::index& b)
{
    auto copy = lua::push(a.state(), a);
    a = b;
    b = copy;

    lua_pop(a.state(), 1);
}

void lua::remove(const lua::index& target)
{
    lua_remove(target.state(), target.pos());
}

void lua::clear(lua_State* const state)
{
    lua_settop(state, 0);
}

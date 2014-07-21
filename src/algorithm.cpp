#include "algorithm.hpp"

#include "error.hpp"
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

std::string lua::traceback(lua_State* const state, const int toplevel)
{
    #if LUA_VERSION_NUM >= 502
        std::string rv;
        luaL_traceback(state, state, NULL, toplevel);
        rv = lua::get<std::string>(state, -1);
        lua_pop(state, 1);
        return rv;
    #else
        auto getter = lua::global(state, "debug")["traceback"];
        return getter("", topLevel).get<std::string>().substr(1);
    #endif
}

const char* lua::class_id(const lua::index& index)
{
    lua_getmetatable(index.state(), index.pos());
    lua_getfield(index.state(), -1, "__class");
    auto rv = lua_topointer(index.state(), -1);
    lua_pop(index.state(), 1);
    return static_cast<const char*>(rv);
}

const char* lua::class_id(lua_State* const state, int pos)
{
    return lua::class_id(lua::index(state, pos));
}

std::string lua::class_name(const lua::index& index)
{
    auto id = lua::class_id(index);
    if (!id) {
        return std::string();
    }

    return std::string(id);
}

std::string lua::class_name(lua_State* const state, int pos)
{
    return lua::class_name(lua::index(state, pos));
}

size_t lua::userdata_size(const lua::index& index)
{
    return lua_rawlen(index.state(), index.pos()) - sizeof(lua::userdata_block);
}

std::string lua::dump(lua_State* const state)
{
    std::stringstream str;

    str << "Lua stack (" << lua::size(state) << " ";
    if (lua::size(state) == 1) {
        str << "item";
    } else {
        str << "items";
    }

    str << "): ";

    for (lua::index iter(state, 1); iter; ++iter) {
        switch (iter.type().get()) {
        case lua::type::boolean:
            str << (lua::get<bool>(iter) ? "true" : "false");
            break;
        case lua::type::string:
        {
            auto value = lua::get<std::string>(iter);
            if (value.size() > 30) {
                str << '"' << value.substr(0, 30) << "\"...";
            } else {
                str << '"' << value << '"';
            }
            break;
        }
        case lua::type::number:
            str << lua::get<std::string>(iter);
            break;
        case lua::type::userdata:
        {
            auto name = lua::class_id(iter);
            if (name) {
                str << name << "(size=" << lua_rawlen(iter.state(), iter.pos()) << ')';
            } else {
                str << iter.type().name() << "(size=" << lua_rawlen(iter.state(), iter.pos()) << ')';
            }
            break;
        }
        case lua::type::table:
            str << iter.type().name() << "(size=" << lua_rawlen(iter.state(), iter.pos()) << ')';
            break;
        case lua::type::function:
        case lua::type::thread:
        {
            str << iter.type().name() << "@";
            str << lua_topointer(iter.state(), iter.pos());
            break;
        }
        default:
            str << iter.type().name();
        }
        if (iter.pos() != lua::top(state).pos()) {
            str << ", ";
        }
    }

    return str.str();
}

std::string memory_address(const lua::index& index)
{
    std::stringstream str;
    str << lua_topointer(index.state(), index.pos());
    return str.str();
}

lua::index lua::top(lua_State* const state)
{
    return lua::index(state, -1);
}

int lua::size(lua_State* const state)
{
    return lua_gettop(state);
}

int lua::size(const lua::index& index)
{
    return luaL_len(index.state(), index.pos());
}

int lua::table::length(const lua::index& index)
{
    return lua_rawlen(index.state(), index.pos());
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

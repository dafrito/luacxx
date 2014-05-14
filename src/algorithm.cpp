#include "algorithm.hpp"

#include "error.hpp"
#include "type/standard.hpp"
#include "type/function.hpp"

#include <cassert>
#include <string>
#include <sstream>

static int on_error(lua::state* const state)
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
            auto ex = lua::get<lua::error*>(state, -1);
            throw *ex;
    }

    std::stringstream str;
    str << "Unexpected Lua pcall result of " << result;
    throw std::runtime_error(str.str());
}

std::string lua::traceback(lua::state* const state, const int toplevel)
{
    #if LUA_VERSION_NUM >= 502
        std::string rv;
        luaL_traceback(state, state, NULL, toplevel);
        rv = lua::get<std::string>(state, -1);
        lua::pop(state, 1);
        return rv;
    #else
        auto getter = lua::global(state, "debug")["traceback"];
        return getter("", topLevel).get<std::string>().substr(1);
    #endif
}

std::string lua::dump(lua::state* const state)
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
        case lua::type::table:
            str << iter.type().name() << "(size=" << lua_rawlen(iter.state(), iter.pos()) << ')';
            break;
        default:
            str << iter.type().name();
        }
        if (iter.pos() != lua::top(state).pos()) {
            str << ", ";
        }
    }

    return str.str();
}

lua::index lua::top(lua::state* const state)
{
    return lua::index(state, -1);
}

int lua::size(lua::state* const state)
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

    lua::pop(a.state(), 1);
}

void lua::remove(const lua::index& target)
{
    lua_remove(target.state(), target.pos());
}

void lua::pop(lua::state* const state, const int num)
{
    lua_pop(state, num);
}

void lua::clear(lua::state* const state)
{
    lua_settop(state, 0);
}

#include "algorithm.hpp"

#include "exception.hpp"
#include "type/standard.hpp"
#include "type/function.hpp"

#include <cassert>
#include <string>
#include <sstream>

static int on_error(lua::state* const state)
{
    if (lua::size(state) > 0) {
        if (!lua::index(state, 1).type().userdata()) {
            lua::exception ex(lua::get<const char*>(state, 1));
            lua::clear(state);
            lua::push(state, ex);
        }
    } else {
        lua::push(state, lua::exception("An error occurred within Lua"));
    }
    auto ex = lua::get<lua::exception*>(state, 1);
    ex->set_traceback(lua::traceback(state, 2));

    return 1;
}

lua::index lua::invoke(const lua::index& callable)
{
    auto state = callable.state();
    int numArgs = lua::top(callable.state()).pos() - callable.pos();
    assert(callable.type().function());

    // Call Lua function. LUA_MULTRET ensures all arguments are returned
    // Subtract one from the size to ignore the function itself and pass
    // the correct number of arguments
    lua::push(state, on_error);
    lua_insert(state, callable.pos());

    int result = lua_pcall(state, numArgs, LUA_MULTRET, callable.pos());

    // Be sure to remove the error handler
    lua_remove(state, callable.pos());

    switch (result) {
        case LUA_OK:
            return callable;
        case LUA_ERRGCMM:
            throw std::runtime_error("Lua garbage collector error");
        case LUA_ERRMEM:
            throw std::runtime_error("Lua memory error");
        case LUA_ERRERR:
            throw std::runtime_error("Lua error within error handler");
        case LUA_ERRRUN:
            auto ex = lua::get<lua::exception*>(state, -1);
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

    str << "Stack (" << lua::size(state) << " ";
    if (lua::size(state) == 1) {
        str << "item";
    } else {
        str << "items";
    }

    str << ") [";

    for (lua::index iter(state, 1); iter; ++iter) {
        str << iter.type().name();
        std::string info;
        if (iter.type().boolean()) {
            info = lua::get<bool>(iter) ? "true" : "false";
        } else if (iter.type().string() || iter.type().number()) {
            info = lua::get<std::string>(iter);
        }
        if (info.size()) {
            str << "(";
            if (info.size() > 30) {
                info = info.substr(0, 30);
                str << info << "...";
            } else  {
                str << info;
            }
            str << ")";
        }
        if (iter.pos() != lua::top(state).pos()) {
            str << ", ";
        }
    }

    str << "]";

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

int lua::length(const lua::index& index)
{
    return size(index);
}

void lua::swap(const lua::index& a, const lua::index& b)
{
    auto copy = lua::copy(a);
    lua::store(a, b);
    lua::store(b, copy);

    lua::pop(a.state(), 1);
}

lua::index lua::copy(const lua::index& source)
{
    lua_pushvalue(source.state(), source.pos());
    return lua::index(source.state(), -1);
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

/*
bool LuaStack::hasMetatable(const int pos)
{
    bool hasMeta = lua_getmetatable(luaState(), absPos(pos)) != 0;
    if (hasMeta) {
        pop();
    }
    return hasMeta;
}

void LuaStack::pushMetatable(const int pos)
{
    assertUnlocked();
    bool hasMeta = lua_getmetatable(luaState(), absPos(pos)) != 0;
    if (!hasMeta) {
        push(lua::value::table);
        // Offset to ensure the position is set correctly
        setMetatable(pos > 0 ? pos : pos - 1);
    }
}

void LuaStack::setMetatable(const int pos)
{
    assertUnlocked();
    lua_setmetatable(luaState(), absPos(pos));
}
*/

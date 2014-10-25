#include "callable.hpp"

#include "convert/const_char_p.hpp"

#include <iostream>

int lua::invoke_callable(lua_State* const state)
{
    auto callable = lua::Get<lua::callable*>::get(state, lua_upvalueindex(1));
    try {
        return (*callable)(state);
    } catch (lua::error& ex) {
        lua::push(state, ex);
        lua_error(state);
        throw std::logic_error("lua_error must never return");
    }
}

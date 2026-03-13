#ifndef LUACXX_LOADERS_INCLUDED
#define LUACXX_LOADERS_INCLUDED

#include <string>

#include "algorithm.hpp"

namespace lua {

// Load and run Lua source from strings, files, or streams. See
// docs/guide/loading-and-running-lua-code.md for the higher-level workflow.
lua::index load_file(lua_State* const state, const std::string& filename);
lua::index load_file(lua_State* const state, const char* file);
lua::index load_file(lua_State* const state, std::istream& stream, const std::string& name);

lua::index load_string(lua_State* const state, const std::string& input);
lua::index load_string(lua_State* const state, const char* input);

template <class RV, class Input, class... Rest>
RV run_string(lua_State* const state, Input& runnable, Rest... args)
{
    lua::index rv(state, lua_gettop(state) + 1);
    lua::invoke(lua::load_string(state, runnable, args...));
    if (!rv) {
        throw lua::error("lua::run_string: The invoked callable did not return a value");
    }
    return lua::get<RV>(rv);
}

template <class Input, class... Rest>
void run_string(lua_State* const state, Input& runnable, Rest... args)
{
    lua::invoke(lua::load_string(state, runnable, args...));
}

template <class RV, class Input>
RV run_file(lua_State* const state, Input& runnable)
{
    lua::index rv(state, lua_gettop(state) + 1);
    lua::invoke(lua::load_file(state, runnable));
    if (!rv) {
        throw lua::error("lua::run_file: The invoked callable did not return a value");
    }
    return lua::get<RV>(rv);
}

template <class Input>
void run_file(lua_State* const state, Input& runnable)
{
    lua::invoke(lua::load_file(state, runnable));
}

} // namespace lua

#endif // LUACXX_LOADERS_INCLUDED

#ifndef LUACXX_LOADERS_INCLUDED
#define LUACXX_LOADERS_INCLUDED

#include <string>

#include "algorithm.hpp"

namespace lua {

/*

=head1 NAME

#include <luacxx/load.hpp> - Loads files and strings into Lua functions

=head1 DESCRIPTION

=head2 lua::index lua::load_file(state, file)

Reads and compiles the Lua code within the given file, and pushes a function
that, when executed, will run that code. The file can be either a filename, a
QFile, or a std::istream.

If compilation errors occur, a lua::error will be thrown.

*/
lua::index load_file(lua_State* const state, const std::string& filename);
lua::index load_file(lua_State* const state, const char* file);
lua::index load_file(lua_State* const state, std::istream& stream, const std::string& name);

/*

=head2 lua::index lua::load_string(state, input)

Reads and compiles the given input as literal Lua code. If successful, a
function to execute the given code will be pushed on the Lua stack.

If compilation errors occur, a lua::error will be thrown.

*/
lua::index load_string(lua_State* const state, const std::string& input);
lua::index load_string(lua_State* const state, const char* input);

/*

=head2 RV lua::run_string<RV>(state, runnable)

Loads and runs the given string, using lua::load_string to do it. The arguments
returned from the run will be on the top of the stack.

The return value can be specified to have a single argument be returned.

*/
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

/*

=head2 RV lua::run_file<RV>(state, runnable)

Loads and runs the given file, using lua::load_file to do it. The arguments
returned from the run will be on the top of the stack.

The return value can be specified to have a single argument be returned.

*/

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

#ifndef LUA_CXX_LOADERS_HEADER
#define LUA_CXX_LOADERS_HEADER

#include <string>

#include "algorithm.hpp"

class QDir;
class QFile;

namespace lua {

/*

=head2 lua::index lua::load_file(state, file)

Reads and compiles the Lua code within the given file, and pushes a function
that, when executed, will run that code. The file can be either a filename, a
QFile, or a std::istream.

If compilation errors occur, a lua::error will be thrown.

*/
lua::index load_file(lua::state* const state, QFile& file);
lua::index load_file(lua::state* const state, const std::string& file);
lua::index load_file(lua::state* const state, const char* file);
lua::index load_file(lua::state* const state, std::istream& stream, const std::string& name);

/*

=head2 lua::index lua::load_string(state, input)

Reads and compiles the given input as literal Lua code. If successful, a
function to execute the given code will be pushed on the Lua stack.

If compilation errors occur, a lua::error will be thrown.

*/
lua::index load_string(lua::state* const state, const std::string& input);
lua::index load_string(lua::state* const state, const char* input);

/*

=head2 lua::index run_dir(state, const QDir&, bool recurse)

Runs every file in the specified directory, optionally recursing into
subdirectories.

By default, QDir will include every file, so if you want to filter the files,
specify a filter list on the directory itself:

    QDir dir = QDir::current();
    dir.setFilters(QDir::Files);

    QStringList filters;
    filters << "*.lua";
    dir.setNameFilters(filters);

    lua::run_dir(state, dir, true);

*/
void run_dir(lua::state* const state, const QDir& dir, const bool recurse);

/*

=head2 RV lua::run_string<RV>(state, runnable)

Loads and runs the given string, using lua::load_string to do it. The arguments
returned from the run will be on the top of the stack.

The return value can be specified to have a single argument be returned.

*/
template <class RV, class Input, class... Rest>
RV run_string(lua::state* const state, Input& runnable, Rest... args)
{
    lua::index rv(state, lua_gettop(state) + 1);
    lua::invoke(lua::load_string(state, runnable, args...));
    if (!rv) {
        throw lua::error("lua::run_string: The invoked callable did not return a value");
    }
    return lua::get<RV>(rv);
}

template <class Input, class... Rest>
void run_string(lua::state* const state, Input& runnable, Rest... args)
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
RV run_file(lua::state* const state, Input& runnable)
{
    lua::index rv(state, lua_gettop(state) + 1);
    lua::invoke(lua::load_file(state, runnable));
    if (!rv) {
        throw lua::error("lua::run_file: The invoked callable did not return a value");
    }
    return lua::get<RV>(rv);
}

template <class Input>
void run_file(lua::state* const state, Input& runnable)
{
    lua::invoke(lua::load_file(state, runnable));
}

} // namespace lua

#endif // LUA_CXX_LOADERS_HEADER

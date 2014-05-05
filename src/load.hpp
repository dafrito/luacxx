#ifndef LUA_CXX_LOADERS_HEADER
#define LUA_CXX_LOADERS_HEADER

#include <string>
#include <QFile>

#include "algorithm.hpp"

class QDir;

namespace lua
{
    lua::index load_file(lua::state* const state, QFile& file);
    lua::index load_file(lua::state* const state, const std::string& file);
    lua::index load_file(lua::state* const state, const char* file);
    lua::index load_file(lua::state* const state, std::istream& stream, const std::string& name);

    lua::index load_string(lua::state* const state, const std::string& input);
    lua::index load_string(lua::state* const state, const char* input);

    /**
     * Runs every file in the directory, with optional recursion. If
     * you want to filter the files, specify a filter list on the directory
     * itself.
     */
    void run_dir(lua::state* const state, const QDir& dir, const bool recurse);

    template <class Input>
    lua::index run_string(lua::state* const state, Input& runnable)
    {
        return lua::invoke(lua::load_string(state, runnable));
    }

    template <class Input>
    lua::index run_file(lua::state* const state, Input& runnable)
    {
        return lua::invoke(lua::load_file(state, runnable));
    }

} // namespace lua

#endif // LUA_CXX_LOADERS_HEADER

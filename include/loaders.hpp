#ifndef LOADERS_HPP
#define LOADERS_HPP

#include <string>
#include "LuaEnvironment.hpp"

class QDir;

namespace lua
{
    void load_file(Lua& lua, const std::string& file);
    void load_file(Lua& lua, const QString& file);
    void load_file(Lua& lua, const char* file);

    void load_string(Lua& lua, const std::string& input);
    void load_string(Lua& lua, const QString& input);
    void load_string(Lua& lua, const char* input);

    /**
     * Load every file in the directory, with optional recursion. If
     * you want to filter the files, specify a filter list on the directory
     * itself.
     */
    void load_dir(Lua& lua, const QDir& dir, const bool recurse);
}

#endif // LOADERS_HPP

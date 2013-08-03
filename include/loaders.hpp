#ifndef LOADERS_HPP
#define LOADERS_HPP

#include <string>
#include "LuaEnvironment.hpp"

class QDir;

namespace lua
{
    void loadFile(LuaEnvironment& lua, const std::string& file);
    void loadFile(LuaEnvironment& lua, const char* file);

    void loadString(LuaEnvironment& lua, const std::string& input);
    void loadString(LuaEnvironment& lua, const char* input);

    /**
     * Load every file in the directory, with optional recursion. If
     * you want to filter the files, specify a filter list on the directory
     * itself.
     */
    void loadDir(LuaEnvironment& lua, const QDir& dir, const bool recurse);
}

#endif // LOADERS_HPP

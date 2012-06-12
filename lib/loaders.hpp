#ifndef LOADERS_HPP
#define LOADERS_HPP

#include <string>
#include "Lua.hpp"

namespace lua
{
    void load_file(Lua& lua, const std::string& file);
    void load_string(Lua& lua, const std::string& input);
}

#endif // LOADERS_HPP

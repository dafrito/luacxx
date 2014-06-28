#ifndef LUA_CXX_MODULE_LOADER_HEADER
#define LUA_CXX_MODULE_LOADER_HEADER

#include "stack.hpp"

#include <string>

class ModuleLoader
{
public:
    virtual bool search(const std::string& module)=0;
    virtual void load(lua_State* const state, const std::string& module)=0;
    virtual ~ModuleLoader() {}
};

#endif // MODULELOADER_HEADER

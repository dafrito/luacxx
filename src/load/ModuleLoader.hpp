#ifndef LUACXX_MODULE_LOADER_INCLUDED
#define LUACXX_MODULE_LOADER_INCLUDED

#include "stack.hpp"

#include <string>

class ModuleLoader
{
public:
    virtual bool search(const std::string& module)=0;
    virtual void load(lua_State* const state, const std::string& module)=0;
    virtual ~ModuleLoader() {}
};

#endif // LUACXX_MODULE_LOADER_INCLUDED

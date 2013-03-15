#ifndef MODULELOADER_HEADER
#define MODULELOADER_HEADER

#include <QString>
#include "LuaEnvironment.hpp"

class ModuleLoader
{
public:
    virtual bool search(const QString& module)=0;

    virtual void load(Lua& lua, const QString& module)=0;

    virtual ~ModuleLoader() {}
};

#endif // MODULELOADER_HEADER

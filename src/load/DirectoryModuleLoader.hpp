#ifndef LUACXX_DIRECTORY_MODULE_LOADER_INCLUDED
#define LUACXX_DIRECTORY_MODULE_LOADER_INCLUDED

#include "ModuleLoader.hpp"

#include <string>

#include <QDir>
#include <QFile>

class DirectoryModuleLoader : public ModuleLoader
{
    QDir _root;
    std::string _prefix;

    void resolve(QFile& file, const std::string& module);

public:
    void setRoot(const QDir&& root)
    {
        _root = root;
    }

    void setPrefix(const std::string& prefix)
    {
        _prefix = prefix;
    }

    bool search(const std::string& module);
    void load(lua_State* const state, const std::string& module);
};

#endif // LUACXX_DIRECTORY_MODULE_LOADER_INCLUDED

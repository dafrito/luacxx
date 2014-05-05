#ifndef DIRECTORYMODULELOADER_HEADER
#define DIRECTORYMODULELOADER_HEADER

#include "ModuleLoader.hpp"

#include <QDir>
#include <QFile>
#include <string>

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
    void load(lua::state* const state, const std::string& module);
};

#endif // DIRECTORYMODULELOADER_HEADER

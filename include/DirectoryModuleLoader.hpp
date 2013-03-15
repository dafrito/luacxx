#ifndef DIRECTORYMODULELOADER_HEADER
#define DIRECTORYMODULELOADER_HEADER

#include "ModuleLoader.hpp"
#include <QDir>
#include <QString>

class DirectoryModuleLoader : public ModuleLoader
{
    QDir _root;

    void resolve(QFile& file, const QString& module);

public:

    DirectoryModuleLoader(const QDir& root) :
        _root(root)
    {
    }

    bool search(const QString& module);
    void load(Lua& lua, const QString& module);
};

#endif // DIRECTORYMODULELOADER_HEADER

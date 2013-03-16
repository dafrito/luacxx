#ifndef DIRECTORYMODULELOADER_HEADER
#define DIRECTORYMODULELOADER_HEADER

#include "ModuleLoader.hpp"
#include <QDir>
#include <QString>

class DirectoryModuleLoader : public ModuleLoader
{
    QDir _root;

    QString _prefix;

    void resolve(QFile& file, const QString& module);

public:

    void setRoot(const QDir&& root)
    {
        _root = root;
    }

    void setPrefix(const QString& prefix)
    {
        _prefix = prefix;
    }

    bool search(const QString& module);
    void load(Lua& lua, const QString& module);
};

#endif // DIRECTORYMODULELOADER_HEADER

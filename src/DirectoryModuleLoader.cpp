#include "DirectoryModuleLoader.hpp"
#include "LuaValue.hpp"

void DirectoryModuleLoader::resolve(QFile& file, const QString& module)
{
    QString modulePath(module);
    if (!_prefix.isEmpty()) {
        if (!modulePath.startsWith(_prefix)) {
            return;
        }
        modulePath = modulePath.mid(_prefix.length());
    }
    file.setFileName(_root.filePath(modulePath + ".lua"));
}

bool DirectoryModuleLoader::search(const QString& module)
{
    QFile moduleFile;
    resolve(moduleFile, module);
    return moduleFile.exists();
}

void DirectoryModuleLoader::load(Lua& lua, const QString& module)
{
    QFile moduleFile;
    resolve(moduleFile, module);
    if (!moduleFile.exists()) {
        throw std::runtime_error(
            (QString("Module name '") + module + "' must resolve to an existing file").toStdString()
        );
    }
    lua(moduleFile);
}

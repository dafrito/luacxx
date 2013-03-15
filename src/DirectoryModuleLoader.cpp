#include "DirectoryModuleLoader.hpp"
#include "LuaValue.hpp"

void DirectoryModuleLoader::resolve(QFile& file, const QString& module)
{
    file.setFileName(_root.filePath(module + ".lua"));
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
        throw QString("Module does not exist: ") + module;
    }
    lua(moduleFile);
}

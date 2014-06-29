#include "DirectoryModuleLoader.hpp"

#include "lua-cxx/load.hpp"

void DirectoryModuleLoader::resolve(QFile& file, const std::string& module)
{
    QString modulePath(module.c_str());
    if (!_prefix.empty()) {
        if (!modulePath.startsWith(_prefix.c_str())) {
            return;
        }
        modulePath = modulePath.mid(_prefix.length());
    }
    file.setFileName(_root.filePath(modulePath + ".lua"));
}

bool DirectoryModuleLoader::search(const std::string& module)
{
    QFile moduleFile;
    resolve(moduleFile, module);
    return moduleFile.exists();
}

void DirectoryModuleLoader::load(lua_State* const state, const std::string& module)
{
    QFile moduleFile;
    resolve(moduleFile, module);
    if (!moduleFile.exists()) {
        throw std::runtime_error(
            std::string("Module name '") + module + "' must resolve to an existing file"
        );
    }

    lua::run_file(state, moduleFile);
}

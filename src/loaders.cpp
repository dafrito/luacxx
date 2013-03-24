#include "loaders.hpp"
#include <fstream>
#include <sstream>
#include <QDir>

#include "LuaValue.hpp"

namespace lua
{
    void load_file(Lua& lua, const std::string& file)
    {
        std::ifstream f(file, std::ios::in);
        lua(f, file);
    }

    void load_file(Lua& lua, const QString& file)
    {
        load_file(lua, file.toStdString());
    }

    void load_file(Lua& lua, const char* file)
    {
        load_file(lua, std::string(file));
    }

    void load_string(Lua& lua, const std::string& input)
    {
        std::istringstream stream(input);
        lua(stream, "string input");
    }

    void load_string(Lua& lua, const QString& input)
    {
        load_string(lua, input.toStdString());
    }

    void load_string(Lua& lua, const char* input)
    {
        load_string(lua, std::string(input));
    }

    void load_dir(Lua& lua, const QDir& dir, const bool recurse)
    {
        foreach(QFileInfo info, dir.entryInfoList(
            (recurse ? QDir::AllEntries : QDir::Files) | QDir::NoDotAndDotDot))
        {
            if (info.isFile()) {
                QFile file(info.filePath());
                lua(file);
            } else if (recurse && info.isDir()) {
                load_dir(lua, info.filePath(), recurse);
            }
        }
    }
}


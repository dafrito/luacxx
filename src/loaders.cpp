#include "loaders.hpp"
#include <fstream>
#include <sstream>
#include <QDir>

#include "LuaValue.hpp"

namespace lua
{
    void load_file(LuaEnvironment& lua, const std::string& file)
    {
        std::ifstream f(file, std::ios::in);
        if (!f) {
            throw std::runtime_error(std::string("File stream could not be opened for '") + file + "'");
        }
        lua(f, file);
    }

    void load_file(LuaEnvironment& lua, const QString& file)
    {
        load_file(lua, file.toStdString());
    }

    void load_file(LuaEnvironment& lua, const char* file)
    {
        load_file(lua, std::string(file));
    }

    void load_string(LuaEnvironment& lua, const std::string& input)
    {
        std::istringstream stream(input);
        lua(stream, "string input");
    }

    void load_string(LuaEnvironment& lua, const QString& input)
    {
        load_string(lua, input.toStdString());
    }

    void load_string(LuaEnvironment& lua, const char* input)
    {
        load_string(lua, std::string(input));
    }

    void load_dir(LuaEnvironment& lua, const QDir& dir, const bool recurse)
    {
        foreach(QFileInfo info, dir.entryInfoList(
            (recurse ? QDir::AllEntries : QDir::Files) | QDir::NoDotAndDotDot,
            QDir::Name
            ))
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


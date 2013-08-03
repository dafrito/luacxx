#include "loaders.hpp"
#include <fstream>
#include <sstream>
#include <QDir>

#include "LuaValue.hpp"

namespace lua
{
    void loadFile(LuaEnvironment& lua, const std::string& file)
    {
        std::ifstream f(file, std::ios::in);
        if (!f) {
            throw std::runtime_error(std::string("File stream could not be opened for '") + file + "'");
        }
        lua(f, file);
    }

    void loadFile(LuaEnvironment& lua, const QString& file)
    {
        loadFile(lua, file.toStdString());
    }

    void loadFile(LuaEnvironment& lua, const char* file)
    {
        loadFile(lua, std::string(file));
    }

    void loadString(LuaEnvironment& lua, const std::string& input)
    {
        std::istringstream stream(input);
        lua(stream, "string input");
    }

    void loadString(LuaEnvironment& lua, const QString& input)
    {
        loadString(lua, input.toStdString());
    }

    void loadString(LuaEnvironment& lua, const char* input)
    {
        loadString(lua, std::string(input));
    }

    void loadDir(LuaEnvironment& lua, const QDir& dir, const bool recurse)
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
                loadDir(lua, info.filePath(), recurse);
            }
        }
    }
}


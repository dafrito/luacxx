#include "loaders.hpp"
#include <fstream>
#include <sstream>
#include <QDir>

#include "LuaValue.hpp"

using namespace std;

namespace lua
{
    void load_file(Lua& lua, const string& file)
    {
        ifstream f(file, ios::in);
        lua(f, file);
    }

    void load_string(Lua& lua, const string& input)
    {
        std::istringstream stream(input);
        lua(stream, "string input");
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


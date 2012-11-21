#include <QtTest/QtTest>
#include "LuaEnvironment.hpp"
#include "loaders.hpp"
#include "LuaGlobal.hpp"

using namespace std;

class LoaderTests : public QObject
{
    Q_OBJECT
private slots:

    void testLuaCanLoadAFileStreamIntoItsEnvironment()
    {
        Lua lua;
        lua["No"] = "Time";
        lua::load_file(lua, "simple.lua");
    }

    void testLuaSupportsQFile()
    {
        Lua lua;
        lua["No"] = "Time";
        QFile file("simple.lua");
        lua(file);
    }
};

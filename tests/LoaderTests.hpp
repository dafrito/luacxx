#include <QtTest/QtTest>
#include "LuaEnvironment.hpp"
#include "LuaValue.hpp"
#include "loaders.hpp"

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

    void luaSupportsDirectories()
    {
        Lua lua;
        lua::load_dir(lua, QDir("dummy"), true);
        QCOMPARE((int)lua["a"], 42);
        QCOMPARE((const char*)lua["b"], "foo");
    }
};

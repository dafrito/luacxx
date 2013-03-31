#include <QtTest/QtTest>
#include "LuaEnvironment.hpp"
#include "LuaValue.hpp"
#include "loaders.hpp"
#include <functional>
#include "table.hpp"

#include "DirectoryModuleLoader.hpp"

using namespace std;

class LoaderTests : public QObject
{
    Q_OBJECT
private slots:

    void testLuaCanLoadAFileStreamIntoItsEnvironment()
    {
        Lua lua;
        lua["No"] = "Time";
        lua::load_file(lua, LUA_DIR "simple.lua");
    }

    void testLuaSupportsQFile()
    {
        Lua lua;
        lua["No"] = "Time";
        QFile file(LUA_DIR "simple.lua");
        lua(file);
    }

    void luaSupportsDirectories()
    {
        Lua lua;
        lua::load_dir(lua, QDir(LUA_DIR "bin"), true);
        QCOMPARE((int)lua["a"], 42);
        QCOMPARE((const char*)lua["b"], "foo");
    }

    void testDirectoryModuleLoader()
    {
        Lua lua;

        DirectoryModuleLoader loader;
        loader.setRoot(QDir(LUA_DIR "testlib"));
        loader.setPrefix("testlib/");

        const char* searchersName = "searchers";
        #if LUA_VERSION_NUM < 502
            searchersName = "loaders";
        #endif

        QString module;
        table::push(lua["package"][searchersName],
            std::function< std::function<void()>(const QString) >(
                [&](const QString arg) {
                    module = arg;
                    return [&]() {
                        loader.load(lua, module);
                    };
                }
            )
        );

        lua["foo"] = std::function<int(int, int)>( [](int a, int b) {
            return a + b;
        });

        lua("require 'testlib/Library';"
            ""
            "bar = Curry(foo, 40);"
        );

        QCOMPARE((int)lua["bar"](2), 42);
    }

    void testModuleLoaderUtility()
    {
        Lua lua;

        DirectoryModuleLoader loader;
        loader.setRoot(QDir(LUA_DIR "testlib"));
        loader.setPrefix("testlib/");

        lua.addModuleLoader(&loader);

        lua["foo"] = std::function<int(int, int)>( [](int a, int b) {
            return a + b;
        });

        lua("require 'testlib/Library';"
            ""
            "bar = Curry(foo, 40);"
        );

        QCOMPARE((int)lua["bar"](2), 42);
    }
};

#include <string>
#include <QtTest/QtTest>

#include "LuaEnvironment.hpp"
#include "loaders.hpp"
#include "LuaException.hpp"
#include "LuaStack.hpp"
#include "LuaValue.hpp"
#include "mocks.hpp"
#include "table.hpp"
#include <iostream>

#include <functional>

#include "DirectoryModuleLoader.hpp"

using namespace std;

namespace {

int addNumbers(int a, int b)
{
    return a + b;
}

} // anonymous namespace

class LuaTableTests : public QObject
{
    Q_OBJECT
private slots:

    void testPushWithInteger()
    {
        Lua lua;
        LuaStack stack(lua);

        lua("foo = {}");

        table::push(lua["foo"], 42);

        QCOMPARE((int)lua["foo"][1], 42);
    }

    void testPushWithFunction()
    {
        Lua lua;
        LuaStack stack(lua);

        lua("foo = {}");

        table::push(lua["foo"], addNumbers);

        QCOMPARE((int)lua("return foo[1](2, 2)"), 4);
    }

    void testManuallyConfiguredLoader()
    {
        Lua lua;

        QString module;

        const char* searchersName = "searchers";
        #if LUA_VERSION_NUM < 502
            searchersName = "loaders";
        #endif

        table::push(lua["package"][searchersName],
            std::function< std::function<void()>(const QString) >(
                [&](const QString arg) {
                    module = QDir::home().filePath("src/fritomod");
                    module += "/";
                    module += arg;
                    module += ".lua";
                    return [&]() {
                        QFile moduleFile(module);
                        if (moduleFile.exists()) {
                            lua(moduleFile);
                        }
                    };
                }
            )
        );

        lua["foo"] = std::function<int(int, int)>( [](int a, int b) {
            return a + b;
        });

        lua("require 'fritomod/currying';"
            ""
            "bar = Curry(foo, 40);"
        );

        QCOMPARE((int)lua["bar"](2), 42);
    }

    void testDirectoryModuleLoader()
    {
        Lua lua;

        DirectoryModuleLoader loader;
        loader.setRoot(QDir(QDir::home().filePath("src/fritomod/fritomod")));
        loader.setPrefix("fritomod/");

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

        lua("require 'fritomod/currying';"
            ""
            "bar = Curry(foo, 40);"
        );

        QCOMPARE((int)lua["bar"](2), 42);
    }

    void testModuleLoaderUtility()
    {
        Lua lua;

        DirectoryModuleLoader loader;
        loader.setRoot(QDir(QDir::home().filePath("src/fritomod/fritomod")));
        loader.setPrefix("fritomod/");

        lua.addModuleLoader(&loader);

        lua["foo"] = std::function<int(int, int)>( [](int a, int b) {
            return a + b;
        });

        lua("require 'fritomod/currying';"
            ""
            "bar = Curry(foo, 40);"
        );

        QCOMPARE((int)lua["bar"](2), 42);
    }

};

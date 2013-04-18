#include "init.hpp"

#include "table.hpp"
#include "DirectoryModuleLoader.hpp"

BOOST_AUTO_TEST_CASE(testLuaCanLoadAFileStreamIntoItsEnvironment)
{
    Lua lua;
    lua["No"] = "Time";
    lua::load_file(lua, LUA_DIR "simple.lua");
}

BOOST_AUTO_TEST_CASE(testLuaSupportsQFile)
{
    Lua lua;
    lua["No"] = "Time";
    QFile file(LUA_DIR "simple.lua");
    lua(file);
}

BOOST_AUTO_TEST_CASE(luaSupportsDirectories)
{
    Lua lua;
    lua::load_dir(lua, QDir(LUA_DIR "bin"), true);
    BOOST_REQUIRE_EQUAL((int)lua["a"], 42);
    BOOST_REQUIRE_EQUAL((const char*)lua["b"], "foo");
}

BOOST_AUTO_TEST_CASE(testDirectoryModuleLoader)
{
    Lua lua;

    DirectoryModuleLoader loader;
    loader.setRoot(QDir(LUA_DIR "testlib"));
    loader.setPrefix("testlib/");

    const char* searchersName = "searchers";
    #if LUA_VERSION_NUM < 502
        searchersName = "loaders";
    #endif

    std::string module;
    table::push(lua["package"][searchersName],
        std::function< std::function<void()>(const std::string&) >(
            [&](const std::string& arg) {
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

    BOOST_REQUIRE_EQUAL((int)lua["bar"](2), 42);
}

BOOST_AUTO_TEST_CASE(testModuleLoaderUtility)
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

    BOOST_REQUIRE_EQUAL((int)lua["bar"](2), 42);
}

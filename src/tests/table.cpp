#include "init.hpp"

#include "table.hpp"

namespace {

int addNumbers(int a, int b)
{
    return a + b;
}

int returnMagic()
{
    return 42;
}

} // namespace anonymous

BOOST_AUTO_TEST_CASE(testPushWithInteger)
{
    LuaEnvironment lua;
    LuaStack stack(lua);

    lua("foo = {}");

    table::push(lua["foo"], 42);

    BOOST_REQUIRE_EQUAL((int)lua["foo"][1], 42);
}

BOOST_AUTO_TEST_CASE(testPushWithFunction)
{
    LuaEnvironment lua;
    LuaStack stack(lua);

    lua("foo = {}");

    table::push(lua["foo"], addNumbers);

    BOOST_REQUIRE_EQUAL((int)lua("return foo[1](2, 2)"), 4);
}

BOOST_AUTO_TEST_CASE(tablesCanBeSetWhileNested)
{
    LuaEnvironment lua;

    lua["Rainback"] = lua::value::table;
    lua["Rainback"]["Font"] = returnMagic;

    lua("assert(Rainback.Font)");
}

BOOST_AUTO_TEST_CASE(tableReferences)
{
    LuaEnvironment lua;

    lua("foo = {bar = 42}");

    BOOST_REQUIRE_EQUAL(lua["foo"]["bar"].typestring(), std::string("number"));
}

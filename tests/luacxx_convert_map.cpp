#include "main.hpp"

#include "luacxx/thread.hpp"
#include "luacxx/stack.hpp"
#include "luacxx/algorithm.hpp"
#include "luacxx/load.hpp"

#include "luacxx/convert/map.hpp"
#include "luacxx/convert/numeric.hpp"
#include "luacxx/convert/string.hpp"

#include <map>
#include <string>

BOOST_AUTO_TEST_CASE(luacxx_convert_map)
{
    auto env = lua::create();

    std::map<std::string, int> values {
        {"one", 1},
        {"two", 2},
        {"three", 3},
    };
    env["foo"] = values;

    std::map<std::string, int> values_from_lua;
    lua::store(values_from_lua, env["foo"]);

    BOOST_REQUIRE_EQUAL(values_from_lua.size(), 3);
    BOOST_CHECK_EQUAL(values_from_lua["one"], 1);
    BOOST_CHECK_EQUAL(values_from_lua["two"], 2);
    BOOST_CHECK_EQUAL(values_from_lua["three"], 3);

    lua::run_string(env, "assert(foo.one == 1)");
    lua::run_string(env, "assert(foo.two == 2)");
    lua::run_string(env, "assert(foo.three == 3)");
}

BOOST_AUTO_TEST_CASE(luacxx_convert_map_replaces_destination_contents)
{
    auto env = lua::create();

    lua::run_string(env, "foo = { alpha = 4, beta = 5 }");

    std::map<std::string, int> values_from_lua {
        {"stale", 99},
        {"alpha", 0},
        {"gamma", 101},
    };
    lua::store(values_from_lua, env["foo"]);

    BOOST_REQUIRE_EQUAL(values_from_lua.size(), 2);
    BOOST_CHECK_EQUAL(values_from_lua.count("stale"), 0);
    BOOST_CHECK_EQUAL(values_from_lua.count("gamma"), 0);
    BOOST_CHECK_EQUAL(values_from_lua["alpha"], 4);
    BOOST_CHECK_EQUAL(values_from_lua["beta"], 5);
}

BOOST_AUTO_TEST_CASE(luacxx_convert_map_push_copies_values)
{
    auto env = lua::create();

    std::map<std::string, int> values {
        {"one", 1},
        {"two", 2},
    };
    env["foo"] = values;

    values["one"] = 99;
    values["three"] = 3;
    values.erase("two");

    std::map<std::string, int> values_from_lua;
    lua::store(values_from_lua, env["foo"]);

    BOOST_REQUIRE_EQUAL(values_from_lua.size(), 2);
    BOOST_CHECK_EQUAL(values_from_lua.count("three"), 0);
    BOOST_CHECK_EQUAL(values_from_lua["one"], 1);
    BOOST_CHECK_EQUAL(values_from_lua["two"], 2);

    lua::run_string(env, "assert(foo.one == 1)");
    lua::run_string(env, "assert(foo.two == 2)");
    lua::run_string(env, "assert(foo.three == nil)");
}

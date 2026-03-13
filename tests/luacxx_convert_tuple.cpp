#include "main.hpp"

#include "luacxx/thread.hpp"
#include "luacxx/stack.hpp"
#include "luacxx/algorithm.hpp"
#include "luacxx/load.hpp"

#include "luacxx/convert/tuple.hpp"
#include "luacxx/convert/numeric.hpp"
#include "luacxx/convert/string.hpp"

#include <string>
#include <tuple>

BOOST_AUTO_TEST_CASE(luacxx_convert_tuple)
{
    auto env = lua::create();

    std::tuple<int, std::string, bool> value {1, "two", true};
    env["foo"] = value;

    std::tuple<int, std::string, bool> value_from_lua;
    lua::store(value_from_lua, env["foo"]);

    BOOST_CHECK_EQUAL(std::get<0>(value_from_lua), 1);
    BOOST_CHECK_EQUAL(std::get<1>(value_from_lua), "two");
    BOOST_CHECK_EQUAL(std::get<2>(value_from_lua), true);

    lua::run_string(env, "assert(#foo == 3)");
    lua::run_string(env, "assert(foo[1] == 1)");
    lua::run_string(env, "assert(foo[2] == 'two')");
    lua::run_string(env, "assert(foo[3] == true)");
}

BOOST_AUTO_TEST_CASE(luacxx_convert_tuple_replaces_destination_contents)
{
    auto env = lua::create();

    lua::run_string(env, "foo = {4, 'five', false}");

    std::tuple<int, std::string, bool> value_from_lua {99, "stale", true};
    lua::store(value_from_lua, env["foo"]);

    BOOST_CHECK_EQUAL(std::get<0>(value_from_lua), 4);
    BOOST_CHECK_EQUAL(std::get<1>(value_from_lua), "five");
    BOOST_CHECK_EQUAL(std::get<2>(value_from_lua), false);
}

BOOST_AUTO_TEST_CASE(luacxx_convert_tuple_push_copies_values)
{
    auto env = lua::create();

    std::tuple<int, std::string, bool> value {1, "two", true};
    env["foo"] = value;

    std::get<0>(value) = 99;
    std::get<1>(value) = "changed";
    std::get<2>(value) = false;

    std::tuple<int, std::string, bool> value_from_lua;
    lua::store(value_from_lua, env["foo"]);

    BOOST_CHECK_EQUAL(std::get<0>(value_from_lua), 1);
    BOOST_CHECK_EQUAL(std::get<1>(value_from_lua), "two");
    BOOST_CHECK_EQUAL(std::get<2>(value_from_lua), true);

    lua::run_string(env, "assert(foo[1] == 1)");
    lua::run_string(env, "assert(foo[2] == 'two')");
    lua::run_string(env, "assert(foo[3] == true)");
}

BOOST_AUTO_TEST_CASE(luacxx_convert_tuple_rejects_wrong_sized_table)
{
    auto env = lua::create();

    lua::run_string(env, "foo = {1, 'two', true, 'extra'}");

    std::tuple<int, std::string, bool> value_from_lua;

    BOOST_CHECK_THROW(lua::store(value_from_lua, env["foo"]), lua::error);
}

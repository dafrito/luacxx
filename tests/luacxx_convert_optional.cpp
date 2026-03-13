#include "main.hpp"

#include "luacxx/thread.hpp"
#include "luacxx/stack.hpp"
#include "luacxx/algorithm.hpp"
#include "luacxx/load.hpp"

#include "luacxx/convert/optional.hpp"
#include "luacxx/convert/numeric.hpp"

#include <optional>

BOOST_AUTO_TEST_CASE(luacxx_convert_optional)
{
    auto env = lua::create();

    std::optional<int> value = 42;
    env["foo"] = value;

    std::optional<int> value_from_lua;
    lua::store(value_from_lua, env["foo"]);

    BOOST_REQUIRE(value_from_lua.has_value());
    BOOST_CHECK_EQUAL(*value_from_lua, 42);

    lua::run_string(env, "assert(foo == 42)");
}

BOOST_AUTO_TEST_CASE(luacxx_convert_optional_nil)
{
    auto env = lua::create();

    std::optional<int> value;
    env["foo"] = value;

    std::optional<int> value_from_lua = 99;
    lua::store(value_from_lua, env["foo"]);

    BOOST_CHECK(!value_from_lua.has_value());

    lua::run_string(env, "assert(foo == nil)");
}

BOOST_AUTO_TEST_CASE(luacxx_convert_optional_replaces_destination_contents)
{
    auto env = lua::create();

    lua::run_string(env, "foo = nil");

    std::optional<int> value_from_lua = 99;
    lua::store(value_from_lua, env["foo"]);
    BOOST_CHECK(!value_from_lua.has_value());

    lua::run_string(env, "foo = 17");
    lua::store(value_from_lua, env["foo"]);

    BOOST_REQUIRE(value_from_lua.has_value());
    BOOST_CHECK_EQUAL(*value_from_lua, 17);
}

BOOST_AUTO_TEST_CASE(luacxx_convert_optional_push_copies_values)
{
    auto env = lua::create();

    std::optional<int> value = 7;
    env["foo"] = value;

    value = 99;

    std::optional<int> value_from_lua;
    lua::store(value_from_lua, env["foo"]);

    BOOST_REQUIRE(value_from_lua.has_value());
    BOOST_CHECK_EQUAL(*value_from_lua, 7);

    lua::run_string(env, "assert(foo == 7)");
}

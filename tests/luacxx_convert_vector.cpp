#include "main.hpp"

#include "luacxx/thread.hpp"
#include "luacxx/stack.hpp"
#include "luacxx/algorithm.hpp"
#include "luacxx/load.hpp"

#include "luacxx/convert/vector.hpp"
#include "luacxx/convert/numeric.hpp"

BOOST_AUTO_TEST_CASE(luacxx_convert_vector)
{
    auto env = lua::create();

    std::vector<int> nums {1, 2, 3};
    env["foo"] = nums;

    std::vector<int> nums_from_lua;
    lua::store(nums_from_lua, env["foo"]);

    BOOST_REQUIRE_EQUAL(nums_from_lua.size(), 3);
    BOOST_CHECK_EQUAL(nums_from_lua[0], 1);
    BOOST_CHECK_EQUAL(nums_from_lua[1], 2);
    BOOST_CHECK_EQUAL(nums_from_lua[2], 3);

    lua::run_string(env, "assert(foo[1] == 1)");
    lua::run_string(env, "assert(foo[2] == 2)");
    lua::run_string(env, "assert(foo[3] == 3)");
}

BOOST_AUTO_TEST_CASE(luacxx_convert_vector_replaces_destination_contents)
{
    auto env = lua::create();

    lua::run_string(env, "foo = {4, 5}");

    std::vector<int> nums_from_lua {99, 100, 101};
    lua::store(nums_from_lua, env["foo"]);

    BOOST_REQUIRE_EQUAL(nums_from_lua.size(), 2);
    BOOST_CHECK_EQUAL(nums_from_lua[0], 4);
    BOOST_CHECK_EQUAL(nums_from_lua[1], 5);
}

BOOST_AUTO_TEST_CASE(luacxx_convert_vector_push_copies_values)
{
    auto env = lua::create();

    std::vector<int> nums {1, 2, 3};
    env["foo"] = nums;

    nums[0] = 99;
    nums[1] = 100;
    nums.pop_back();

    std::vector<int> nums_from_lua;
    lua::store(nums_from_lua, env["foo"]);

    BOOST_REQUIRE_EQUAL(nums_from_lua.size(), 3);
    BOOST_CHECK_EQUAL(nums_from_lua[0], 1);
    BOOST_CHECK_EQUAL(nums_from_lua[1], 2);
    BOOST_CHECK_EQUAL(nums_from_lua[2], 3);

    lua::run_string(env, "assert(#foo == 3)");
    lua::run_string(env, "assert(foo[1] == 1)");
    lua::run_string(env, "assert(foo[2] == 2)");
    lua::run_string(env, "assert(foo[3] == 3)");
}

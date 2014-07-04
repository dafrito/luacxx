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

    BOOST_REQUIRE_EQUAL(nums.size(), 3);
    BOOST_CHECK_EQUAL(nums[0], 1);
    BOOST_CHECK_EQUAL(nums[1], 2);
    BOOST_CHECK_EQUAL(nums[2], 3);
}

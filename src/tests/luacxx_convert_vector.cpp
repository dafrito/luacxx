#include "main.hpp"

#include "thread.hpp"
#include "stack.hpp"
#include "algorithm.hpp"
#include "load.hpp"

#include "convert/vector.hpp"
#include "convert/numeric.hpp"

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

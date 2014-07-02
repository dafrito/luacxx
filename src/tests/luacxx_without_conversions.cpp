#include "main.hpp"

#include "luacxx/thread.hpp"
#include "luacxx/stack.hpp"
#include "luacxx/algorithm.hpp"
#include "luacxx/load.hpp"

BOOST_AUTO_TEST_CASE(luacxx_without_conversions)
{
    auto env = lua::create();

    env["foo"] = 42;
    BOOST_CHECK(!env["foo"].type().number());
    BOOST_CHECK(env["foo"].type().userdata());

    // const char* conversion is implicit
    env["bar"] = "notime";
    BOOST_CHECK(env["bar"].type().string());
    BOOST_CHECK(!env["bar"].type().userdata());

    env["baz"] = true;
    BOOST_CHECK(!env["baz"].type().boolean());
    BOOST_CHECK(env["baz"].type().userdata());
    lua::push(env["baz"]);
}

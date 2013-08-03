#include "init.hpp"

BOOST_AUTO_TEST_CASE(insertion)
{
    LuaEnvironment lua;
    LuaStack stack(lua);

    lua::push(stack, true);
    lua::push(stack, 42);
    lua::push(stack, "No time");

    BOOST_CHECK_EQUAL(stack.typestring(-1), "string");
    BOOST_CHECK_EQUAL(stack.typestring(-2), "number");
    BOOST_CHECK_EQUAL(stack.typestring(-3), "boolean");
}

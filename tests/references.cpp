#include "init.hpp"

#include "LuaGlobalAccessible.hpp"

BOOST_AUTO_TEST_CASE(testLuaHandlesReferencesProperly)
{
    Lua lua;
    LuaStack stack(lua);
    stack << "No Time";
    LuaReference ref = stack.save();
    BOOST_REQUIRE(stack.size() == 1);
    lua::push(stack, ref);
    BOOST_REQUIRE_EQUAL(stack.as<const char*>(), "No Time");
}

BOOST_AUTO_TEST_CASE(testAccessibleCanGetAReference)
{
    Lua lua;
    LuaReferenceAccessible accessor(lua.luaState());
    LuaStack s(lua);
    s << "No Time";
    accessor.store(s);
    BOOST_REQUIRE_EQUAL(s.as<const char*>(), "No Time");
    s.clear();
    accessor.push(s);
    BOOST_REQUIRE_EQUAL(s.as<const char*>(), "No Time");
}

BOOST_AUTO_TEST_CASE(testAccessibleCanGetAGlobal)
{
    Lua lua;
    LuaGlobalAccessible accessor("foo");
    LuaStack s(lua);
    s << "No Time";
    accessor.store(s);
    BOOST_REQUIRE_EQUAL((const char*)lua["foo"], "No Time");
    s.clear();
    accessor.push(s);
    BOOST_REQUIRE_EQUAL(s.as<const char*>(), "No Time");
}

BOOST_AUTO_TEST_CASE(testLuaValueGetsALength)
{
    Lua lua;
    lua("foo = {42, 42, 42}");
    BOOST_REQUIRE_EQUAL(lua["foo"].length(), 3);
}

#include "init.hpp"

#include "LuaGlobalAccessible.hpp"

BOOST_AUTO_TEST_CASE(testLuaHandlesReferencesProperly)
{
    Lua lua;
    LuaStack s(lua);
    s << "No Time";
    LuaReference r = s.save();
    BOOST_REQUIRE(s.size() == 0);
    s << r;
    BOOST_REQUIRE_EQUAL(s.as<const char*>(), "No Time");
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

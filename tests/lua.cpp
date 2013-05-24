#include "init.hpp"

namespace {

int addToMagicNumber(int v)
{
    return 42 + v;
}

double addNumbers(int a, int b)
{
    return a + b;
}

double addBonanza(int a, long b, float c, double d, short e)
{
    return a+b+c+d+e;
}

void luaAdd(LuaStack& stack)
{
    auto a = stack.as<int>(1);
    auto b = stack.as<int>(2);
    stack.clear();
    stack << a + b;
}

int getMagicNumber()
{
    return 42;
}

void doNothing(int)
{
}

int subtract(int a, int b)
{
    return a - b;
}

int semiManaged(LuaStack& stack)
{
    return stack.as<int>(1) + stack.as<int>(2);
}

} // namespace anonymous

BOOST_AUTO_TEST_CASE(testLuaOffersSubscriptSupportForAccessingGlobalValues)
{
    Lua lua;
    lua("No = 'Time'");
    auto g = lua["No"];
    QString str;
    g.to(str);
    BOOST_REQUIRE_EQUAL((const char*)lua["No"], "Time");
}

BOOST_AUTO_TEST_CASE(testLuaOffersSubscriptSupportForGlobalValues)
{
    Lua lua;
    auto g = lua["No"];
    g = "Time";
    BOOST_REQUIRE_EQUAL((const char*)lua["No"], "Time");
}

BOOST_AUTO_TEST_CASE(testLuaRunsStringsDirectly)
{
    Lua lua;
    lua::load_string(lua, "_G['No']='Foo'");
    BOOST_REQUIRE_EQUAL((const char*)lua["No"], "Foo");
}

BOOST_AUTO_TEST_CASE(testLuaValueIsAProxyForTheGlobalTable)
{
    Lua lua;
    auto v = lua["No"];
    v = "Time";
    BOOST_REQUIRE_EQUAL((const char*)lua["No"], "Time");
}

BOOST_AUTO_TEST_CASE(testLuaCallsACFunction)
{
    Lua lua;
    std::string name("luaAdd");
    lua[name] = luaAdd;
    BOOST_REQUIRE_EQUAL("function", lua[name].typestring().c_str());
    lua::load_string(lua, std::string("Bar = ") + name + "(2, 2)");
    BOOST_REQUIRE_EQUAL((int)lua["Bar"], 4);
}

BOOST_AUTO_TEST_CASE(testLuaCallsAZeroParamFunction)
{
    Lua lua;
    std::string name("getMagicNumber");
    lua[name] = getMagicNumber;
    BOOST_CHECK_EQUAL("function", lua[name].typestring().c_str());
    lua::load_string(lua, std::string("Bar = ") + name + "()");
    BOOST_CHECK_EQUAL(lua["Bar"].as<int>(), 42);
}

BOOST_AUTO_TEST_CASE(testLuaCallsAOneParameterFunction)
{
    Lua lua;
    std::string name("addToMagicNumber");
    lua[name] = addToMagicNumber;
    BOOST_REQUIRE_EQUAL("function", lua[name].typestring().c_str());
    lua::load_string(lua, std::string("Bar = ") + name + "(2)");
    BOOST_REQUIRE_EQUAL((int)lua["Bar"], 44);
}

BOOST_AUTO_TEST_CASE(testLuaCallsATwoParameterFunction)
{
    Lua lua;
    std::string name("addNumbers");
    lua[name] = addNumbers;
    BOOST_REQUIRE_EQUAL("function", lua[name].typestring().c_str());
    lua::load_string(lua, std::string("Bar = ") + name + "(2, 3)");
    BOOST_REQUIRE_EQUAL((int)lua["Bar"], 5);
}

BOOST_AUTO_TEST_CASE(testLuaCallsABonanza)
{
    Lua lua;
    std::string name("addBonanza");
    lua[name] = addBonanza;
    BOOST_REQUIRE_EQUAL("function", lua[name].typestring().c_str());
    lua::load_string(lua, std::string("Bar = ") + name + "(2, 3, 4, 5, 6)");
    BOOST_REQUIRE_EQUAL((int)lua["Bar"], 2+3+4+5+6);
}

BOOST_AUTO_TEST_CASE(testLuaStackCallsAVoidFunction)
{
    Lua lua;
    std::string name("doNothing");
    lua[name] = doNothing;
    BOOST_REQUIRE("function" == lua[name].typestring());
    lua::load_string(lua, std::string("Bar = ") + name + "(2)");
}

BOOST_AUTO_TEST_CASE(testLuaCanPushClosures)
{
    Lua lua;
    LuaStack s(lua);
    s << 42;
    s << 24;
    lua::push(s, addNumbers, 2);
    s.setGlobal("foo");
    lua("assert(foo() == 66)");
}

BOOST_AUTO_TEST_CASE(testLuaCanPushClosuresWithMultipleArguments)
{
    Lua lua;
    LuaStack s(lua);
    s << 42;
    s << 20;
    lua::push(s, subtract, 2);
    s.setGlobal("foo");
    BOOST_REQUIRE_EQUAL((int)lua("return foo()"), 22);
}

BOOST_AUTO_TEST_CASE(testLuaCanPushLambdas)
{
    Lua lua;
    LuaStack s(lua);
    s << 42;
    s << 24;
    // In a perfect world, we wouldn't need to wrap the lambda inside a std::function, but
    // as far as I know, there's no way to get access the argument types of a lambda. This
    // is required for us to actually forward the function into Lua.
    lua::push(s, std::function<int(int, int)>([](int a, int b) { return a + b; }), 2);
    s.setGlobal("foo");
    lua("assert(foo() == 66)");
}

BOOST_AUTO_TEST_CASE(luaFunctionsCanBeCalledFromC)
{
    Lua lua;
    lua(""
    "function foo(a, b)\n"
    "    return a + b\n"
    "end");
    int result = lua["foo"](42, "24");
    BOOST_REQUIRE(result == 66);
}

BOOST_AUTO_TEST_CASE(luaCanReturnValuesFromEvaluatedStrings)
{
    Lua lua;
    BOOST_REQUIRE_EQUAL((int)lua("return 42"), 42);
}

BOOST_AUTO_TEST_CASE(luaValuesCanBeSetToRawValues)
{
    Lua lua;
    lua["foo"] = 42;
    lua("assert(foo == 42)");
    lua["foo"] = lua::value::table;
    lua("assert(type(foo) == 'table')");
    lua["foo"] = lua::value::nil;
    lua("assert(foo == nil)");
    BOOST_REQUIRE(lua["foo"].isNil());
}

BOOST_AUTO_TEST_CASE(someLuaFunctionsCanReturnValues)
{
    Lua lua;
    lua["foo"] = semiManaged;
    BOOST_REQUIRE_EQUAL((int)lua["foo"](1, 2), 3);
    lua["bar"] = std::function<int(LuaStack&)>(semiManaged);
    BOOST_REQUIRE_EQUAL((int)lua["bar"](3, 4), 7);
}

BOOST_AUTO_TEST_CASE(dualReturnValuesUseTheFirst)
{
    Lua lua;
    QFile falseFile(LUA_DIR "returnfalse.lua");
    BOOST_CHECK_EQUAL(lua(falseFile).as<bool>(), false);

    QFile trueFile(LUA_DIR "returntrue.lua");
    BOOST_CHECK_EQUAL(lua(trueFile).as<bool>(), true);
}

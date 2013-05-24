#include "init.hpp"

BOOST_AUTO_TEST_CASE(testLuaStackManagesItOwnStack)
{
    Lua lua;
    {
        LuaStack s(lua);
        s.global("No");
        {
            LuaStack s2(lua);
            BOOST_REQUIRE_EQUAL(1, s2.offset());
            s2.global("No");
            s2.global("Foo");
            BOOST_REQUIRE_EQUAL(2, s2.size());
        }
        // Stack is emptied when LuaStack goes out of scope.
        BOOST_REQUIRE_EQUAL(0, s.offset());
        BOOST_REQUIRE_EQUAL(1, s.size());
    }
    BOOST_REQUIRE_EQUAL(0, LuaStack(lua).size());
}

BOOST_AUTO_TEST_CASE(testLuaStackCanReplaceValues)
{
    Lua lua;
    LuaStack s(lua);
    s << 42 << 24;
    s.replace(-2);
    BOOST_REQUIRE_EQUAL(1, s.size());
    BOOST_REQUIRE_EQUAL(s.as<int>(), 24);
}

BOOST_AUTO_TEST_CASE(testLuaStackCanSwapValues)
{
    Lua lua;
    LuaStack s(lua);
    s << 1 << 2;
    // Stack is now [1, 2]

    s.swap();
    // Stack is now [2, 1]
    BOOST_REQUIRE_EQUAL(s.as<int>(), 1);
    s.pop();
    BOOST_REQUIRE_EQUAL(s.as<int>(), 2);
    s.pop();
}

BOOST_AUTO_TEST_CASE(testLuaStackCanSetGlobalValues)
{
    Lua lua;
    LuaStack s(lua);
    s.setGlobal("No", "Time");
    BOOST_REQUIRE_EQUAL((const char*)lua["No"], "Time");
}

BOOST_AUTO_TEST_CASE(luaStackCanBeComparedToValues)
{
    Lua lua;
    LuaStack s(lua);
    s << 42;

    // Truthy tests
    BOOST_REQUIRE_EQUAL(s.as<int>(), 42);

    // Falsy tests
    BOOST_REQUIRE(43 != s.as<int>());
}

BOOST_AUTO_TEST_CASE(testLuaStackHandlesNilValuesProperly)
{
    Lua lua;
    LuaStack s(lua);

    s << lua::value::nil;
    BOOST_REQUIRE(s.isNil());
}

BOOST_AUTO_TEST_CASE(testLuaStackSupportsBitwiseOperators)
{
    Lua lua;
    LuaStack s(lua);
    s << 42 << 34;
    int a, b;
    s >> a;
    BOOST_REQUIRE(a == 34);
    s >> b;
    BOOST_REQUIRE(b == 34);
}

BOOST_AUTO_TEST_CASE(testLuaStackCanBeDirectlyCastToAValue)
{
    Lua lua;
    LuaStack s(lua);
    s << 42;
    BOOST_REQUIRE(s.as<int>() == 42);
}

BOOST_AUTO_TEST_CASE(testStackSupportsIndexing)
{
    Lua lua;
    LuaStack s(lua);
    s << 5 << 6 << 7;

    int a;
    int b;
    int c;
    s.begin() >> a >> b >> c;
    BOOST_REQUIRE_EQUAL(a, 5);
    BOOST_REQUIRE_EQUAL(b, 6);
    BOOST_REQUIRE_EQUAL(c, 7);
}

BOOST_AUTO_TEST_CASE(testLuaStackPushesABoolean)
{
    Lua lua;
    LuaStack(lua).setGlobal("Good", false);
    BOOST_REQUIRE_EQUAL((bool)lua["Good"], false);
    BOOST_REQUIRE(LuaStack(lua).global("Good").type() == lua::type::boolean);
}

BOOST_AUTO_TEST_CASE(testLuaStackSetsANumber)
{
    Lua lua;
    LuaStack s(lua);
    // Note that Lua implicitly converts these numbers
    // to a floating-point type (typically a double), so
    // number() returns a double, instead of the integer
    // that we originally passed.
    s.setGlobal("No", 42);
    BOOST_REQUIRE_EQUAL(s.global("No").as<int>(), 42);
}

BOOST_AUTO_TEST_CASE(testYouCanPushTables)
{
    Lua lua;
    LuaStack s(lua);
    s << lua::value::table;
    BOOST_REQUIRE("table" == s.typestring());
}

BOOST_AUTO_TEST_CASE(testLuaHandlesInterestingCharValues)
{
    Lua lua;
    LuaStack s(lua);
    char c = 'c';
    s.push(&c, 1);
    std::string sink;
    s >> sink;
    BOOST_REQUIRE(sink == "c");
}

BOOST_AUTO_TEST_CASE(testLuaHandlesQString)
{
    Lua lua;
    LuaStack s(lua);
    QString i('c');
    s << i;
    QString o;
    s >> o;
    BOOST_CHECK(o == QString("c"));
}

BOOST_AUTO_TEST_CASE(testLuaHandlesQChar)
{
    Lua lua;
    LuaStack s(lua);
    QChar i('c');
    s << i;
    QChar o(s.as<char>());

    BOOST_CHECK_EQUAL(o.toLatin1(), i.toLatin1());
    BOOST_CHECK(i == o);
}

BOOST_AUTO_TEST_CASE(testLuaHandlesQVariants)
{
    Lua lua;
    lua["foo"] = QVariant(42);
    BOOST_REQUIRE(lua["foo"] == 42);
}

static void receive(LuaStack& stack)
{
    BOOST_REQUIRE_EQUAL(stack.as<const char*>(1), "getValue");
    BOOST_REQUIRE_EQUAL(stack.as<int>(2), 2);
}

BOOST_AUTO_TEST_CASE(closuresHandleStringsProperly)
{
    Lua lua;
    LuaStack s(lua);
    s << "getValue";
    s.push(receive, 1);
    s.setGlobal("foo");
    lua("foo(2)");
}

BOOST_AUTO_TEST_CASE(stackSetsATableValue)
{
    Lua lua;
    lua("c = {}");
    LuaStack stack(lua);
    stack.global("c").set("a", 42);
    stack.global("c").set("b", true);

    // We don't repush global because that table should
    // already be at the top of the stack; only the key
    // and value were removed
    BOOST_REQUIRE_EQUAL(42, stack.get("a").as<int>());
    stack.pop();
    BOOST_REQUIRE_EQUAL(true, stack.get("b").as<bool>());
}

BOOST_AUTO_TEST_CASE(cRetrievesBasicProperties)
{
    Lua lua;
    lua("c = {f = 42};");
    LuaStack stack(lua);
    BOOST_REQUIRE_EQUAL(stack.global("c").get("f").as<int>(), 42);
}

BOOST_AUTO_TEST_CASE(cRetrievesNestedPropertiesWithLuaStack)
{
    Lua lua;
    lua("d = {e = {f = 42} };");
    LuaStack stack(lua);
    BOOST_REQUIRE_EQUAL(stack.global("d").get("e").get("f").as<int>(), 42);
}

BOOST_AUTO_TEST_CASE(cRetrievesDeeplyNestedPropertiesWithLuaStack)
{
    Lua lua;
    lua("c = {d = {e = {f = 42} } };");
    LuaStack stack(lua);
    BOOST_REQUIRE_EQUAL(stack.global("c").get("d").get("e").get("f").as<int>(), 42);
}

BOOST_AUTO_TEST_CASE(nestedInvocations)
{
    Lua lua;

    lua["bar"] = std::function<const char*()>([&]() {
        return "bar";
    });

    lua["foo"] = std::function<QString(const QString&)>([&](const QString& internal) {
        return internal + QString("foo") + lua["bar"]().as<QString>();
    });

    BOOST_REQUIRE_EQUAL(lua("return foo('lua')").as<const char*>(), "luafoobar");
}

BOOST_AUTO_TEST_CASE(throwAnError)
{
    Lua lua;

    bool errored = false;

    try {
        lua("function foo()"
        "   someUnknownFunction();"
        "end");

        lua["foo"]();
    } catch(LuaException& ex) {
        errored = true;
    }

    BOOST_REQUIRE(errored);
}

void immediatelyThrow()
{
    throw LuaException("Intentional");
}

BOOST_AUTO_TEST_CASE(luaExceptionIsCatchableWithinLua)
{
    Lua lua;

    lua["thrower"] = immediatelyThrow;

    lua("result = not pcall(thrower);");

    BOOST_CHECK_EQUAL(lua["result"].as<bool>(), true);
}

struct Wrapper {
    int& alive;

    Wrapper(int& alive) : alive(alive)
    {
        this->alive++;
    }

    ~Wrapper()
    {
        this->alive++;
    }
};

BOOST_AUTO_TEST_CASE(luaIsBuiltWithExceptionSupport)
{
    Lua lua;

    int value = 0;
    lua["call"] = std::function<void(bool)>([&](bool shouldErr) {
        Wrapper wrapper(value);

        if (shouldErr) {
            LuaStack(lua).error("Intentional");
        }
    });

    lua["call"](false);
    BOOST_CHECK_EQUAL(value, 2);

    try {
        lua["call"](true);
    } catch (LuaException& ex) {
        // pass through
    }
    BOOST_CHECK_EQUAL(value, 4);
}

BOOST_AUTO_TEST_CASE(luaValuesCanBePassedIntoLua)
{
    Lua lua;

    lua("foo = {}");
    auto bar = lua("return function(a) end;");
    bar(lua["foo"]);
}

BOOST_AUTO_TEST_CASE(stackSavedTheRightReturnedValue)
{
    Lua lua;

    LuaStack stack(lua);

    // This extra argument is important for this test, to ensure the stack doesn't just
    // naively return the "second" argument
    lua::push(stack, "notime");

    auto worker = stack.lua()(""
    "return function(value)"
    "foo=value;"
    "end;"
    "");

    worker(42);
    BOOST_CHECK_EQUAL(lua["foo"].typestring(), "number");
    BOOST_CHECK_EQUAL(lua["foo"].as<int>(), 42);
}

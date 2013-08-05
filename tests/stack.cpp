#include "init.hpp"

#include "type/QString.hpp"
#include "type/QVariant.hpp"
#include "type/QChar.hpp"

BOOST_AUTO_TEST_CASE(testLuaStackManagesItOwnStack)
{
    LuaEnvironment lua;
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
    LuaEnvironment lua;
    LuaStack s(lua);
    s << 42 << 24;
    s.replace(-2);
    BOOST_REQUIRE_EQUAL(1, s.size());
    BOOST_REQUIRE_EQUAL(s.get<int>(), 24);
}

BOOST_AUTO_TEST_CASE(testLuaStackCanSwapValues)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    s << 1 << 2;
    // Stack is now [1, 2]

    s.swap();
    // Stack is now [2, 1]
    BOOST_REQUIRE_EQUAL(s.get<int>(), 1);
    s.pop();
    BOOST_REQUIRE_EQUAL(s.get<int>(), 2);
    s.pop();
}

BOOST_AUTO_TEST_CASE(testLuaStackCanSetGlobalValues)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    s.setGlobal("No", "Time");
    BOOST_REQUIRE_EQUAL((const char*)lua["No"], "Time");
}

BOOST_AUTO_TEST_CASE(luaStackCanBeComparedToValues)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    s << 42;

    // Truthy tests
    BOOST_REQUIRE_EQUAL(s.get<int>(), 42);

    // Falsy tests
    BOOST_REQUIRE(43 != s.get<int>());
}

BOOST_AUTO_TEST_CASE(testLuaStackHandlesNilValuesProperly)
{
    LuaEnvironment lua;
    LuaStack s(lua);

    s << lua::value::nil;
    BOOST_REQUIRE(s.isNil());
}

BOOST_AUTO_TEST_CASE(testLuaStackSupportsBitwiseOperators)
{
    LuaEnvironment lua;
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
    LuaEnvironment lua;
    LuaStack s(lua);
    s << 42;
    BOOST_REQUIRE(s.get<int>() == 42);
}

BOOST_AUTO_TEST_CASE(testStackSupportsIndexing)
{
    LuaEnvironment lua;
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
    LuaEnvironment lua;
    LuaStack(lua).setGlobal("Good", false);
    BOOST_REQUIRE_EQUAL((bool)lua["Good"], false);
    BOOST_REQUIRE(LuaStack(lua).global("Good").type() == lua::type::boolean);
}

BOOST_AUTO_TEST_CASE(testLuaStackSetsANumber)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    // Note that Lua implicitly converts these numbers
    // to a floating-point type (typically a double), so
    // number() returns a double, instead of the integer
    // that we originally passed.
    s.setGlobal("No", 42);
    BOOST_REQUIRE_EQUAL(s.global("No").get<int>(), 42);
}

BOOST_AUTO_TEST_CASE(testYouCanPushTables)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    s << lua::value::table;
    BOOST_REQUIRE("table" == s.typestring());
}

BOOST_AUTO_TEST_CASE(testLuaHandlesInterestingCharValues)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    char c = 'c';
    s.push(&c, 1);
    std::string sink;
    s >> sink;
    BOOST_REQUIRE(sink == "c");
}

BOOST_AUTO_TEST_CASE(testLuaHandlesQString)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    QString i('c');
    s << i;
    QString o;
    s >> o;
    BOOST_CHECK(o == QString("c"));
}

BOOST_AUTO_TEST_CASE(testLuaHandlesQChar)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    QChar i('c');
    s << i;
    QChar o(s.get<char>());

    BOOST_CHECK_EQUAL(o.toLatin1(), i.toLatin1());
    BOOST_CHECK(i == o);
}

BOOST_AUTO_TEST_CASE(testLuaHandlesQVariants)
{
    LuaEnvironment lua;
    lua["foo"] = QVariant(42);
    BOOST_REQUIRE(lua["foo"] == 42);
}

static void receive(LuaStack& stack)
{
    BOOST_REQUIRE_EQUAL(stack.get<const char*>(1), "getValue");
    BOOST_REQUIRE_EQUAL(stack.get<int>(2), 2);
}

BOOST_AUTO_TEST_CASE(closuresHandleStringsProperly)
{
    LuaEnvironment lua;
    LuaStack s(lua);
    s << "getValue";
    s.push(receive, 1);
    s.setGlobal("foo");
    lua::runString(s, "foo(2)");
}

BOOST_AUTO_TEST_CASE(stackSetsATableValue)
{
    LuaEnvironment lua;
    lua("c = {}");
    LuaStack stack(lua);
    stack.global("c").set("a", 42);
    stack.global("c").set("b", true);

    // We don't repush global because that table should
    // already be at the top of the stack; only the key
    // and value were removed
    BOOST_REQUIRE_EQUAL(42, stack.get("a").get<int>());
    stack.pop();
    BOOST_REQUIRE_EQUAL(true, stack.get("b").get<bool>());
}

BOOST_AUTO_TEST_CASE(cRetrievesBasicProperties)
{
    LuaEnvironment lua;
    lua::runString(lua, "c = {f = 42};");
    LuaStack stack(lua);
    BOOST_REQUIRE_EQUAL(stack.global("c").get("f").get<int>(), 42);
}

BOOST_AUTO_TEST_CASE(cRetrievesNestedPropertiesWithLuaStack)
{
    LuaEnvironment lua;
    lua("d = {e = {f = 42} };");
    LuaStack stack(lua);
    BOOST_REQUIRE_EQUAL(stack.global("d").get("e").get("f").get<int>(), 42);
}

BOOST_AUTO_TEST_CASE(cRetrievesDeeplyNestedPropertiesWithLuaStack)
{
    LuaEnvironment lua;
    lua("c = {d = {e = {f = 42} } };");
    LuaStack stack(lua);
    BOOST_REQUIRE_EQUAL(stack.global("c").get("d").get("e").get("f").get<int>(), 42);
}

BOOST_AUTO_TEST_CASE(nestedInvocations)
{
    LuaEnvironment lua;

    lua["bar"] = std::function<const char*()>([&]() {
        return "bar";
    });

    lua["foo"] = std::function<QString(const QString&)>([&](const QString& internal) {
        return internal + QString("foo") + lua["bar"]().get<QString>();
    });

    BOOST_REQUIRE_EQUAL(lua("return foo('lua')").get<const char*>(), "luafoobar");
}

BOOST_AUTO_TEST_CASE(throwAnError)
{
    LuaEnvironment lua;

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
    LuaEnvironment lua;

    lua["thrower"] = immediatelyThrow;

    lua("result = not pcall(thrower);");

    BOOST_CHECK_EQUAL(lua["result"].get<bool>(), true);
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
    LuaEnvironment lua;

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
    LuaEnvironment lua;

    lua("foo = {}");
    auto bar = lua("return function(a) end;");
    bar(lua["foo"]);
}

BOOST_AUTO_TEST_CASE(stackSavedTheRightReturnedValue)
{
    LuaEnvironment lua;

    LuaStack stack(lua);

    // This extra argument is important for this test, to ensure the stack doesn't just
    // naively return the "second" argument
    lua::push(stack, "notime");

    auto worker = lua(""
    "return function(value)"
    "foo=value;"
    "end;"
    "");

    worker(42);
    BOOST_CHECK_EQUAL(lua["foo"].typestring(), "number");
    BOOST_CHECK_EQUAL(lua["foo"].get<int>(), 42);
}

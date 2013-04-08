#include "init.hpp"

#include "userdata.hpp"

BOOST_AUTO_TEST_CASE(testLuaHandleQObjects)
{
    Lua lua;
    LuaStack s(lua);

    QObject obj;
    s.push(&obj, "QObject");

    LuaUserdata* returned;
    s >> returned;

    BOOST_REQUIRE(returned->rawData() == &obj);
}

BOOST_AUTO_TEST_CASE(testLuaHandleQObjectsWithMinimalSemantics)
{
    Lua lua;
    LuaStack stack(lua);

    auto orig = std::shared_ptr<QObject>(new QObject);
    stack << orig;

    std::shared_ptr<QObject> other;
    stack >> other;

    BOOST_REQUIRE(other.get() == orig.get());
}

LuaStack& operator<<(LuaStack& stack, Counter& ptr)
{
    stack << LuaUserdata(&ptr, "QObject");

    stack.pushMetatable();
    lua::userdata::qobject(stack, &ptr);
    stack.setMetatable();
    return stack;
}

BOOST_AUTO_TEST_CASE(luaRetrievesQObjectProperties)
{
    Lua lua;

    Counter counter(42);

    lua("function add(counter)\n"
    "    bar = counter.value;\n"
    "end");
    lua["add"](counter);

    BOOST_REQUIRE_EQUAL(lua["bar"].as<int>(), 42);
}

BOOST_AUTO_TEST_CASE(luaCanSetQObjectProperties)
{
    Lua lua;
    Counter counter(42);
    lua("function work(counter)\n"
    "    counter.value = 24;\n"
    "end");
    lua["work"](counter);

    BOOST_REQUIRE_EQUAL(counter.getValue(), 24);
}

static void receive(QObject* const ptr)
{
    if (!ptr)  {
        throw LuaException("Pointer must not be null");
    }
    static_cast<Counter*>(ptr)->setValue(24);
}

BOOST_AUTO_TEST_CASE(luaCanPassBackCxxValues)
{
    Lua lua;
    auto obj = std::shared_ptr<QObject>(new Counter(42));
    lua["obj"] = obj;

    lua["receive"] = receive;

    lua("receive(obj)");

    BOOST_REQUIRE_EQUAL(static_cast<Counter*>(obj.get())->getValue(), 24);
}

BOOST_AUTO_TEST_CASE(qobjectDynamicallyAddsPropertiesWhenNonexistent)
{
    Lua lua;
    auto obj = std::shared_ptr<QObject>(new Counter(42));
    lua["c"] = obj;

    lua("c.someValue = 24");

    BOOST_REQUIRE_EQUAL((int)lua("return c.someValue"), 24);
}

BOOST_AUTO_TEST_CASE(luaCanCallQObjectMethods)
{
    Lua lua;
    lua["c"] = std::shared_ptr<QObject>(new Counter(42));
    lua("foo = c:getValue()");
    BOOST_REQUIRE(lua["foo"] == 42);
}

BOOST_AUTO_TEST_CASE(luaCanPassValuesToQObjectMethods)
{
    Lua lua;
    Counter* counter = new Counter;
    lua["c"] = std::shared_ptr<QObject>(counter);

    lua("c:setValue(24)");
    BOOST_REQUIRE_EQUAL(counter->getValue(), 24);
}

BOOST_AUTO_TEST_CASE(luaCanPassTwoValuesToQObjectMethods)
{
    Lua lua;
    Counter* counter = new Counter;
    lua["c"] = std::shared_ptr<QObject>(counter);

    lua("c:setAddedValue(3, 6)");
    BOOST_REQUIRE_EQUAL(counter->getValue(), 9);
}

BOOST_AUTO_TEST_CASE(methodsCanUseTheStackDirectly)
{
    Lua lua;
    Counter* counter = new Counter(2);
    lua["c"] = std::shared_ptr<QObject>(counter);

    lua("c:addAll(1, 2, 3)");
    BOOST_REQUIRE_EQUAL(counter->getValue(), 8);
}

BOOST_AUTO_TEST_CASE(methodsCanStillReturnValues)
{
    Lua lua;
    lua["c"] = std::shared_ptr<QObject>(new Counter(0));

    BOOST_REQUIRE_EQUAL((int)lua("return c:summed(1, 2, 3)"), 6);
}

BOOST_AUTO_TEST_CASE(luaSetsPropertiesDirectly)
{
    Lua lua;
    QFile file(LUA_DIR "anim.lua");
    lua(file);

    auto square = new Square;

    int old = square->getX();
    lua["Tick"](std::shared_ptr<QObject>(square), M_PI);
    BOOST_REQUIRE(square->getX() != old);
}

BOOST_AUTO_TEST_CASE(stackAcceptsRawPointers)
{
    Lua lua;

    Counter counter;
    LuaStack stack(lua);
    stack << counter;
    BOOST_REQUIRE_EQUAL(stack.typestring().c_str(), "userdata");
}

BOOST_AUTO_TEST_CASE(stackAllocatedObjectsAreAccepted)
{
    Lua lua;

    lua(
    "function work(a, b)"
    "   a.value = 50;"
    "   if b then b.value = 42; end;"
    "end;");

    Counter a(42);
    lua["work"](a, Counter(53));
    lua["work"](a, a);
    lua["work"](Counter(53), a);
    lua["work"](Counter(53), Counter(42));
    lua["work"](&a, Counter(42));
    lua["work"](&a, a);
    lua["work"](a, &a);

    //BOOST_REQUIRE_EQUAL(counter.getValue(), 50);
}

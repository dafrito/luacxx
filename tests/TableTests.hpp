#include <QtTest/QtTest>
#include "Lua.hpp"
#include "loaders.hpp"
#include "LuaException.hpp"
#include "LuaStack.hpp"
#include "mocks.hpp"
#include "LuaGlobal.hpp"

using namespace std;

// XXX This is a misnomer; these tests aren't fundamentally different from those
// in BasicTests. However, they're typically more advanced since they were written
// after those in BasicTests.
class TableTests : public QObject
{
    Q_OBJECT
private slots:

    void stackSetsATableValue()
    {
        Lua lua;
        lua("c = {}");
        LuaStack stack(lua);
        stack.global("c").set("a", 42);

        // We don't repush global because that table should
        // already be at the top of the stack; only the key
        // and value were removed
        QCOMPARE(42, (int)stack.get("a"));
    }

    void cRetrievesBasicProperties()
    {
        Lua lua;
        lua("c = {f = 42};");
        LuaStack stack(lua);
        bool check = stack.global("c").get("f") == 42;
        QVERIFY(check);
        check = 42 == stack.global("c").get("f");
        QVERIFY(check);
    }

    void cRetrievesNestedPropertiesWithLuaStack()
    {
        Lua lua;
        lua("d = {e = {f = 42} };");
        LuaStack stack(lua);
        QCOMPARE((int)(stack.global("d").get("e").get("f")), 42);
    }

    void cRetrievesDeeplyNestedPropertiesWithLuaStack()
    {
        Lua lua;
        lua("c = {d = {e = {f = 42} } };");
        LuaStack stack(lua);
        QCOMPARE((int)(stack.global("c").get("d").get("e").get("f")), 42);
    }

    void luaRetrievesQObjectProperties()
    {
        Lua lua;
        Counter counter(42);
        lua["foo"] = &counter;
        QVERIFY("userdata" == lua["foo"].typestring());
        lua::load_string(lua, "bar = foo.value");
        QVERIFY(lua["bar"] == 42);
    }

    void luaCanSetQObjectProperties()
    {
        Lua lua;
        Counter counter(42);
        lua["c"] = &counter;

        lua::load_string(lua, "c.value = 24");
        QCOMPARE(counter.getValue(), 24);
    }

    void luaCanCallQObjectMethods()
    {
        Lua lua;
        Counter counter(42);
        lua["c"] = &counter;
        lua::load_string(lua, "foo = c:getValue()");
        QVERIFY(lua["foo"] == 42);
    }

    void luaCanPassValuesToQObjectMethods()
    {
        Lua lua;
        Counter counter(42);
        lua["c"] = &counter;
        lua::load_string(lua, "c:setValue(24)");
        QCOMPARE(counter.getValue(), 24);
    }

    void luaFunctionsCanBeCalledFromC()
    {
        Lua lua;
        lua(""
        "function foo(a, b)\n"
        "    return a + b\n"
        "end");
        int result = lua["foo"](42, "24");
        QVERIFY(result == 66);
    }

    void luaSetsPropertiesDirectly()
    {
        Lua lua;
        QFile file("anim.lua");
        lua(file);
        Square square;
        int old = square.getX();
        lua["Tick"](&square, M_PI);
        QVERIFY(square.getX() != old);
    }
};

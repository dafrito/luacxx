#include <QtTest/QtTest>
#include "LuaEnvironment.hpp"
#include "loaders.hpp"
#include "LuaStack.hpp"
#include "LuaValue.hpp"
#include "mocks.hpp"

using namespace std;

class LuaTests : public QObject
{
    Q_OBJECT
private slots:

    void testLuaOffersSubscriptSupportForAccessingGlobalValues()
    {
        Lua lua;
        lua("No = 'Time'");
        LuaValue g = lua["No"];
        QString str;
        g.to(str);
        QCOMPARE((const char*)lua["No"], "Time");
    }

    void testLuaOffersSubscriptSupportForGlobalValues()
    {
        Lua lua;
        LuaValue g = lua["No"];
        g = "Time";
        QCOMPARE((const char*)lua["No"], "Time");
    }

    void testLuaRunsStringsDirectly()
    {
        Lua lua;
        lua::load_string(lua, "_G['No']='Foo'");
        QCOMPARE((const char*)lua["No"], "Foo");
    }

    void testLuaValueIsAProxyForTheGlobalTable()
    {
        Lua lua;
        LuaValue v = lua["No"];
        v = "Time";
        QCOMPARE((const char*)lua["No"], "Time");
    }

    static void luaAdd(LuaStack& stack)
    {
        auto a = stack.as<int>(1);
        auto b = stack.as<int>(2);
        stack.clear();
        stack << a + b;
    }

    void testLuaCallsACFunction()
    {
        Lua lua;
        string name("luaAdd");
        lua[name] = luaAdd;
        QCOMPARE("function", lua[name].typestring().c_str());
        lua::load_string(lua, string("Bar = ") + name + "(2, 2)");
        QCOMPARE((int)lua["Bar"], 4);
    }

    static int getMagicNumber()
    {
        return 42;
    }

    void testLuaCallsAZeroParamFunction()
    {
        Lua lua;
        string name("getMagicNumber");
        lua[name] = getMagicNumber;
        QCOMPARE("function", lua[name].typestring().c_str());
        lua::load_string(lua, string("Bar = ") + name + "()");
        QVERIFY(lua["Bar"] == 42);
    }

    static int addToMagicNumber(int v)
    {
        return 42 + v;
    }

    void testLuaCallsAOneParameterFunction()
    {
        Lua lua;
        string name("addToMagicNumber");
        lua[name] = addToMagicNumber;
        QCOMPARE("function", lua[name].typestring().c_str());
        lua::load_string(lua, string("Bar = ") + name + "(2)");
        QCOMPARE((int)lua["Bar"], 44);
    }

    static double addNumbers(int a, int b)
    {
        return a + b;
    }

    void testLuaCallsATwoParameterFunction()
    {
        Lua lua;
        string name("addNumbers");
        lua[name] = addNumbers;
        QCOMPARE("function", lua[name].typestring().c_str());
        lua::load_string(lua, string("Bar = ") + name + "(2, 3)");
        QCOMPARE((int)lua["Bar"], 5);
    }

    static double addBonanza(int a, long b, float c, double d, short e)
    {
        return a+b+c+d+e;
    }

    void testLuaCallsABonanza()
    {
        Lua lua;
        string name("addBonanza");
        lua[name] = addBonanza;
        QCOMPARE("function", lua[name].typestring().c_str());
        lua::load_string(lua, string("Bar = ") + name + "(2, 3, 4, 5, 6)");
        QCOMPARE((int)lua["Bar"], 2+3+4+5+6);
    }

    static void doNothing(int)
    {
    }

    void testLuaStackCallsAVoidFunction()
    {
        Lua lua;
        string name("doNothing");
        lua[name] = doNothing;
        QVERIFY("function" == lua[name].typestring());
        lua::load_string(lua, string("Bar = ") + name + "(2)");
    }

    void testLuaCanPushClosures()
    {
        Lua lua;
        LuaStack s(lua);
        s << 42;
        s << 24;
        s.push(addNumbers, 2);
        s.setGlobal("foo");
        lua("assert(foo() == 66)");
    }

    static int subtract(int a, int b)
    {
        return a - b;
    }

    void testLuaCanPushClosuresWithMultipleArguments()
    {
        Lua lua;
        LuaStack s(lua);
        s << 42;
        s << 20;
        s.push(subtract, 2);
        s.setGlobal("foo");
        QCOMPARE((int)lua("return foo()"), 22);
    }

    void testLuaCanPushLambdas()
    {
        Lua lua;
        LuaStack s(lua);
        s << 42;
        s << 24;
        // In a perfect world, we wouldn't need to wrap the lambda inside a std::function, but
        // as far as I know, there's no way to get access the argument types of a lambda. This
        // is required for us to actually forward the function into Lua.
        s.push(std::function<int(int, int)>([](int a, int b) { return a + b; }), 2);
        s.setGlobal("foo");
        lua("assert(foo() == 66)");
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

    void luaCanReturnValuesFromEvaluatedStrings()
    {
        Lua lua;
        QCOMPARE((int)lua("return 42"), 42);
    }
};

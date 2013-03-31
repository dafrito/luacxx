#include <string>
#include <QtTest/QtTest>

#include "LuaEnvironment.hpp"
#include "loaders.hpp"
#include "LuaException.hpp"
#include "LuaStack.hpp"
#include "LuaValue.hpp"
#include "mocks.hpp"

using namespace std;

class LuaStackTests : public QObject
{
    Q_OBJECT
private slots:

    void testLuaStackManagesItOwnStack()
    {
        Lua lua;
        {
            LuaStack s(lua);
            s.global("No");
            {
                LuaStack s2(lua);
                QCOMPARE(1, s2.offset());
                s2.global("No");
                s2.global("Foo");
                QCOMPARE(2, s2.size());
            }
            // Stack is emptied when LuaStack goes out of scope.
            QCOMPARE(0, s.offset());
            QCOMPARE(1, s.size());
        }
        QCOMPARE(0, LuaStack(lua).size());
    }

    void testLuaStackCanReplaceValues()
    {
        Lua lua;
        LuaStack s(lua);
        s << 42 << 24;
        s.replace(-2);
        QCOMPARE(1, s.size());
        QCOMPARE(s.as<int>(), 24);
    }

    void testLuaStackCanSwapValues()
    {
        Lua lua;
        LuaStack s(lua);
        s << 1 << 2;
        // Stack is now [1, 2]

        s.swap();
        // Stack is now [2, 1]
        QCOMPARE(s.as<int>(), 1);
        s.pop();
        QCOMPARE(s.as<int>(), 2);
        s.pop();
    }

    void testLuaStackCanSetGlobalValues()
    {
        Lua lua;
        LuaStack s(lua);
        s.setGlobal("No", "Time");
        QCOMPARE((const char*)lua["No"], "Time");
    }

    void luaStackCanBeComparedToValues()
    {
        Lua lua;
        LuaStack s(lua);
        s << 42;
        bool equality = false;

        // Truthy tests
        QCOMPARE(s.as<int>(), 42);

        // Falsy tests
        QVERIFY(43 != s.as<int>());
    }

    void testLuaStackHandlesNilValuesProperly()
    {
        Lua lua;
        LuaStack s(lua);

        s.pushNil();
        QVERIFY(s.isNil());
    }

    void testLuaStackSupportsBitwiseOperators()
    {
        Lua lua;
        LuaStack s(lua);
        s << 42 << 34;
        int a, b;
        s >> a;
        QVERIFY(a == 34);
        s >> b;
        QVERIFY(b == 34);
    }

    void testLuaStackCanBeDirectlyCastToAValue()
    {
        Lua lua;
        LuaStack s(lua);
        s << 42;
        QVERIFY(s.as<int>() == 42);
    }

    void testStackSupportsIndexing()
    {
        Lua lua;
        LuaStack s(lua);
        s << 5 << 6 << 7;

        int a;
        int b;
        int c;
        s.begin() >> a >> b >> c;
        QCOMPARE(a, 5);
        QCOMPARE(b, 6);
        QCOMPARE(c, 7);
    }

    void testLuaStackPushesABoolean()
    {
        Lua lua;
        LuaStack(lua).setGlobal("Good", false);
        QCOMPARE((bool)lua["Good"], false);
        QCOMPARE(LuaStack(lua).global("Good").type(), lua::Type::BOOLEAN);
    }

    void testLuaStackSetsANumber()
    {
        Lua lua;
        LuaStack s(lua);
        // Note that Lua implicitly converts these numbers
        // to a floating-point type (typically a double), so
        // number() returns a double, instead of the integer
        // that we originally passed.
        s.setGlobal("No", 42);
        QCOMPARE(s.global("No").as<int>(), 42);
    }

    void testYouCanPushTables()
    {
        Lua lua;
        LuaStack s(lua);
        s.pushNewTable();
        QVERIFY("table" == s.typestring());
    }

    void testLuaHandlesInterestingCharValues()
    {
        Lua lua;
        LuaStack s(lua);
        char c = 'c';
        s.push(&c, 1);
        string sink;
        s >> sink;
        QVERIFY(sink == "c");
    }

    void testLuaHandlesQString()
    {
        Lua lua;
        LuaStack s(lua);
        QString i('c');
        s << i;
        QString o;
        s >> o;
        QVERIFY(o == "c");
    }

    void testLuaHandlesQChar()
    {
        Lua lua;
        LuaStack s(lua);
        QChar i('c');
        s << i;
        QString o;
        s >> o;
        QCOMPARE(o, QString("c"));
    }

    void testLuaHandlesQVariants()
    {
        Lua lua;
        lua["foo"] = QVariant(42);
        QVERIFY(lua["foo"] == 42);
    }

    static void receive(LuaStack& stack)
    {
        QCOMPARE(stack.as<const char*>(1), "getValue");
        QCOMPARE(stack.as<int>(2), 2);
    }

    void testLuaHandlesStringsProperly()
    {
        Lua lua;
        LuaStack s(lua);
        s << "getValue";
        s.push(receive, 1);
        s.setGlobal("foo");
        lua("foo(2)");
    }

    void stackSetsATableValue()
    {
        Lua lua;
        lua("c = {}");
        LuaStack stack(lua);
        stack.global("c").set("a", 42);

        // We don't repush global because that table should
        // already be at the top of the stack; only the key
        // and value were removed
        QCOMPARE(42, stack.get("a").as<int>());
    }

    void cRetrievesBasicProperties()
    {
        Lua lua;
        lua("c = {f = 42};");
        LuaStack stack(lua);
        QCOMPARE(stack.global("c").get("f").as<int>(), 42);
    }

    void cRetrievesNestedPropertiesWithLuaStack()
    {
        Lua lua;
        lua("d = {e = {f = 42} };");
        LuaStack stack(lua);
        QCOMPARE(stack.global("d").get("e").get("f").as<int>(), 42);
    }

    void cRetrievesDeeplyNestedPropertiesWithLuaStack()
    {
        Lua lua;
        lua("c = {d = {e = {f = 42} } };");
        LuaStack stack(lua);
        QCOMPARE(stack.global("c").get("d").get("e").get("f").as<int>(), 42);
    }
};

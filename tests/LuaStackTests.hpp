#include <string>
#include <QtTest/QtTest>

#include "LuaEnvironment.hpp"
#include "loaders.hpp"
#include "LuaException.hpp"
#include "LuaStack.hpp"
#include "LuaGlobal.hpp"
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
        QVERIFY(24 == (int)s);
    }

    void testLuaStackCanSwapValues()
    {
        Lua lua;
        LuaStack s(lua);
        s << 1 << 2;
        // Stack is now [1, 2]

        s.swap();
        // Stack is now [2, 1]
        QCOMPARE((int)s, 1);
        s.pop();
        QCOMPARE((int)s, 2);
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
        equality = 42 == s;
        QVERIFY(equality);
        equality = s == 42;
        QVERIFY(equality);

        // Falsy tests
        equality = 43 != s;
        QVERIFY(equality);
        equality = s != 43;
        QVERIFY(equality);
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
        int a = s;
        QVERIFY(a == 42);
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
        QCOMPARE((int)s.global("No").number(), 42);
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
        QVERIFY(o == "c");
    }

    void testLuaHandleQObjects()
    {
        Lua lua;
        LuaStack s(lua);
        QObject c;

        s.push(&c);

        QObject* p;
        s >> p;

        QVERIFY(p == &c);
    }

    void testLuaHandlesQVariants()
    {
        Lua lua;
        lua["foo"] = QVariant(42);
        QVERIFY(lua["foo"] == 42);
    }

    static void receive(Lua&, LuaStack& stack)
    {
        QVERIFY(QString("getValue") == stack.qstring(1));
        QVERIFY(2 == stack.number(2));
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
};

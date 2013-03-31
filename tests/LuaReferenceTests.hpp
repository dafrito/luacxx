#include <QtTest/QtTest>
#include "LuaEnvironment.hpp"
#include "LuaStack.hpp"
#include "LuaReferenceAccessible.hpp"
#include "LuaGlobalAccessible.hpp"
#include "LuaValue.hpp"

using namespace std;

class LuaReferenceTests : public QObject
{
    Q_OBJECT
private slots:

    void testLuaHandlesReferencesProperly()
    {
        Lua lua;
        LuaStack s(lua);
        s << "No Time";
        LuaValue r = s.save();
        QVERIFY(s.size() == 0);
        s << r;
        QCOMPARE(s.as<const char*>(), "No Time");
    }

    void testAccessibleCanGetAReference()
    {
        Lua lua;
        LuaReferenceAccessible accessor(lua);
        LuaStack s(lua);
        s << "No Time";
        accessor.store(s);
        QCOMPARE(s.as<const char*>(), "No Time");
        s.clear();
        accessor.push(s);
        QCOMPARE(s.as<const char*>(), "No Time");
    }

    void testAccessibleCanGetAGlobal()
    {
        Lua lua;
        LuaGlobalAccessible accessor(lua, "foo");
        LuaStack s(lua);
        s << "No Time";
        accessor.store(s);
        QCOMPARE((const char*)lua["foo"], "No Time");
        s.clear();
        accessor.push(s);
        QCOMPARE(s.as<const char*>(), "No Time");
    }

    void testLuaValueGetsALength()
    {
        Lua lua;
        lua("foo = {42, 42, 42}");
        QCOMPARE(lua["foo"].length(), 3);
    }

};

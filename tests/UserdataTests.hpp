#include <string>
#include <QtTest/QtTest>

#include "LuaEnvironment.hpp"
#include "loaders.hpp"
#include "LuaException.hpp"
#include "LuaStack.hpp"
#include "LuaValue.hpp"
#include "mocks.hpp"

#include "QObjectUserdata.hpp"

using namespace std;

class QObjectTests : public QObject
{
    Q_OBJECT
private slots:

    void testLuaHandleQObjects()
    {
        Lua lua;
        LuaStack s(lua);

        auto ptr = lua::qobjectUserdata(new QObject, "QObject");
        s.push(ptr);

        std::shared_ptr<LuaUserdata> returned;
        s >> returned;

        QVERIFY(returned.get() == ptr.get());
    }

    void luaRetrievesQObjectProperties()
    {
        Lua lua;
        Counter counter(42);
        lua["foo"] = lua::qobjectUserdata(new Counter(42), "Counter");
        QVERIFY("userdata" == lua["foo"].typestring());
        lua::load_string(lua, "bar = foo.value");
        QVERIFY(lua["bar"] == 42);
    }

    void luaCanSetQObjectProperties()
    {
        Lua lua;
        auto obj = lua::qobjectUserdata(new Counter(42), "Counter");
        lua["c"] = obj;

        lua::load_string(lua, "c.value = 24");
        QCOMPARE(static_cast<Counter*>(obj.get()->rawData())->getValue(), 24);
    }

    void luaCanCallQObjectMethods()
    {
        Lua lua;
        lua["c"] = lua::qobjectUserdata(new Counter(42), "Counter");
        lua::load_string(lua, "foo = c:getValue()");
        QVERIFY(lua["foo"] == 42);
    }

    void luaCanPassValuesToQObjectMethods()
    {
        Lua lua;
        auto obj = lua::qobjectUserdata(new Counter(42), "Counter");
        lua["c"] = obj;

        Counter* counter = static_cast<Counter>(obj.get()->rawData());

        lua::load_string(lua, "c:setValue(24)");
        QCOMPARE(counter->getValue(), 24);
    }
/*
    void luaCanPassTwoValuesToQObjectMethods()
    {
        Lua lua;
        Counter counter(2);
        lua["c"] = &counter;
        lua::load_string(lua, "c:setAddedValue(3, 6)");
        QCOMPARE(counter.getValue(), 9);
    }

    void luaCollectsGarbage()
    {
        Lua lua;
        QObject obj;
        lua["foo"] = &obj;
        lua("foo = nil");
        lua.collectGarbage();
    }

    void methodsCanUseTheStackDirectly()
    {
        Lua lua;
        Counter counter(2);
        lua["c"] = &counter;
        lua::load_string(lua, "c:addAll(1, 2, 3)");
        QCOMPARE(counter.getValue(), 8);
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
*/
};

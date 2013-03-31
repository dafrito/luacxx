#include <string>
#include <QtTest/QtTest>

#include "LuaEnvironment.hpp"
#include "loaders.hpp"
#include "LuaException.hpp"
#include "LuaStack.hpp"
#include "LuaValue.hpp"
#include "LuaUserdata.hpp"
#include "mocks.hpp"

#include "userdata.hpp"

using namespace std;

class UserdataTests : public QObject
{
    Q_OBJECT
private slots:

    void testLuaHandleQObjects()
    {
        Lua lua;
        LuaStack s(lua);

        auto ptr = std::shared_ptr<QObject>(new QObject);
        s.push(ptr, "QObject");

        LuaUserdata* returned;
        s >> returned;

        QVERIFY(returned->rawData() == ptr.get());
    }

    void testLuaHandleQObjectsWithMinimalSemantics()
    {
        Lua lua;
        LuaStack stack(lua);

        auto orig = std::shared_ptr<QObject>(new QObject);
        stack << orig;

        std::shared_ptr<QObject> other;
        stack >> other;

        QVERIFY(other.get() == orig.get());
    }

    void luaRetrievesQObjectProperties()
    {
        Lua lua;

        lua["foo"] = std::shared_ptr<QObject>(new Counter(42));

        QVERIFY("userdata" == lua["foo"].typestring());
        lua("bar = foo.value");
        QVERIFY(lua["bar"] == 42);
    }

    void luaCanSetQObjectProperties()
    {
        Lua lua;
        auto obj = std::shared_ptr<QObject>(new Counter(42));
        lua["c"] = obj;

        lua("c.value = 24");

        QCOMPARE(static_cast<Counter*>(obj.get())->getValue(), 24);
    }

    static void receive(QObject* const ptr)
    {
        if (!ptr)  {
            throw LuaException("Pointer must not be null");
        }
        static_cast<Counter*>(ptr)->setValue(24);
    }

    void luaCanPassBackCxxValues()
    {
        Lua lua;
        auto obj = std::shared_ptr<QObject>(new Counter(42));
        lua["obj"] = obj;

        lua["receive"] = receive;

        lua("receive(obj)");

        QCOMPARE(static_cast<Counter*>(obj.get())->getValue(), 24);
    }

    void qobjectDynamicallyAddsPropertiesWhenNonexistent()
    {
        Lua lua;
        auto obj = std::shared_ptr<QObject>(new Counter(42));
        lua["c"] = obj;

        lua("c.someValue = 24");

        QCOMPARE((int)lua("return c.someValue"), 24);
    }

    void luaCanCallQObjectMethods()
    {
        Lua lua;
        lua["c"] = std::shared_ptr<QObject>(new Counter(42));
        lua("foo = c:getValue()");
        QVERIFY(lua["foo"] == 42);
    }

    void luaCanPassValuesToQObjectMethods()
    {
        Lua lua;
        Counter* counter = new Counter;
        lua["c"] = std::shared_ptr<QObject>(counter);

        lua("c:setValue(24)");
        QCOMPARE(counter->getValue(), 24);
    }

    void luaCanPassTwoValuesToQObjectMethods()
    {
        Lua lua;
        Counter* counter = new Counter;
        lua["c"] = std::shared_ptr<QObject>(counter);

        lua("c:setAddedValue(3, 6)");
        QCOMPARE(counter->getValue(), 9);
    }

    void methodsCanUseTheStackDirectly()
    {
        Lua lua;
        Counter* counter = new Counter(2);
        lua["c"] = std::shared_ptr<QObject>(counter);

        lua("c:addAll(1, 2, 3)");
        QCOMPARE(counter->getValue(), 8);
    }

    void luaSetsPropertiesDirectly()
    {
        Lua lua;
        QFile file("anim.lua");
        lua(file);

        auto square = new Square;

        int old = square->getX();
        lua["Tick"](std::shared_ptr<QObject>(square), M_PI);
        QVERIFY(square->getX() != old);
    }
};

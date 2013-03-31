#include <string>
#include <QtTest/QtTest>

#include "LuaEnvironment.hpp"
#include "loaders.hpp"
#include "LuaException.hpp"
#include "LuaStack.hpp"
#include "LuaValue.hpp"
#include "mocks.hpp"
#include "table.hpp"

using namespace std;

namespace {

int addNumbers(int a, int b)
{
    return a + b;
}

} // anonymous namespace

class LuaTableTests : public QObject
{
    Q_OBJECT
private slots:

    void testPushWithInteger()
    {
        Lua lua;
        LuaStack stack(lua);

        lua("foo = {}");

        table::push(lua["foo"], 42);

        QCOMPARE((int)lua["foo"][1], 42);
    }

    void testPushWithFunction()
    {
        Lua lua;
        LuaStack stack(lua);

        lua("foo = {}");

        table::push(lua["foo"], addNumbers);

        QCOMPARE((int)lua("return foo[1](2, 2)"), 4);
    }

};

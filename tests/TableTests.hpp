#include <QtTest/QtTest>
#include "Lua.hpp"
#include "loaders.hpp"
#include "exceptions.hpp"
#include "LuaStack.hpp"
#include "mocks.hpp"

using namespace std;

class TableTests : public QObject
{
	Q_OBJECT
private slots:

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
		QCOMPARE(24, counter.getValue());
	}

};

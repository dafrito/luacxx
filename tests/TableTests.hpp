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

	void testLuaConvertsAQObjectToUserdata()
	{
		Lua lua;
		Counter counter;
		lua["foo"] = &counter;
		QVERIFY("userdata" == lua["foo"].typestring());
	}

};

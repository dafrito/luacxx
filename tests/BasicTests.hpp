#include <string>

#include <QtTest/QtTest>

#include "Lua.hpp"
#include "loaders.hpp"
#include "exceptions.hpp"
#include "LuaStack.hpp"

using namespace std;

class BasicTests : public QObject
{
	Q_OBJECT
private slots:
	void testLuaOffersSubscriptSupportForGlobalValues()
	{
		Lua lua;
		lua["No"] = "Time";
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

	void testLuaCanLoadAFileStreamIntoItsEnvironment()
	{
		Lua lua;
		lua["No"] = "Time";
		lua::load_file(lua, "tests/simple.lua");
	}

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

	void testLuaStackCanSetGlobalValues()
	{
		Lua lua;
		LuaStack s(lua);
		s.setGlobal("No", "Time");
		QCOMPARE((const char*)lua["No"], "Time");
	}

	static void luaAdd(Lua&, LuaStack& stack)
	{
		int a = stack.number(1);
		int b = stack.number(2);
		stack.clear();
		stack.push(a + b);
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
};

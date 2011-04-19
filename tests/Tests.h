#include <cxxtest/TestSuite.h>
#include <string>
#include "../Lua.hpp"
#include "../loaders.hpp"
#include "../exceptions.hpp"
#include "../LuaStack.hpp"

using namespace std;

class Tests : public CxxTest::TestSuite
{
public:
	void testLuaOffersSubscriptSupportForGlobalValues()
	{
		Lua lua;
		lua["No"] = "Time";
		TS_ASSERT_EQUALS(lua["No"], "Time");
	}

	void testLuaRunsStringsDirectly()
	{
		Lua lua;
		lua::load_string(lua, "_G['No']='Foo'");
		TS_ASSERT_EQUALS(lua["No"], "Foo");
	}

	void testLuaValueIsAProxyForTheGlobalTable()
	{
		Lua lua;
		LuaValue v = lua["No"];
		v = "Time";
		TS_ASSERT_EQUALS(lua["No"], "Time");
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
				TS_ASSERT_EQUALS(1, s2.offset());
				s2.global("No");
				s2.global("Foo");
				TS_ASSERT_EQUALS(2, s2.size());
			}
			// Stack is emptied when LuaStack goes out of scope.
			TS_ASSERT_EQUALS(0, s.offset());
			TS_ASSERT_EQUALS(1, s.size());
		}
		TS_ASSERT_EQUALS(0, LuaStack(lua).size());
	}

	void testLuaStackCanSetGlobalValues()
	{
		Lua lua;
		LuaStack s(lua);
		s.setGlobal("No", "Time");
		TS_ASSERT_EQUALS(lua["No"], "Time");
	}

	void testLuaStackHandlesNilValuesProperly()
	{
		// TODO: Figure out if/how we want to support nil values.
		//TS_ASSERT_EQUALS(nil?, s.global("No").string());
	}

	static void luaAdd(Lua& lua, LuaStack& stack)
	{
		int a = stack.number(1);
		int b = stack.number(2);
		stack.clear();
		stack.push(a + b);
	}

	void testLuaCallsACFunction()
	{
		Lua lua;
		string name("luaAdd");
		lua[name] = luaAdd;
		TS_ASSERT_EQUALS("function", lua[name].typestring());
		lua::load_string(lua, string("Bar = ") + name + "(2, 2)");
		TS_ASSERT_EQUALS(lua["Bar"], 4);
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
		TS_ASSERT_EQUALS("function", lua[name].typestring());
		lua::load_string(lua, string("Bar = ") + name + "()");
		TS_ASSERT_EQUALS(lua["Bar"], 42);
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
		TS_ASSERT_EQUALS("function", lua[name].typestring());
		lua::load_string(lua, string("Bar = ") + name + "(2)");
		TS_ASSERT_EQUALS(lua["Bar"], 44);
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
		TS_ASSERT_EQUALS("function", lua[name].typestring());
		lua::load_string(lua, string("Bar = ") + name + "(2, 3)");
		TS_ASSERT_EQUALS(lua["Bar"], 5);
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
		TS_ASSERT_EQUALS("function", lua[name].typestring());
		lua::load_string(lua, string("Bar = ") + name + "(2, 3, 4, 5, 6)");
		TS_ASSERT_EQUALS(lua["Bar"], 2+3+4+5+6);
	}

	void testLuaStackPushesABoolean()
	{
		Lua lua;
		LuaStack(lua).setGlobal("Good", false);
		TS_ASSERT_EQUALS(lua["Good"], false);
		TS_ASSERT_EQUALS(LuaStack(lua).global("Good").type(), lua::Type::BOOLEAN);
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
		TS_ASSERT_EQUALS(s.global("No").number(), 42);
	}
};

#include <cxxtest/TestSuite.h>
#include <string>
#include "../Lua.hpp"
#include <lua.hpp>
#include <fstream>
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
		lua("_G['No']='Foo'");
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
		ifstream f("tests/simple.lua", ios::in);
		TS_ASSERT(f.is_open());
		Lua lua;
		lua["No"] = "Time";
		lua(f, "tests/simple.lua");
	}

	void testLuaStackManagesItOwnStack()
	{
		Lua lua;
		TS_ASSERT_EQUALS(0, lua_gettop(lua.state));
		{
			LuaStack s(lua);
			s.global("No");
			s.global("Foo");
			TS_ASSERT_EQUALS(2, lua_gettop(lua.state));
		}
		// Stack is emptied when LuaStack goes out of scope.
		TS_ASSERT_EQUALS(0, lua_gettop(lua.state));
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
		//TS_ASSERT_EQUALS(nil?, s.global("No").string());
	}
	
	static int foo(lua_State* L)
	{
		return 0;
	}

	void testLuaStackPushesAFunction()
	{
		Lua lua;
		LuaStack s(lua);
		s.push(foo);
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

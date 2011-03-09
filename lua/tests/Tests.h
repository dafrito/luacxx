#include <cxxtest/TestSuite.h>
#include <string>
#include "../Lua.hpp"
#include <lua.hpp>
#include <fstream>

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
		lua["No"] = "Time";
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

	void testLuaSetsAValue()
	{
		Lua lua;
		lua_State *L=lua.state;
		lua_pushstring(L, "Time");
		lua_setglobal(L, "No");
		TS_ASSERT_EQUALS(0, lua_gettop(L));

		lua_getglobal(L, "No");
		TS_ASSERT_EQUALS(1, lua_gettop(L));
		TS_ASSERT_SAME_DATA(lua_tostring(L, -1), "Time", 4);
	}
};

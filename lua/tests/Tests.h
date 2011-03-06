#include <cxxtest/TestSuite.h>
#include <string>
#include "../Lua.hpp"
#include <lua.hpp>

using namespace std;

class Tests : public CxxTest::TestSuite
{
public:
	void testLuaIsInstantiated()
	{
		Lua lua;
		lua["No"] = "Time";
		TS_ASSERT(lua["No"] == "Time");
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

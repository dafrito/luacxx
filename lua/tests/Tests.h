#include <cxxtest/TestSuite.h>
#include <string>
#include "../Lua.hpp"

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

};

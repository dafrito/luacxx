#include <cxxtest/TestSuite.h>
#include "../Lua.hpp"

using namespace std;

class Tests : public CxxTest::TestSuite
{
public:
	void testLuaIsInstantiated()
	{
		Lua lua;
		TS_ASSERT_EQUALS(1, 1);
	}

};

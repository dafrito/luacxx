#include <cxxtest/TestSuite.h>

using namespace std;

class Tests : public CxxTest::TestSuite
{
public:
	void testDoNothing()
	{
		TS_ASSERT_EQUALS(2,2);
	}

};

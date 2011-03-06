#include <cxxtest/TestSuite.h>

using namespace std;

class Tests : public CxxTest::TestSuite
{
public:
	void testExactlyEqualNumbersAreEqual()
	{
		TS_ASSERT_EQUALS(1, 1);
	}

};

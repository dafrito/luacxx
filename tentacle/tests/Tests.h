#include <cxxtest/TestSuite.h>
#include "../Question.hpp"

using namespace std;

class Tests : public CxxTest::TestSuite
{
public:
	void testQuestionCanBeInstantiated()
	{
		Question q;
		TS_ASSERT_EQUALS(2,2);
	}

};

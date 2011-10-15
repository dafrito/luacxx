#include "BasicTests.hpp"

int main(int argc, char *argv[])
{
	BasicTests basic;
	QTest::qExec(&basic, argc, argv);
}

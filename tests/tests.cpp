#include "BasicTests.hpp"
#include "TableTests.hpp"

int main(int argc, char *argv[])
{
	BasicTests basic;
	QTest::qExec(&basic, argc, argv);

	TableTests tables;
	QTest::qExec(&tables, argc, argv);
}

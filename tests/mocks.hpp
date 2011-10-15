#ifndef MOCKS_HPP
#define MOCKS_HPP

#include <QObject>

class Counter : public QObject
{
	Q_OBJECT
	int b;
};

#endif // MOCKS_HPP

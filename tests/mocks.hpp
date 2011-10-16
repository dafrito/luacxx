#ifndef MOCKS_HPP
#define MOCKS_HPP

#include <QObject>

class Counter : public QObject
{
	Q_OBJECT
	int value;

	Q_PROPERTY(int value READ getValue WRITE setValue);
public slots:
	void setValue(const int value) {
		this->value = value;
	}
	int getValue() const { return value; }
public:
	Counter(int value = 0) : value(value) {}
};

#endif // MOCKS_HPP

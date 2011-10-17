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
		if (this->value != value) {
			this->value = value;
			emit valueChanged(value);
		}
	}
	int getValue() const { return value; }
signals:
	void valueChanged(int value) const;
public:
	Counter(int value = 0) : value(value) {}
};

#endif // MOCKS_HPP

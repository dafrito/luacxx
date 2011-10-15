#ifndef QLUACALLABLE_HPP
#define QLUACALLABLE_HPP

#include <QObject>
#include <functional>

class Lua;
class LuaStack;

namespace lua
{

typedef std::function<void (Lua& lua, LuaStack& stack)> LuaCallable;

class QLuaCallable : public QObject, public LuaCallable
{
	Q_OBJECT

public:
	QLuaCallable(QObject* const parent, const LuaCallable& func) :
		QObject(parent),
		LuaCallable(func)
	{}
};

}

#endif // QLUACALLABLE_HPP

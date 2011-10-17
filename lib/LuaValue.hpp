#ifndef HEADER_LUAVALUE_HPP
#define HEADER_LUAVALUE_HPP

#include <string>
#include <cstring>
#include "LuaStack.hpp"
#include "types.hpp"

using std::string;

class Lua;

class LuaValue
{
protected:
	Lua& lua;

	virtual void push(LuaStack& stack) const=0;

	lua_State* luaState() const
	{
		return lua.state;
	}
public:
	LuaValue(Lua& lua) : lua(lua) {}

	lua::Type type()
	{
		LuaStack stack(lua);
		push(stack);
		return stack.type();
	}

	string typestring()
	{
		LuaStack stack(lua);
		push(stack);
		return stack.typestring();
	}

	template <typename T>
	void to(T* value) const
	{
		LuaStack stack(lua);
		push(stack);
		stack.to(value);
	}

	template<typename T>
	operator T() const
	{
		T t;
		this->to(&t);
		return t;
	}

	template<typename T>
	bool operator==(const T& other) const
	{
		return other == static_cast<T>(*this);
	}

private:
	friend class LuaStack;
};

#endif

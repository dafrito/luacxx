#ifndef HEADER_LUAVALUE_HPP
#define HEADER_LUAVALUE_HPP

#include <string>
#include <cstring>
#include "LuaStack.hpp"
using std::string;

class Lua;

class LuaValue
{
private:
	Lua& lua;
	string key;

	void push_key();
public:
	LuaValue(Lua& lua, const string& key) :
		lua(lua), key(key) {}

	template <typename T>
	void to(T& value) const
	{
		LuaStack(lua).global(key).to(value);
	}

	template<typename T>
	operator T() const
	{
		T t;
		this->to(t);
		return t;
	}

	template<typename T>
	bool operator==(T other) const
	{
		return other == static_cast<T>(*this);
	}

	bool operator==(const char* other) const
	{
		const char* p = static_cast<const char*>(*this);
		return !std::strcmp(other, p);
	}

	template<typename T>
	const LuaValue& operator=(T value)
	{
		LuaStack(lua).setGlobal(key, value);
		return *this;
	}
};

#endif

#ifndef HEADER_LUAVALUE_HPP
#define HEADER_LUAVALUE_HPP

#include <string>
#include "LuaStack.hpp"
using std::string;

class Lua;

class LuaValue
{
private:
	Lua& lua;
	string key;

	void push_key();
	const char* char_value() const;
public:
	LuaValue(Lua& lua, const string& key) :
		lua(lua), key(key) {}

	operator const char*() const;
	operator string() const;
	operator bool() const;
	operator int() const;
	operator lua_Number() const;

	template<typename T>
	bool operator==(T other) const
	{
		return other == static_cast<T>(*this);
	}
	bool operator==(const char* other) const;

	template<typename T>
	const LuaValue& operator=(T value)
	{
		LuaStack(lua).setGlobal(key, value);
		return *this;
	}
};

#endif

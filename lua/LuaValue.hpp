#ifndef HEADER_LUAVALUE_HPP
#define HEADER_LUAVALUE_HPP

#include <string>
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

	const LuaValue& operator=(const char *value);
	bool operator==(const char* other);
	bool operator==(const string& other);
	operator const char*();
	operator string();
};

#endif

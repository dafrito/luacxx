#ifndef HEADER_LUA_HPP
#define HEADER_LUA_HPP

#include <string>
#include <lua.hpp>

using std::string;

class Lua
{
private:
public:
	// XXX make this private once testing is complete
	lua_State * state;

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
	Lua();
	~Lua();

	LuaValue operator[](const string& key);

	friend class LuaValue;
};

#endif

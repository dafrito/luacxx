#ifndef HEADER_LUASTACK_HPP
#define HEADER_LUASTACK_HPP

#include <string>

class Lua;

class LuaStack
{
private:
	Lua& lua;
	const int initialPosition;

	void checkPos(const int& pos);
	void checkSize(const int& min);
	bool isMagicalPos(const int& pos);
public:
	LuaStack(Lua& lua);
	const char* cstring(int pos = -1);
	std::string string(int pos = -1);
	lua_Number number(int pos = -1);
	LuaStack& global(const char* name);
	LuaStack& global(const std::string& name);

	LuaStack& set(const char* key, int tablePos);
	LuaStack& set(const std::string& key, int tablePos);

	LuaStack& push(const char* value);
	LuaStack& push(const std::string& value);
	LuaStack& push(const lua_Number& value);
	LuaStack& push(const bool& value);
	LuaStack& push(lua_CFunction f);

	// We need this definition since integers can be 
	// implicitly converted to booleans or numbers, which
	// is ambiguous.
	template <typename K>
	LuaStack& set(K key, int value, int tablePos)
	{
		return set<K, double>(key, value, tablePos);
	}

	template <typename K, typename V>
	LuaStack& set(K key, V value, int tablePos)
	{
		checkPos(tablePos);
		push(value);
		if (!isMagicalPos(tablePos))
			--tablePos;
		set(key, tablePos);
		return (*this);
	}

	template <typename K, typename V>
	LuaStack& setGlobal(K key, V value)
	{
		return set(key, value, LUA_GLOBALSINDEX);
	}

	~LuaStack();
};

#endif

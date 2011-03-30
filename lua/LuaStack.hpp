#ifndef HEADER_LUASTACK_HPP
#define HEADER_LUASTACK_HPP

#include <string>
#include <functional>
#include <lua.hpp>

#include "LuaFunction.hpp"

class Lua;

class LuaStack
{
private:
	static int invokeWrappedFunction(lua_State* state);

	Lua& lua;
	int _offset;

	void checkPos(int pos) const;
	bool isMagicalPos(const int& pos) const;

	LuaStack& offset(int offset);
public:
	LuaStack(Lua& lua);

	int size() const;
	bool empty() const
	{
		return size() == 0;
	}

	int offset() const
	{
		return _offset;
	}

	LuaStack& shift(int count = -1);
	LuaStack& pop(int count = 1);
	LuaStack& replace(int pos);
	LuaStack& clear()
	{
		return pop(size());
	}

	int type(int pos = -1) const;
	const char* cstring(int pos = -1);
	std::string string(int pos = -1);
	lua_Number number(int pos = -1);
	bool boolean(int pos = -1);
	LuaStack& global(const char* name);
	LuaStack& global(const std::string& name);

	LuaStack& set(const char* key, int tablePos);
	LuaStack& set(const std::string& key, int tablePos);

	LuaStack& push(const char* value);
	LuaStack& push(const std::string& value);
	LuaStack& push(const lua_Number& value);
	LuaStack& push(void* const p);
	LuaStack& push(const LuaCallable& f);
	LuaStack& push(void (*p)(Lua& lua, LuaStack& stack));
	LuaStack& push(const bool& b);
	LuaStack& push(const int& b);

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

	friend class ForwardingLuaFunction;
};

#endif

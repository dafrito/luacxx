#ifndef HEADER_LUASTACK_HPP
#define HEADER_LUASTACK_HPP

#include <string>
#include <functional>
#include <tuple>
#include <lua.hpp>
#include "types.hpp"

class Lua;
class LuaStack;

namespace
{
	template <typename RV, typename... Args>
	class LuaWrapper;
}

namespace lua
{
	typedef std::function<void (Lua& lua, LuaStack& stack)> LuaCallable;
}

using lua::LuaCallable;

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

	LuaStack& pop(int count = 1);
	LuaStack& shift(int count = 1);
	LuaStack& replace(int pos);
	LuaStack& clear()
	{
		return pop(size());
	}

	lua::Type type(int pos = -1) const;

	std::string typestring(int pos = -1) const;

	LuaStack& to(bool* sink, int pos = -1);
	LuaStack& to(lua_Number* sink, int pos = -1);
	LuaStack& to(const char** sink, int pos = -1);
	LuaStack& to(int* sink, int pos = -1);
	LuaStack& to(long* sink, int pos = -1);
	LuaStack& to(float* sink, int pos = -1);
	LuaStack& to(short* sink, int pos = -1);

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
	LuaStack& push(const long& b);
	LuaStack& push(const float& b);
	LuaStack& push(const short& b);

	template <typename RV, typename... Args>
	LuaStack& push(RV(*p)(Args...))
	{
		this->push(LuaWrapper<RV, Args...>(p));
		return (*this);
	}

	// We need this definition since integers can be 
	// implicitly converted to booleans or numbers, which
	// is ambiguous.
	template <typename K>
	LuaStack& set(K key, int value, int tablePos)
	{
		return set<K, double>(key, value, tablePos);
	}

	template <typename K, typename V>
	LuaStack& set(K key, const V& value, int tablePos)
	{
		checkPos(tablePos);
		push(value);
		if (!isMagicalPos(tablePos))
			--tablePos;
		set(key, tablePos);
		return (*this);
	}

	template <typename K, typename V>
	LuaStack& setGlobal(K key, const V& value)
	{
		return set(key, value, LUA_GLOBALSINDEX);
	}

	~LuaStack();

};

namespace
{
	/**
	 * This implementation was based off of:
	 * http://dvandyk.wordpress.com/2010/08/15/apply-functions-to-stdtuple/
	 */
	
	template <unsigned I>
	struct Filler
	{
		template <typename Tuple>
		static void fill(LuaStack& stack, Tuple& tuple)
		{
			stack.to(&std::get<I-1>(tuple));
			stack.pop();
			Filler<I-1>::fill(stack, tuple);
		}
	};

	template <>
	struct Filler<0>
	{
		template <typename Tuple>
		static void fill(LuaStack&, Tuple&)
		{}
	};

	template <typename RV, unsigned I>
	struct Chain
	{
		template <typename Function, typename Tuple, typename... Args>
		static void apply(LuaStack& stack, const Function& f, const Tuple& tuple, Args... args)
		{
			Chain<RV, I-1>::apply(stack, f, tuple, std::get<I-1>(tuple), args...);
		}
	};

	template <typename RV>
	struct Chain <RV, 0>
	{
		template <typename Function, typename Tuple, typename... Args>
		static void apply(LuaStack& stack, const Function& f, const Tuple&, Args... args)
		{
			stack.push(f(args...));
		}
	};

	template <>
	struct Chain <void, 0>
	{
		template <typename Function, typename Tuple, typename... Args>
		static void apply(LuaStack&, const Function& f, const Tuple&, Args... args)
		{
			f(args...);
		}
	};

	template <typename RV, typename... Args>
	class LuaWrapper
	{
		typedef std::tuple<Args...> ArgsTuple;
		std::function<RV(Args...)> func;

	public:
		LuaWrapper(RV(*func)(Args...)) : func(func)
		{}
	
		void operator()(Lua&, LuaStack& stack)
		{
			ArgsTuple args;
			Filler<sizeof...(Args)>::fill(stack, args);
			Chain<RV, sizeof...(Args)>::apply(stack, func, args);
		}
	};
}

#endif

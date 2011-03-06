#include "Lua.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>

using std::runtime_error;
using std::istream;

namespace {
	struct LuaReadingData
	{
		istream& stream;
		char buffer[4096];

		LuaReadingData(istream& stream) : stream(stream) {}
	};

	const char* read_stream(lua_State *L, void *data, size_t *size)
	{
		LuaReadingData* d = static_cast<LuaReadingData*>(data);
		if (!d->stream)
			return NULL;
		d->stream.read(d->buffer, 4096);
		*size = d->stream.gcount();
		return d->buffer;
	}
}


Lua::Lua()
{
	state = luaL_newstate();
	luaL_openlibs(state);
}

void Lua::operator()(istream& stream, const char* name)
{
	LuaReadingData d(stream);
	if(0 != lua_load(state, &read_stream, &d, name)) {
		throw runtime_error(lua_tostring(state, -1));
	}
	lua_call(state, 0, 0);
}

Lua::~Lua()
{
	lua_close(state);
}

const char* Lua::LuaValue::char_value() const
{
	lua_getglobal(lua.state, key.c_str());
	return lua_tostring(lua.state, -1);
}

const Lua::LuaValue& Lua::LuaValue::operator=(const char *value)
{
	lua_pushstring(lua.state, value);
	lua_setglobal(lua.state, key.c_str());
	return *this;
}

Lua::LuaValue Lua::operator[](const string& key)
{
	return Lua::LuaValue(*this, key);
}

Lua::LuaValue::operator string()
{
	return string(char_value());
}

Lua::LuaValue::operator const char*()
{
	return char_value();
}

bool Lua::LuaValue::operator==(const char* other)
{
	return !strcmp(char_value(), other);
}

bool Lua::LuaValue::operator==(const string& other)
{
	return other == char_value();
}

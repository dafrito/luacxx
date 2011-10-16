#include "Lua.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "LuaStack.hpp"
#include <QMetaObject>
#include <QMetaMethod>

using std::runtime_error;
using std::istream;

namespace {
	struct LuaReadingData
	{
		istream& stream;
		char buffer[4096];
		LuaReadingData(istream& stream) : stream(stream) {}
	};

	const char* read_stream(lua_State *, void *data, size_t *size)
	{
		LuaReadingData* d = static_cast<LuaReadingData*>(data);
		if (!d->stream)
			return NULL;
		d->stream.read(d->buffer, 4096);
		*size = d->stream.gcount();
		return d->buffer;
	}
}


/**
 * Handles Lua's __index metamethod for all light userdata.
 */
void __index(Lua&, LuaStack& stack)
{
	QObject* const obj = stack.object(1);
	if (obj == 0) {
		// No object, so just return nil.
		stack.clear();
		stack.pushNil();
		return;
	}
	const char* name = stack.cstring(2);
	if (name == 0) {
		stack.clear();
		stack.pushNil();
		return;
	}
	stack.clear();
	// First, check for properties
	QVariant propValue = obj->property(name);
	if (propValue.isValid()) {
		stack << propValue;
		return;
	}
	// Not a property, so return a method for the given the name.
	const QMetaObject* const metaObject = obj->metaObject();
	int idx = metaObject->indexOfMethod(name);
	if (idx == -1) {
		stack.pushNil();
		return;
	}
}

void __newindex(Lua&, LuaStack& stack)
{
	QObject* const obj = stack.object(1);
	if (obj == 0) {
		// No object, so just return nil.
		stack.clear();
		stack.pushNil();
		return;
	}
	const char* name = stack.cstring(2);
	if (name == 0) {
		stack.clear();
		stack.pushNil();
		return;
	}
	QVariant v;
	stack.to(&v, 3);
	obj->setProperty(name, v);
}

Lua::Lua()
{
	state = luaL_newstate();
	luaL_openlibs(state);
	{
		LuaStack stack(*this);
		lua_pushlightuserdata(state, 0);
		stack.pushNewTable();
		stack.set("__index", __index, -1);
		stack.set("__newindex", __newindex, -1);
		lua_setmetatable(state, -2);
		stack.grab();
	}
}

void Lua::operator()(istream& stream, const string& name = NULL)
{
	LuaReadingData d(stream);
	if(0 != lua_load(state, &read_stream, &d, name.c_str())) {
		throw runtime_error(lua_tostring(state, -1));
	}
	lua_call(state, 0, 0);
}

LuaValue Lua::operator[](const string& key)
{
	return LuaValue(*this, key);
}

Lua::~Lua()
{
	lua_close(state);
}

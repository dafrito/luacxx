#ifndef luacxx_QDataStream_INCLUDED
#define luacxx_QDataStream_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QDataStream>

LUA_METATABLE_BUILT(QDataStream)
LUA_METATABLE_ENUM(QDataStream::Status)
LUA_METATABLE_ENUM(QDataStream::ByteOrder)
LUA_METATABLE_ENUM(QDataStream::FloatingPointPrecision)
LUA_METATABLE_ENUM(QDataStream::Version)

extern "C" int luaopen_luacxx_QDataStream(lua_State* const);

#endif // luacxx_QDataStream_INCLUDED

#ifndef luacxx_QSsl_INCLUDED
#define luacxx_QSsl_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QSsl>

LUA_METATABLE_ENUM(QSsl::AlternativeNameEntryType);
LUA_METATABLE_ENUM(QSsl::EncodingFormat);
LUA_METATABLE_ENUM(QSsl::KeyAlgorithm);
LUA_METATABLE_ENUM(QSsl::KeyType);
LUA_METATABLE_ENUM(QSsl::SslOption);
LUA_METATABLE_ENUM(QSsl::SslProtocol);

extern "C" int luaopen_luacxx_QSsl(lua_State* const);

#endif // luacxx_QSsl_INCLUDED

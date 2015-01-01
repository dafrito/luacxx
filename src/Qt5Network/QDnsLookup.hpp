#ifndef luacxx_QDnsLookup_INCLUDED
#define luacxx_QDnsLookup_INCLUDED

#include "../stack.hpp"
#include "../enum.hpp"

#include <QDnsLookup>
#include "../Qt5Core/QObject.hpp"

// http://doc.qt.io/qt-5/qdnslookup.html

LUA_METATABLE_INHERIT(QDnsLookup, QObject)
LUA_METATABLE_ENUM(QDnsLookup::Error)
LUA_METATABLE_ENUM(QDnsLookup::Type)

extern "C" int luaopen_luacxx_QDnsLookup(lua_State* const);

#endif // luacxx_QDnsLookup_INCLUDED

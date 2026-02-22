#ifndef luacxx_QDnsTextRecord_INCLUDED
#define luacxx_QDnsTextRecord_INCLUDED

#include "../stack.hpp"

#include <QDnsTextRecord>

// http://doc.qt.io/qt-5/qdnstextrecord.html

LUA_METATABLE_BUILT(QDnsTextRecord)

extern "C" int luaopen_Qt5Network_QDnsTextRecord(lua_State* const);

#endif // luacxx_QDnsTextRecord_INCLUDED

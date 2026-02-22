#ifndef luacxx_QDnsServiceRecord_INCLUDED
#define luacxx_QDnsServiceRecord_INCLUDED

#include "../stack.hpp"

#include <QDnsServiceRecord>

// http://doc.qt.io/qt-5/qdnsservicerecord.html

LUA_METATABLE_BUILT(QDnsServiceRecord)

extern "C" int luaopen_Qt5Network_QDnsServiceRecord(lua_State* const);

#endif // luacxx_QDnsServiceRecord_INCLUDED

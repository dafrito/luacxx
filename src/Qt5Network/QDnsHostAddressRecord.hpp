#ifndef luacxx_QDnsHostAddressRecord_INCLUDED
#define luacxx_QDnsHostAddressRecord_INCLUDED

#include "../stack.hpp"

#include <QDnsHostAddressRecord>

// http://doc.qt.io/qt-5/qdnshostaddressrecord.html

LUA_METATABLE_BUILT(QDnsHostAddressRecord)

extern "C" int luaopen_Qt5Network_QDnsHostAddressRecord(lua_State* const);

#endif // luacxx_QDnsHostAddressRecord_INCLUDED

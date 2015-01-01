#ifndef luacxx_QDnsDomainNameRecord_INCLUDED
#define luacxx_QDnsDomainNameRecord_INCLUDED

#include "../stack.hpp"

#include <QDnsDomainNameRecord>

// http://doc.qt.io/qt-5/qdnsdomainnamerecord.html

LUA_METATABLE_BUILT(QDnsDomainNameRecord)

extern "C" int luaopen_Qt5Network_QDnsDomainNameRecord(lua_State* const);

#endif // luacxx_QDnsDomainNameRecord_INCLUDED

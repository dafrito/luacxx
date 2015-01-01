#ifndef luacxx_QDnsMailExchangeRecord_INCLUDED
#define luacxx_QDnsMailExchangeRecord_INCLUDED

#include "../stack.hpp"

#include <QDnsMailExchangeRecord>

LUA_METATABLE_BUILT(QDnsMailExchangeRecord)

extern "C" int luaopen_Qt5Network_QDnsMailExchangeRecord(lua_State* const);

#endif // luacxx_QDnsMailExchangeRecord_INCLUDED

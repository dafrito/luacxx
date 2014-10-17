#ifndef luacxx_QSslCertificate_INCLUDED
#define luacxx_QSslCertificate_INCLUDED

#include "../stack.hpp"

class QSslCertificate;

LUA_METATABLE_BUILT(QSslCertificate);

extern "C" int luaopen_luacxx_QSslCertificate(lua_State* const);

#endif // luacxx_QSslCertificate_INCLUDED

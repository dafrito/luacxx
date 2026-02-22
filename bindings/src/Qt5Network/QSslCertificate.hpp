#ifndef luacxx_QSslCertificate_INCLUDED
#define luacxx_QSslCertificate_INCLUDED

#include "Qt5Network.hpp"
#include "../enum.hpp"

#include <QSslCertificate>

LUA_METATABLE_BUILT(QSslCertificate);
LUA_METATABLE_ENUM(QSslCertificate::SubjectInfo);

extern "C" int luaopen_Qt5Network_QSslCertificate(lua_State* const);

#endif // luacxx_QSslCertificate_INCLUDED

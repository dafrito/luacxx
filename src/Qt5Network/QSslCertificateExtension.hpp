#ifndef luacxx_QSslCertificateExtension_INCLUDED
#define luacxx_QSslCertificateExtension_INCLUDED

#include "Qt5Network.hpp"

#include <QSslCertificateExtension>

LUA_METATABLE_BUILT(QSslCertificateExtension);

bool operator==(const QSslCertificateExtension& first, const QSslCertificateExtension& second);

extern "C" int luaopen_luacxx_QSslCertificateExtension(lua_State* const);

#endif // luacxx_QSslCertificateExtension_INCLUDED

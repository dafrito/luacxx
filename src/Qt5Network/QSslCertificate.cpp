#include "QSslCertificate.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QSslCertificate>

#include "../Qt5Core/QCryptographicHash.hpp"
#include "../Qt5Core/QByteArray.hpp"
#include "../Qt5Core/QDateTime.hpp"
#include "QSslCertificateExtension.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QStringList.hpp"
#include "../Qt5Core/QList.hpp"
#include "QSslKey.hpp"
#include "QSsl.hpp"

int QSslCertificate_issuerInfo(lua_State* const state)
{
    return 0;
}
int QSslCertificate_subjectInfo(lua_State* const state)
{
    return 0;
}

void lua::QSslCertificate_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["clear"] = &QSslCertificate::clear;
    mt["digest"] = &QSslCertificate::digest;
    mt["effectiveDate"] = &QSslCertificate::effectiveDate;
    mt["expiryDate"] = &QSslCertificate::expiryDate;
    mt["extensions"] = &QSslCertificate::extensions;
    mt["handle"] = &QSslCertificate::handle;
    mt["isBlacklisted"] = &QSslCertificate::isBlacklisted;
    mt["isNull"] = &QSslCertificate::isNull;
    mt["issuerInfo"] = QSslCertificate_issuerInfo;
    mt["issuerInfoAttributes"] = &QSslCertificate::issuerInfoAttributes;
    mt["publicKey"] = &QSslCertificate::publicKey;
    mt["serialNumber"] = &QSslCertificate::serialNumber;
    mt["subjectAlternativeNames"] = &QSslCertificate::subjectAlternativeNames;
    mt["subjectInfo"] = QSslCertificate_subjectInfo;
    mt["subjectInfoAttributes"] = &QSslCertificate::subjectInfoAttributes;
    mt["swap"] = &QSslCertificate::swap;
    mt["toDer"] = &QSslCertificate::toDer;
    mt["toPem"] = &QSslCertificate::toPem;
    mt["toText"] = &QSslCertificate::toText;
    mt["version"] = &QSslCertificate::version;
}

int QSslCertificate_new(lua_State* const state)
{
    // QSslCertificate(QIODevice * device, QSsl::EncodingFormat format = QSsl::Pem)
    // QSslCertificate(const QByteArray & data = QByteArray(), QSsl::EncodingFormat format = QSsl::Pem)
    // QSslCertificate(const QSslCertificate & other)
    lua::make<QSslCertificate>(state);
    // TODO Set up object-specific methods

    return 1;
}

int QSslCertificate_fromData(lua_State* const state)
{
    return 0;
}
int QSslCertificate_fromDevice(lua_State* const state)
{
    return 0;
}
int QSslCertificate_fromPath(lua_State* const state)
{
    return 0;
}
int QSslCertificate_verify(lua_State* const state)
{
    return 0;
}

int luaopen_luacxx_QSslCertificate(lua_State* const state)
{
    lua::thread env(state);

    env["QSslCertificate"] = lua::value::table;
    env["QSslCertificate"]["new"] = QSslCertificate_new;
    auto t = env["QSslCertificate"];

    // enum QSslCertificate::SubjectInfo
    t["Organization"] = QSslCertificate::Organization;
    t["CommonName"] = QSslCertificate::CommonName;
    t["LocalityName"] = QSslCertificate::LocalityName;
    t["OrganizationalUnitName"] = QSslCertificate::OrganizationalUnitName;
    t["CountryName"] = QSslCertificate::CountryName;
    t["StateOrProvinceName"] = QSslCertificate::StateOrProvinceName;
    t["DistinguishedNameQualifier"] = QSslCertificate::DistinguishedNameQualifier;
    t["SerialNumber"] = QSslCertificate::SerialNumber;
    t["EmailAddress"] = QSslCertificate::EmailAddress;

    t["fromData"] = QSslCertificate_fromData;
    t["fromDevice"] = QSslCertificate_fromDevice;
    t["fromPath"] = QSslCertificate_fromPath;
    t["verify"] = QSslCertificate_verify;

    return 0;
}

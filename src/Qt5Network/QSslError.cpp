#include "QSslError.hpp"
#include "../thread.hpp"

#include "QSslCertificate.hpp"

void lua::QSslError_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["certificate"] = &QSslError::certificate;
    mt["error"] = &QSslError::error;
    mt["errorString"] = &QSslError::errorString;
    mt["swap"] = &QSslError::swap;
}

int QSslError_new(lua_State* const state)
{
    if (lua::is_type<QSslError>(state, 2)) {
        // QSslError(const QSslError & other)
        lua::make<QSslError>(state, lua::get<const QSslError&>(state, 2));
    } else if (lua::size(state) == 3) {
        // QSslError(SslError error, const QSslCertificate & certificate)
        lua::make<QSslError>(state,
            lua::get<QSslError::SslError>(state, 2),
            lua::get<const QSslCertificate&>(state, 3)
        );
    } else if (lua::size(state) == 2) {
        // QSslError()
        lua::make<QSslError>(state);
    } else {
        // QSslError(SslError error)
        lua::make<QSslError>(state, lua::get<QSslError::SslError>(state, 2));
    }

    return 1;
}

int luaopen_Qt5Network_QSslError(lua_State* const state)
{
    lua::thread env(state);

    env["QSslError"] = lua::value::table;
    env["QSslError"]["new"] = QSslError_new;
    auto t = env["QSslError"];

    // enum QSslError::SslError
    t["NoError"] = QSslError::NoError;
    t["UnableToGetIssuerCertificate"] = QSslError::UnableToGetIssuerCertificate;
    t["UnableToDecryptCertificateSignature"] = QSslError::UnableToDecryptCertificateSignature;
    t["UnableToDecodeIssuerPublicKey"] = QSslError::UnableToDecodeIssuerPublicKey;
    t["CertificateSignatureFailed"] = QSslError::CertificateSignatureFailed;
    t["CertificateNotYetValid"] = QSslError::CertificateNotYetValid;
    t["CertificateExpired"] = QSslError::CertificateExpired;
    t["InvalidNotBeforeField"] = QSslError::InvalidNotBeforeField;
    t["InvalidNotAfterField"] = QSslError::InvalidNotAfterField;
    t["SelfSignedCertificate"] = QSslError::SelfSignedCertificate;
    t["SelfSignedCertificateInChain"] = QSslError::SelfSignedCertificateInChain;
    t["UnableToGetLocalIssuerCertificate"] = QSslError::UnableToGetLocalIssuerCertificate;
    t["UnableToVerifyFirstCertificate"] = QSslError::UnableToVerifyFirstCertificate;
    t["CertificateRevoked"] = QSslError::CertificateRevoked;
    t["InvalidCaCertificate"] = QSslError::InvalidCaCertificate;
    t["PathLengthExceeded"] = QSslError::PathLengthExceeded;
    t["InvalidPurpose"] = QSslError::InvalidPurpose;
    t["CertificateUntrusted"] = QSslError::CertificateUntrusted;
    t["CertificateRejected"] = QSslError::CertificateRejected;
    t["SubjectIssuerMismatch"] = QSslError::SubjectIssuerMismatch;
    t["AuthorityIssuerSerialNumberMismatch"] = QSslError::AuthorityIssuerSerialNumberMismatch;
    t["NoPeerCertificate"] = QSslError::NoPeerCertificate;
    t["HostNameMismatch"] = QSslError::HostNameMismatch;
    t["UnspecifiedError"] = QSslError::UnspecifiedError;
    t["NoSslSupport"] = QSslError::NoSslSupport;
    t["CertificateBlacklisted"] = QSslError::CertificateBlacklisted;

    return 0;
}

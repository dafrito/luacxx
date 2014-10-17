#include "QSsl.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QSsl>

int luaopen_luacxx_QSsl(lua_State* const state)
{
    lua::thread env(state);

    env["QSsl"] = lua::value::table;
    env["QSsl"]["new"] = QSsl_new;
    auto t = env["QSsl"];

    // enum QSsl::AlternativeNameEntryType
    t["EmailEntry"] = QSsl::EmailEntry;
    t["DnsEntry"] = QSsl::DnsEntry;

    // enum QSsl::EncodingFormat
    t["Pem"] = QSsl::Pem;
    t["Der"] = QSsl::Der;


    // enum QSsl::KeyAlgorithm
    t["Rsa"] = QSsl::Rsa;
    t["Dsa"] = QSsl::Dsa;
    t["Opaque"] = QSsl::Opaque;

    // enum QSsl::KeyType
    t["PrivateKey"] = QSsl::PrivateKey;
    t["PublicKey"] = QSsl::PublicKey;

    // enum QSsl::SslOption
    t["SslOptionDisableEmptyFragments"] = QSsl::SslOptionDisableEmptyFragments;
    t["SslOptionDisableSessionTickets"] = QSsl::SslOptionDisableSessionTickets;
    t["SslOptionDisableCompression"] = QSsl::SslOptionDisableCompression;
    t["SslOptionDisableServerNameIndication"] = QSsl::SslOptionDisableServerNameIndication;
    t["SslOptionDisableLegacyRenegotiation"] = QSsl::SslOptionDisableLegacyRenegotiation;
    t["SslOptionDisableSessionSharing"] = QSsl::SslOptionDisableSessionSharing;
    t["SslOptionDisableSessionPersistence"] = QSsl::SslOptionDisableSessionPersistence;

    // enum QSsl::SslProtocol
    t["SslV3"] = QSsl::SslV3;
    t["SslV2"] = QSsl::SslV2;
    t["TlsV1_0"] = QSsl::TlsV1_0;
    t["TlsV1"] = QSsl::TlsV1;
    t["TlsV1_1"] = QSsl::TlsV1_1;
    t["TlsV1_2"] = QSsl::TlsV1_2;
    t["UnknownProtocol"] = QSsl::UnknownProtocol;
    t["AnyProtocol"] = QSsl::AnyProtocol;
    t["TlsV1SslV3"] = QSsl::TlsV1SslV3;
    t["SecureProtocols"] = QSsl::SecureProtocols;

    return 0;
}

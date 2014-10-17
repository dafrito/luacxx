#include "QSslKey.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QSslKey>

#include "../Qt5Core/QByteArray.hpp"
#include "../Qt5Core/Qt.hpp"
#include "QSsl.hpp"

int QSslKey_toDer(lua_State* const state)
{
    return 0;
}
int QSslKey_toPem(lua_State* const state)
{
    return 0;
}

void lua::QSslKey_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["algorithm"] = &QSslKey::algorithm;
    mt["clear"] = &QSslKey::clear;
    mt["handle"] = &QSslKey::handle;
    mt["isNull"] = &QSslKey::isNull;
    mt["length"] = &QSslKey::length;
    mt["swap"] = &QSslKey::swap;
    mt["toDer"] = QSslKey_toDer;
    mt["toPem"] = QSslKey_toPem;
    mt["type"] = &QSslKey::type;
}

int QSslKey_new(lua_State* const state)
{
    // QSslKey()
    // QSslKey(const QByteArray & encoded, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat encoding = QSsl::Pem, QSsl::KeyType type = QSsl::PrivateKey, const QByteArray & passPhrase = QByteArray())
    // QSslKey(QIODevice * device, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat encoding = QSsl::Pem, QSsl::KeyType type = QSsl::PrivateKey, const QByteArray & passPhrase = QByteArray())
    // QSslKey(Qt::HANDLE handle, QSsl::KeyType type = QSsl::PrivateKey)
    // QSslKey(const QSslKey & other)
    lua::make<QSslKey>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QSslKey(lua_State* const state)
{
    lua::thread env(state);

    env["QSslKey"] = lua::value::table;
    env["QSslKey"]["new"] = QSslKey_new;
    auto t = env["QSslKey"];

    return 0;
}

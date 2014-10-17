#include "QSslCipher.hpp"
#include "../thread.hpp"

#include "QSsl.hpp"

void lua::QSslCipher_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["authenticationMethod"] = &QSslCipher::authenticationMethod;
    mt["encryptionMethod"] = &QSslCipher::encryptionMethod;
    mt["isNull"] = &QSslCipher::isNull;
    mt["keyExchangeMethod"] = &QSslCipher::keyExchangeMethod;
    mt["name"] = &QSslCipher::name;
    mt["protocol"] = &QSslCipher::protocol;
    mt["protocolString"] = &QSslCipher::protocolString;
    mt["supportedBits"] = &QSslCipher::supportedBits;
    mt["swap"] = &QSslCipher::swap;
    mt["usedBits"] = &QSslCipher::usedBits;
}

int QSslCipher_new(lua_State* const state)
{
    // QSslCipher()
    // QSslCipher(const QString & name)
    // QSslCipher(const QString & name, QSsl::SslProtocol protocol)
    // QSslCipher(const QSslCipher & other)
    lua::make<QSslCipher>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QSslCipher(lua_State* const state)
{
    lua::thread env(state);

    env["QSslCipher"] = lua::value::table;
    env["QSslCipher"]["new"] = QSslCipher_new;
    auto t = env["QSslCipher"];

    return 0;
}

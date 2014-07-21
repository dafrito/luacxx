#include "QCryptographicHash.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QByteArray.hpp"

#include <QCryptographicHash>

int QCryptographicHash_addData(lua_State* const state)
{
    auto self = lua::get<QCryptographicHash*>(state, 1);
    if (lua::class_name(state, 2) == lua::Metatable<QByteArray>::name) {
        self->addData(lua::get<const QByteArray&>(state, 2));
        return 0;
    }
    if (lua_type(state, 2) == LUA_TUSERDATA) {
        self->addData(lua::get<QIODevice*>(state, 2));
        return 0;
    }
    if (lua_type(state, 2) == LUA_TSTRING) {
        self->addData(lua::get<const char*>(state, 2), lua::get<int>(state, 3));
    }
    return 0;
}

void lua::QCryptographicHash_metatable(const lua::index& mt)
{
    mt["addData"] = QCryptographicHash_addData;
    mt["reset"] = &QCryptographicHash::reset;
    mt["result"] = &QCryptographicHash::result;
}

int QCryptographicHash_new(lua_State* const state)
{
    lua::make<QCryptographicHash>(state, lua::get<QCryptographicHash::Algorithm>(state, 2));
    return 1;
}

int luaopen_Qt5Core_QCryptographicHash(lua_State* const state)
{
    lua::thread env(state);

    env["QCryptographicHash"] = lua::value::table;
    env["QCryptographicHash"]["new"] = QCryptographicHash_new;
    env["QCryptographicHash"]["hash"] = &QCryptographicHash::hash;
    auto t = env["QCryptographicHash"];

    // enum QCryptographicHash::Algorithm
    t["Md4"] = QCryptographicHash::Md4;
    t["Md5"] = QCryptographicHash::Md5;
    t["Sha1"] = QCryptographicHash::Sha1;
    t["Sha224"] = QCryptographicHash::Sha224;
    t["Sha256"] = QCryptographicHash::Sha256;
    t["Sha384"] = QCryptographicHash::Sha384;
    t["Sha512"] = QCryptographicHash::Sha512;
    t["Sha3_224"] = QCryptographicHash::Sha3_224;
    t["Sha3_256"] = QCryptographicHash::Sha3_256;
    t["Sha3_384"] = QCryptographicHash::Sha3_384;
    t["Sha3_512"] = QCryptographicHash::Sha3_512;

    return 0;
}

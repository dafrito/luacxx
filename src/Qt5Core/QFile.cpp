#include "QFile.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QFile>
#include "QFileDevice.hpp"
#include "QByteArray.hpp"
#include "QFlags.hpp"

int QFile_open(lua_State* const state)
{
    return 0;
}

void lua::QFile_metatable(lua_State* const state, const int pos)
{
    lua::QFileDevice_metatable(state, pos);

    lua::index mt(state, pos);
    mt["copy"] = static_cast<bool(QFile::*)(const QString&)>(&QFile::copy);
    mt["exists"] = static_cast<bool(QFile::*)() const>(&QFile::exists);
    mt["link"] = static_cast<bool(QFile::*)(const QString&)>(&QFile::link);
    mt["open"] = QFile_open;
    mt["remove"] = static_cast<bool(QFile::*)()>(&QFile::remove);
    mt["rename"] = static_cast<bool(QFile::*)(const QString&)>(&QFile::rename);
    mt["setFileName"] = &QFile::setFileName;
    mt["symLinkTarget"] = static_cast<QString(QFile::*)() const>(&QFile::symLinkTarget);
}

int QFile_new(lua_State* const state)
{
    // QFile(const QString & name)
    // QFile(QObject * parent)
    // QFile(const QString & name, QObject * parent)
    lua::make<QFile>(state);

    return 1;
}

int QFile_copy(lua_State* const state)
{
    return 0;
}

int QFile_decodeName(lua_State* const state)
{
    return 0;
}

int luaopen_luacxx_QFile(lua_State* const state)
{
    lua::thread env(state);

    env["QFile"] = lua::value::table;
    env["QFile"]["new"] = QFile_new;
    auto t = env["QFile"];

    t["copy"] = QFile_copy;
    t["decodeName"] = QFile_decodeName;
    t["encodeName"] = &QFile::encodeName;
    t["exists"] = static_cast<bool(*)(const QString&)>(&QFile::exists);
    t["link"] = static_cast<bool(*)(const QString&, const QString&)>(&QFile::link);
    t["permissions"] = static_cast<QFileDevice::Permissions(*)(const QString&)>(&QFile::permissions);
    t["remove"] = static_cast<bool(*)(const QString&)>(&QFile::remove);
    t["rename"] = static_cast<bool(*)(const QString&, const QString&)>(&QFile::rename);
    t["resize"] = static_cast<bool(*)(const QString&, qint64)>(&QFile::resize);
    t["setPermissions"] = static_cast<bool(*)(const QString&, QFileDevice::Permissions)>(&QFile::setPermissions);
    t["symLinkTarget"] = static_cast<QString(*)(const QString&)>(&QFile::symLinkTarget);

    return 0;
}

#include "QFile.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QFile>
#include "QFileDevice.hpp"
#include "QByteArray.hpp"
#include "QFlags.hpp"
#include "QObject.hpp"
#include "QIODevice.hpp"

int QFile_open(lua_State* const state)
{
    auto self = lua::get<QFile*>(state, 1);

    if (lua_gettop(state) == 1) {
        lua::push(state, self->open(lua::get<QIODevice::OpenMode>(state, 2)));
    } else if (lua_isnumber(state, 2)) {
        // bool    open(int fd, OpenMode mode, FileHandleFlags handleFlags = DontCloseHandle)
        if (lua_gettop(state) > 3) {
            lua::push(state, self->open(
                lua::get<int>(state, 2),
                lua::get<QIODevice::OpenMode>(state, 3),
                lua::get<QFileDevice::FileHandleFlags>(state, 4)
            ));
        } else {
            lua::push(state, self->open(
                lua::get<int>(state, 2),
                lua::get<QIODevice::OpenMode>(state, 3)
            ));
        }
/*    } else {
        // TODO Uncomment once a binding for FILE* has been added
        // bool    open(FILE * fh, OpenMode mode, FileHandleFlags handleFlags = DontCloseHandle)
        if (lua_gettop(state) > 3) {
            lua::push(state, self->open(
                lua::get<FILE*>(state, 2),
                lua::get<QIODevice::OpenMode>(state, 3),
                lua::get<QFileDevice::FileHandleFlags>(state, 4)
            ));
        } else {
            lua::push(state, self->open(
                lua::get<FILE*>(state, 2),
                lua::get<QIODevice::OpenMode>(state, 3)
            ));
        }*/
    }
    return 1;
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
    if (lua_gettop(state) == 0) {
        // QFile()
        lua::push(state, new QFile);
    } else if (lua::is_type<QString>(state, 1) || lua_type(state, 1) == LUA_TSTRING) {
        // QFile(const QString & name)
        lua::push(state, new QFile(lua::get<QString>(state, 1)));
    } else if (lua_gettop(state) == 2) {
        // QFile(const QString & name, QObject * parent)
        lua::push(state, new QFile(
            lua::get<QString>(state, 1),
            lua::get<QObject*>(state, 2)
        ));
    } else {
        // QFile(QObject * parent)
        lua::push(state, new QFile(lua::get<QObject*>(state, 1)));
    }

    return 1;
}

int static_QFile_copy(lua_State* const state)
{
    // bool     copy(const QString & fileName, const QString & newName)
    lua::push(state, QFile::copy(
        lua::get<QString>(state, 1),
        lua::get<QString>(state, 2)
    ));
    return 1;
}

int static_QFile_decodeName(lua_State* const state)
{
    if (lua::is_type<QByteArray>(state, 1)) {
        //  QString     decodeName(const QByteArray & localFileName)
        lua::push(state, QFile::decodeName(lua::get<const QByteArray&>(state, 1)));
    } else {
        //  QString     decodeName(const char * localFileName)
        lua::push(state, QFile::decodeName(lua::get<const char*>(state, 1)));
    }
    return 1;
}

int luaopen_Qt5Core_QFile(lua_State* const state)
{
    lua::thread env(state);

    env["QFile"] = lua::value::table;
    env["QFile"]["new"] = QFile_new;
    auto t = env["QFile"];

    t["copy"] = static_QFile_copy;
    t["decodeName"] = static_QFile_decodeName;
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

#include "QIODevice.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QFlags.hpp"
#include "QByteArray.hpp"
#include "QObject.hpp"

// https://qt-project.org/doc/qt-5/qiodevice.html

int QIODevice_getChar(lua_State* const state)
{
    return 0;
}

int QIODevice_peek(lua_State* const state)
{
    return 0;
}

int QIODevice_read(lua_State* const state)
{
    return 0;
}

int QIODevice_readLine(lua_State* const state)
{
    return 0;
}

int QIODevice_write(lua_State* const state)
{
    return 0;
}

void lua::QIODevice_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);

    mt["atEnd"] = &QIODevice::atEnd;
    mt["bytesAvailable"] = &QIODevice::bytesAvailable;
    mt["bytesToWrite"] = &QIODevice::bytesToWrite;
    mt["canReadLine"] = &QIODevice::canReadLine;
    mt["close"] = &QIODevice::close;
    mt["errorString"] = &QIODevice::errorString;
    mt["getChar"] = QIODevice_getChar;
    mt["isOpen"] = &QIODevice::isOpen;
    mt["isReadable"] = &QIODevice::isReadable;
    mt["isSequential"] = &QIODevice::isSequential;
    mt["isTextModeEnabled"] = &QIODevice::isTextModeEnabled;
    mt["isWritable"] = &QIODevice::isWritable;
    mt["open"] = &QIODevice::open;
    mt["openMode"] = &QIODevice::openMode;
    mt["peek"] = QIODevice_peek;
    mt["pos"] = &QIODevice::pos;
    mt["putChar"] = &QIODevice::putChar;
    mt["read"] = QIODevice_read;
    mt["readAll"] = &QIODevice::readAll;
    mt["readLine"] = QIODevice_readLine;
    mt["reset"] = &QIODevice::reset;
    mt["seek"] = &QIODevice::seek;
    mt["setTextModeEnabled"] = &QIODevice::setTextModeEnabled;
    mt["size"] = &QIODevice::size;
    mt["ungetChar"] = &QIODevice::ungetChar;
    mt["waitForBytesWritten"] = &QIODevice::waitForBytesWritten;
    mt["waitForReadyRead"] = &QIODevice::waitForReadyRead;
    mt["write"] = QIODevice_write;
}

int luaopen_Qt5Core_QIODevice(lua_State* const state)
{
    lua::thread env(state);

    env["QIODevice"] = lua::value::table;
    auto t = env["QIODevice"];

    // enum QIODevice::OpenModeFlag
    t["NotOpen"] = QIODevice::NotOpen;
    t["ReadOnly"] = QIODevice::ReadOnly;
    t["WriteOnly"] = QIODevice::WriteOnly;
    t["ReadWrite"] = QIODevice::ReadWrite;
    t["Append"] = QIODevice::Append;
    t["Truncate"] = QIODevice::Truncate;
    t["Text"] = QIODevice::Text;
    t["Unbuffered"] = QIODevice::Unbuffered;

    return 0;
}


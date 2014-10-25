#include "QDataStream.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QIODevice.hpp"

// QDataStream & QDataStream::readBytes(char *& s, uint & l)
int QDataStream_readBytes(lua_State* const state)
{
    return 0;
}

// int QDataStream::readRawData(char * s, int len)
int QDataStream_readRawData(lua_State* const state)
{
    return 0;
}

// QDataStream & QDataStream::writeBytes(const char * s, uint len)
int QDataStream_writeBytes(lua_State* const state)
{
    auto self = lua::get<QDataStream*>(state, 1);
    self->writeBytes(
        lua::get<const char*>(state, 2),
        lua::get<unsigned int>(state, 3)
    );
    lua_settop(state, 1);
    return 1;
}

namespace lua {

void QDataStream_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["atEnd"] = &QDataStream::atEnd;
    mt["byteOrder"] = &QDataStream::byteOrder;
    mt["device"] = &QDataStream::device;
    mt["floatingPointPrecision"] = &QDataStream::floatingPointPrecision;
    mt["readBytes"] = QDataStream_readBytes;
    mt["readRawData"] = QDataStream_readRawData;
    mt["resetStatus"] = &QDataStream::resetStatus;
    mt["setByteOrder"] = &QDataStream::setByteOrder;
    mt["setDevice"] = &QDataStream::setDevice;
    mt["setFloatingPointPrecision"] = &QDataStream::setFloatingPointPrecision;
    mt["setStatus"] = &QDataStream::setStatus;
    mt["setVersion"] = &QDataStream::setVersion;
    mt["skipRawData"] = &QDataStream::skipRawData;
    mt["status"] = &QDataStream::status;
    mt["version"] = &QDataStream::version;
    mt["writeBytes"] = QDataStream_writeBytes;
    mt["writeRawData"] = &QDataStream::writeRawData;
}

} // namespace lua

int QDataStream_new(lua_State* const state)
{
    // QDataStream()
    // QDataStream(QIODevice * d)
    // QDataStream(QByteArray * a, QIODevice::OpenMode mode)
    // QDataStream(const QByteArray & a)
    lua::make<QDataStream>(state);
    // TODO Set up constructor

    return 1;
}

int luaopen_luacxx_QDataStream(lua_State* const state)
{
    lua::thread env(state);

    env["QDataStream"] = lua::value::table;
    env["QDataStream"]["new"] = QDataStream_new;
    auto t = env["QDataStream"];

    // enum QDataStream::ByteOrder
    t["BigEndian"] = QDataStream::BigEndian;
    t["LittleEndian"] = QDataStream::LittleEndian;

    // enum QDataStream::FloatingPointPrecision
    t["SinglePrecision"] = QDataStream::SinglePrecision;
    t["DoublePrecision"] = QDataStream::DoublePrecision;

    // enum QDataStream::Status
    t["Ok"] = QDataStream::Ok;
    t["ReadPastEnd"] = QDataStream::ReadPastEnd;
    t["ReadCorruptData"] = QDataStream::ReadCorruptData;
    t["WriteFailed"] = QDataStream::WriteFailed;

    // enum QDataStream::Version
    t["Qt_1_0"] = QDataStream::Qt_1_0;
    t["Qt_2_0"] = QDataStream::Qt_2_0;
    t["Qt_2_1"] = QDataStream::Qt_2_1;
    t["Qt_3_0"] = QDataStream::Qt_3_0;
    t["Qt_3_1"] = QDataStream::Qt_3_1;
    t["Qt_3_3"] = QDataStream::Qt_3_3;
    t["Qt_4_0"] = QDataStream::Qt_4_0;
    t["Qt_4_1"] = QDataStream::Qt_4_1;
    t["Qt_4_2"] = QDataStream::Qt_4_2;
    t["Qt_4_3"] = QDataStream::Qt_4_3;
    t["Qt_4_4"] = QDataStream::Qt_4_4;
    t["Qt_4_5"] = QDataStream::Qt_4_5;
    t["Qt_4_6"] = QDataStream::Qt_4_6;
    t["Qt_4_7"] = QDataStream::Qt_4_7;
    t["Qt_4_8"] = QDataStream::Qt_4_8;
    t["Qt_4_9"] = QDataStream::Qt_4_9;
    t["Qt_5_0"] = QDataStream::Qt_5_0;
    t["Qt_5_1"] = QDataStream::Qt_5_1;
    t["Qt_5_2"] = QDataStream::Qt_5_2;
    t["Qt_5_3"] = QDataStream::Qt_5_3;

    return 0;
}

#include "QByteArray.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QList.hpp"

#include <QByteArray>

int QByteArray_append(lua_State* const state)
{
    return 0;
}

int QByteArray_contains(lua_State* const state)
{
    return 0;
}

int QByteArray_count(lua_State* const state)
{
    return 0;
}

int QByteArray_data(lua_State* const state)
{
    return 0;
}

int QByteArray_endsWith(lua_State* const state)
{
    return 0;
}

int QByteArray_fill(lua_State* const state)
{
    return 0;
}

int QByteArray_indexOf(lua_State* const state)
{
    return 0;
}

int QByteArray_insert(lua_State* const state)
{
    return 0;
}

int QByteArray_lastIndexOf(lua_State* const state)
{
    return 0;
}

int QByteArray_leftJustified(lua_State* const state)
{
    return 0;
}

int QByteArray_mid(lua_State* const state)
{
    return 0;
}

int QByteArray_prepend(lua_State* const state)
{
    return 0;
}

int QByteArray_push_back(lua_State* const state)
{
    return 0;
}

int QByteArray_push_front(lua_State* const state)
{
    return 0;
}

int QByteArray_replace(lua_State* const state)
{
    return 0;
}

int QByteArray_rightJustified(lua_State* const state)
{
    return 0;
}

int QByteArray_setNum(lua_State* const state)
{
    return 0;
}

int QByteArray_startsWith(lua_State* const state)
{
    return 0;
}

int QByteArray_swap(lua_State* const state)
{
    return 0;
}

int QByteArray_toBase64(lua_State* const state)
{
    return 0;
}

int QByteArray_toDouble(lua_State* const state)
{
    return 0;
}

int QByteArray_toFloat(lua_State* const state)
{
    return 0;
}

int QByteArray_toInt(lua_State* const state)
{
    return 0;
}

int QByteArray_toLong(lua_State* const state)
{
    return 0;
}

int QByteArray_toLongLong(lua_State* const state)
{
    return 0;
}

int QByteArray_toPercentEncoding(lua_State* const state)
{
    return 0;
}

int QByteArray_toShort(lua_State* const state)
{
    return 0;
}

int QByteArray_toUInt(lua_State* const state)
{
    return 0;
}

int QByteArray_toULong(lua_State* const state)
{
    return 0;
}

int QByteArray_toULongLong(lua_State* const state)
{
    return 0;
}

int QByteArray_toUShort(lua_State* const state)
{
    return 0;
}

void lua::QByteArray_metatable(const lua::index& mt)
{
    mt["append"] = QByteArray_append;
    mt["at"] = &QByteArray::at;
    mt["capacity"] = &QByteArray::capacity;
    mt["chop"] = &QByteArray::chop;
    mt["clear"] = &QByteArray::clear;
    mt["constData"] = &QByteArray::constData;
    mt["contains"] = QByteArray_contains;
    mt["count"] = QByteArray_count;
    mt["data"] = QByteArray_data;
    mt["endsWith"] = QByteArray_endsWith;
    mt["fill"] = QByteArray_fill;
    mt["indexOf"] = QByteArray_indexOf;
    mt["insert"] = QByteArray_insert;
    mt["isEmpty"] = &QByteArray::isEmpty;
    mt["isNull"] = &QByteArray::isNull;
    mt["lastIndexOf"] = QByteArray_lastIndexOf;
    mt["left"] = &QByteArray::left;
    mt["leftJustified"] = QByteArray_leftJustified;
    mt["length"] = &QByteArray::length;
    mt["mid"] = QByteArray_mid;
    mt["prepend"] = QByteArray_prepend;
    mt["push_back"] = QByteArray_push_back;
    mt["push_front"] = QByteArray_push_front;
    mt["remove"] = &QByteArray::remove;
    mt["repeated"] = &QByteArray::repeated;
    mt["replace"] = QByteArray_replace;
    mt["reserve"] = &QByteArray::reserve;
    mt["resize"] = &QByteArray::resize;
    mt["right"] = &QByteArray::right;
    mt["rightJustified"] = QByteArray_rightJustified;
    mt["setNum"] = QByteArray_setNum;
    mt["setRawData"] = &QByteArray::setRawData;
    mt["simplified"] = &QByteArray::simplified;
    mt["size"] = &QByteArray::size;
    mt["split"] = &QByteArray::split;
    mt["squeeze"] = &QByteArray::squeeze;
    mt["startsWith"] = QByteArray_startsWith;
    mt["swap"] = QByteArray_swap;
    mt["toBase64"] = QByteArray_toBase64;
    mt["toDouble"] = QByteArray_toDouble;
    mt["toFloat"] = QByteArray_toFloat;
    mt["toHex"] = &QByteArray::toHex;
    mt["toInt"] = QByteArray_toInt;
    mt["toLong"] = QByteArray_toLong;
    mt["toLongLong"] = QByteArray_toLongLong;
    mt["toLower"] = &QByteArray::toLower;
    mt["toPercentEncoding"] = QByteArray_toPercentEncoding;
    mt["toShort"] = QByteArray_toShort;
    mt["toUInt"] = QByteArray_toUInt;
    mt["toULong"] = QByteArray_toULong;
    mt["toULongLong"] = QByteArray_toULongLong;
    mt["toUShort"] = QByteArray_toUShort;
    mt["toUpper"] = &QByteArray::toUpper;
    mt["trimmed"] = &QByteArray::trimmed;
    mt["truncate"] = &QByteArray::truncate;
}

int QByteArray_new(lua_State* const state)
{
    // QByteArray()
    // QByteArray(const char * data, int size = -1)
    // QByteArray(int size, char ch)
    // QByteArray(const QByteArray & other)
    // QByteArray(QByteArray && other)
    lua::make<QByteArray>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Core_QByteArray(lua_State* const state)
{
    lua::thread env(state);

    env["QByteArray"] = lua::value::table;
    env["QByteArray"]["new"] = QByteArray_new;
    auto t = env["QByteArray"];

    // enum QByteArray::Base64Option
    t["Base64Encoding"] = QByteArray::Base64Encoding;
    t["Base64UrlEncoding"] = QByteArray::Base64UrlEncoding;
    t["KeepTrailingEquals"] = QByteArray::KeepTrailingEquals;
    t["OmitTrailingEquals"] = QByteArray::OmitTrailingEquals;

    return 0;
}

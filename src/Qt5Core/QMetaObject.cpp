#include "QMetaObject.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QObject.hpp"
#include "QMetaProperty.hpp"
#include "QMetaMethod.hpp"
#include "QMetaClassInfo.hpp"
#include "QMetaEnum.hpp"
#include "QByteArray.hpp"

namespace lua {

void QMetaObject_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["classInfo"] = &QMetaObject::classInfo;
    mt["classInfoCount"] = &QMetaObject::classInfoCount;
    mt["classInfoOffset"] = &QMetaObject::classInfoOffset;
    mt["className"] = &QMetaObject::className;
    mt["constructor"] = &QMetaObject::constructor;
    mt["constructorCount"] = &QMetaObject::constructorCount;
    mt["enumerator"] = &QMetaObject::enumerator;
    mt["enumeratorCount"] = &QMetaObject::enumeratorCount;
    mt["enumeratorOffset"] = &QMetaObject::enumeratorOffset;
    mt["indexOfClassInfo"] = &QMetaObject::indexOfClassInfo;
    mt["indexOfConstructor"] = &QMetaObject::indexOfConstructor;
    mt["indexOfEnumerator"] = &QMetaObject::indexOfEnumerator;
    mt["indexOfMethod"] = &QMetaObject::indexOfMethod;
    mt["indexOfProperty"] = &QMetaObject::indexOfProperty;
    mt["indexOfSignal"] = &QMetaObject::indexOfSignal;
    mt["indexOfSlot"] = &QMetaObject::indexOfSlot;
    mt["method"] = &QMetaObject::method;
    mt["methodCount"] = &QMetaObject::methodCount;
    mt["methodOffset"] = &QMetaObject::methodOffset;
    //QObject *   newInstance(QGenericArgument val0 = QGenericArgument( 0 ), QGenericArgument val1 = QGenericArgument(), QGenericArgument val2 = QGenericArgument(), QGenericArgument val3 = QGenericArgument(), QGenericArgument val4 = QGenericArgument(), QGenericArgument val5 = QGenericArgument(), QGenericArgument val6 = QGenericArgument(), QGenericArgument val7 = QGenericArgument(), QGenericArgument val8 = QGenericArgument(), QGenericArgument val9 = QGenericArgument()) const
    mt["property"] = &QMetaObject::property;
    mt["propertyCount"] = &QMetaObject::propertyCount;
    mt["propertyOffset"] = &QMetaObject::propertyOffset;
    mt["superClass"] = &QMetaObject::superClass;
    mt["userProperty"] = &QMetaObject::userProperty;
}

} // namespace lua

int QMetaObject_checkConnectArgs(lua_State* const state)
{
    return 0;
}

int luaopen_Qt5Core_QMetaObject(lua_State* const state)
{
    lua::thread env(state);

    env["QMetaObject"] = lua::value::table;
    auto t = env["QMetaObject"];

    t["checkConnectArgs"] = QMetaObject_checkConnectArgs;
    t["connectSlotsByName"] = QMetaObject::connectSlotsByName;
    // bool    invokeMethod(QObject * obj, const char * member, Qt::ConnectionType type, QGenericReturnArgument ret, QGenericArgument val0 = QGenericArgument( 0 ), QGenericArgument val1 = QGenericArgument(), QGenericArgument val2 = QGenericArgument(), QGenericArgument val3 = QGenericArgument(), QGenericArgument val4 = QGenericArgument(), QGenericArgument val5 = QGenericArgument(), QGenericArgument val6 = QGenericArgument(), QGenericArgument val7 = QGenericArgument(), QGenericArgument val8 = QGenericArgument(), QGenericArgument val9 = QGenericArgument())
    // bool    invokeMethod(QObject * obj, const char * member, QGenericReturnArgument ret, QGenericArgument val0 = QGenericArgument( 0 ), QGenericArgument val1 = QGenericArgument(), QGenericArgument val2 = QGenericArgument(), QGenericArgument val3 = QGenericArgument(), QGenericArgument val4 = QGenericArgument(), QGenericArgument val5 = QGenericArgument(), QGenericArgument val6 = QGenericArgument(), QGenericArgument val7 = QGenericArgument(), QGenericArgument val8 = QGenericArgument(), QGenericArgument val9 = QGenericArgument())
    // bool    invokeMethod(QObject * obj, const char * member, Qt::ConnectionType type, QGenericArgument val0 = QGenericArgument( 0 ), QGenericArgument val1 = QGenericArgument(), QGenericArgument val2 = QGenericArgument(), QGenericArgument val3 = QGenericArgument(), QGenericArgument val4 = QGenericArgument(), QGenericArgument val5 = QGenericArgument(), QGenericArgument val6 = QGenericArgument(), QGenericArgument val7 = QGenericArgument(), QGenericArgument val8 = QGenericArgument(), QGenericArgument val9 = QGenericArgument())
    // bool    invokeMethod(QObject * obj, const char * member, QGenericArgument val0 = QGenericArgument( 0 ), QGenericArgument val1 = QGenericArgument(), QGenericArgument val2 = QGenericArgument(), QGenericArgument val3 = QGenericArgument(), QGenericArgument val4 = QGenericArgument(), QGenericArgument val5 = QGenericArgument(), QGenericArgument val6 = QGenericArgument(), QGenericArgument val7 = QGenericArgument(), QGenericArgument val8 = QGenericArgument(), QGenericArgument val9 = QGenericArgument())
    t["normalizedSignature"] = QMetaObject::normalizedSignature;
    t["normalizedType"] = QMetaObject::normalizedType;

    return 0;
}

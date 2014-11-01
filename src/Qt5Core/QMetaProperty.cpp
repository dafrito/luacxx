#include "QMetaProperty.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QMetaEnum.hpp"
#include "QObject.hpp"
#include "QVariant.hpp"
#include "QMetaMethod.hpp"

int QMetaProperty_isDesignable(lua_State* const state)
{
    return 0;
}
int QMetaProperty_isScriptable(lua_State* const state)
{
    return 0;
}
int QMetaProperty_isStored(lua_State* const state)
{
    return 0;
}
int QMetaProperty_isUser(lua_State* const state)
{
    return 0;
}

namespace lua {

void QMetaProperty_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["enumerator"] = &QMetaProperty::enumerator;
    mt["hasNotifySignal"] = &QMetaProperty::hasNotifySignal;
    mt["isConstant"] = &QMetaProperty::isConstant;
    mt["isDesignable"] = QMetaProperty_isDesignable;
    mt["isEnumType"] = &QMetaProperty::isEnumType;
    mt["isFinal"] = &QMetaProperty::isFinal;
    mt["isFlagType"] = &QMetaProperty::isFlagType;
    mt["isReadable"] = &QMetaProperty::isReadable;
    mt["isResettable"] = &QMetaProperty::isResettable;
    mt["isScriptable"] = QMetaProperty_isScriptable;
    mt["isStored"] = QMetaProperty_isStored;
    mt["isUser"] = QMetaProperty_isUser;
    mt["isValid"] = &QMetaProperty::isValid;
    mt["isWritable"] = &QMetaProperty::isWritable;
    mt["name"] = &QMetaProperty::name;
    mt["notifySignal"] = &QMetaProperty::notifySignal;
    mt["notifySignalIndex"] = &QMetaProperty::notifySignalIndex;
    mt["propertyIndex"] = &QMetaProperty::propertyIndex;
    mt["read"] = &QMetaProperty::read;
    mt["reset"] = &QMetaProperty::reset;
    mt["revision"] = &QMetaProperty::revision;
    mt["type"] = &QMetaProperty::type;
    mt["typeName"] = &QMetaProperty::typeName;
    mt["userType"] = &QMetaProperty::userType;
    mt["write"] = &QMetaProperty::write;
}

} // namespace lua

int luaopen_luacxx_QMetaProperty(lua_State* const state)
{
    lua::thread env(state);

    env["QMetaProperty"] = lua::value::table;
    return 0;
}

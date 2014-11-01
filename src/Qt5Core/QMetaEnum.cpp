#include "QMetaEnum.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QByteArray.hpp"

int QMetaEnum_keyToValue(lua_State* const state)
{
    return 0;
}
int QMetaEnum_keysToValue(lua_State* const state)
{
    return 0;
}

namespace lua {

void QMetaEnum_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["isFlag"] = &QMetaEnum::isFlag;
    mt["isValid"] = &QMetaEnum::isValid;
    mt["key"] = &QMetaEnum::key;
    mt["keyCount"] = &QMetaEnum::keyCount;
    mt["keyToValue"] = QMetaEnum_keyToValue;
    mt["keysToValue"] = QMetaEnum_keysToValue;
    mt["name"] = &QMetaEnum::name;
    mt["scope"] = &QMetaEnum::scope;
    mt["value"] = &QMetaEnum::value;
    mt["valueToKey"] = &QMetaEnum::valueToKey;
    mt["valueToKeys"] = &QMetaEnum::valueToKeys;
}

} // namespace lua

int luaopen_luacxx_QMetaEnum(lua_State* const state)
{
    lua::thread env(state);

    env["QMetaEnum"] = lua::value::table;

    return 0;
}

#include "QBitArray.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"

int QBitArray_count(lua_State* const state)
{
    return 0;
}
int QBitArray_fill(lua_State* const state)
{
    return 0;
}
int QBitArray_setBit(lua_State* const state)
{
    return 0;
}

namespace lua {

void QBitArray_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["at"] = &QBitArray::at;
    mt["clear"] = &QBitArray::clear;
    mt["clearBit"] = &QBitArray::clearBit;
    mt["count"] = QBitArray_count;
    mt["fill"] = QBitArray_fill;
    mt["isEmpty"] = &QBitArray::isEmpty;
    mt["isNull"] = &QBitArray::isNull;
    mt["resize"] = &QBitArray::resize;
    mt["setBit"] = QBitArray_setBit;
    mt["size"] = &QBitArray::size;
    mt["swap"] = &QBitArray::swap;
    mt["testBit"] = &QBitArray::testBit;
    mt["toggleBit"] = &QBitArray::toggleBit;
    mt["truncate"] = &QBitArray::truncate;
}

} // namespace lua

int QBitArray_new(lua_State* const state)
{
    // QBitArray(const QBitArray & other)
    if (lua_gettop(state) == 2) {
        // QBitArray(int size, bool value = false)
        lua::make<QBitArray>(state,
            lua::get<int>(state, 1),
            lua::get<bool>(state, 2)
        );
    } else if (lua::is_type<QBitArray>(state, 1)) {
        lua::make<QBitArray>(state,
            lua::get<const QBitArray&>(state, 1)
        );
    } else if (lua_gettop(state) == 1) {
        lua::make<QBitArray>(state,
            lua::get<int>(state, 1)
        );
    } else {
        // QBitArray()
        lua::make<QBitArray>(state);
    }
    return 1;
}

int luaopen_luacxx_QBitArray(lua_State* const state)
{
    lua::thread env(state);

    env["QBitArray"] = lua::value::table;
    env["QBitArray"]["new"] = QBitArray_new;
    auto t = env["QBitArray"];

    return 0;
}

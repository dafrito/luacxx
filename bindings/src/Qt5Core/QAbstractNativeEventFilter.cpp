#include "QAbstractNativeEventFilter.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QAbstractNativeEventFilter>

void lua::QAbstractNativeEventFilter_metatable(lua_State* const state, const int mt)
{
    // TODO Set up metatable methods for this class
}

int luaopen_Qt5Core_QAbstractNativeEventFilter(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractNativeEventFilter"] = lua::value::table;

    return 0;
}

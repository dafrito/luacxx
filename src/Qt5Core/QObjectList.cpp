#include "QObjectList.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "QObject.hpp"
#include "QList.hpp"

namespace lua {

void QObjectList_metatable(lua_State* const state, const int pos)
{
    lua::QList_metatable<QObject*>(state, pos);
}

} // namespace lua

int QObjectList_new(lua_State* const state)
{
    lua::make<QObjectList>(state);

    return 1;
}

int luaopen_Qt5Core_QObjectList(lua_State* const state)
{
    lua::thread env(state);

    env["QObjectList"] = lua::value::table;
    env["QObjectList"]["new"] = QObjectList_new;
    auto t = env["QObjectList"];

    return 0;
}

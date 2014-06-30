#include "QList.hpp"
#include "../luacxx/convert/callable.hpp"
#include "../luacxx/thread.hpp"

#include <QList>
/*

void lua::QList_metatable(const lua::index& mt)
{
    // TODO Set up metatable methods for this class
}

int QList_new(lua_State* const state)
{
    lua::make<QList>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Core_QList(lua_State* const state)
{
    lua::thread env(state);

    env["QList"] = lua::value::table;
    env["QList"]["new"] = QList_new;

    return 0;
}
*/

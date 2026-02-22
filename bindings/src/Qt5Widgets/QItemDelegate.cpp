#include "QItemDelegate.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QItemEditorFactory.hpp"

namespace lua {

void QItemDelegate_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractItemDelegate_metatable(state, pos);

    lua::index mt(state, pos);
    mt["hasClipping"] = &QItemDelegate::hasClipping;
    mt["itemEditorFactory"] = &QItemDelegate::itemEditorFactory;
    mt["setClipping"] = &QItemDelegate::setClipping;
    mt["setItemEditorFactory"] = &QItemDelegate::setItemEditorFactory;
}

} // namespace lua

int QItemDelegate_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        lua::push(state, new QItemDelegate);
    } else {
        lua::push(state, new QItemDelegate(lua::get<QObject*>(state, 1)));
    }

    return 1;
}

int luaopen_Qt5Widgets_QItemDelegate(lua_State* const state)
{
    lua::thread env(state);

    env["QItemDelegate"] = lua::value::table;
    env["QItemDelegate"]["new"] = QItemDelegate_new;
    auto t = env["QItemDelegate"];

    return 0;
}

#include "QTextBlockGroup.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QTextObject.hpp"
#include "QTextBlock.hpp"
#include "../Qt5Core/Qlist.hpp"

namespace lua {

void QTextBlockGroup_metatable(lua_State* const state, const int pos)
{
    lua::QTextObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["blockFormatChanged"] = &QTextBlockGroup::blockFormatChanged;
    mt["blockInserted"] = &QTextBlockGroup::blockInserted;
    mt["blockList"] = &QTextBlockGroup::blockList;
    mt["blockRemoved"] = &QTextBlockGroup::blockRemoved;
}

} // namespace lua

int QTextBlockGroup_new(lua_State* const state)
{
    lua::make<QTextBlockGroup>(state, lua::get<QTextDocument*>(state, 1));
    return 1;
}

int luaopen_Qt5Gui_QTextBlockGroup(lua_State* const state)
{
    lua::thread env(state);

    env["QTextBlockGroup"] = lua::value::table;
    env["QTextBlockGroup"]["new"] = QTextBlockGroup_new;
    auto t = env["QTextBlockGroup"];

    return 0;
}

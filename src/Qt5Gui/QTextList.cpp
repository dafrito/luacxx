#include "QTextList.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QTextBlockGroup.hpp"
#include "QTextBlock.hpp"
#include "QTextListFormat.hpp"
#include "../Qt5Core/QString.hpp"

namespace lua {

void QTextList_metatable(lua_State* const state, const int pos)
{
    lua::QTextBlockGroup_metatable(state, pos);

    lua::index mt(state, pos);
    mt["add"] = &QTextList::add;
    mt["count"] = &QTextList::count;
    mt["format"] = &QTextList::format;
    mt["item"] = &QTextList::item;
    mt["itemNumber"] = &QTextList::itemNumber;
    mt["itemText"] = &QTextList::itemText;
    mt["remove"] = &QTextList::remove;
    mt["removeItem"] = &QTextList::removeItem;
    mt["setFormat"] = &QTextList::setFormat;
}

} // namespace lua

int luaopen_Qt5Gui_QTextList(lua_State* const state)
{
    lua::thread env(state);

    env["QTextList"] = lua::value::table;
    auto t = env["QTextList"];

    return 0;
}

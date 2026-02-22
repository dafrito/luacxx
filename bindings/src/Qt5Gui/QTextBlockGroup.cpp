#include "QTextBlockGroup.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QTextObject.hpp"
#include "QTextBlock.hpp"
#include "QTextDocument.hpp"
#include "../Qt5Core/QList.hpp"

namespace lua {

void QTextBlockGroup_metatable(lua_State* const state, const int pos)
{
    lua::QTextObject_metatable(state, pos);
}

} // namespace lua

int luaopen_Qt5Gui_QTextBlockGroup(lua_State* const state)
{
    lua::thread env(state);

    env["QTextBlockGroup"] = lua::value::table;

    return 0;
}

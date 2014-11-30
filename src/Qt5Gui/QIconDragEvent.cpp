#include "QIconDragEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

// http://qt-project.org/doc/qt-5/qicondragevent.html

namespace lua {

void QIconDragEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);
}

} // namespace lua

int QIconDragEvent_new(lua_State* const state)
{
    lua::make<QIconDragEvent>(state);

    return 1;
}

int luaopen_Qt5Gui_QIconDragEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QIconDragEvent"] = lua::value::table;
    env["QIconDragEvent"]["new"] = QIconDragEvent_new;
    auto t = env["QIconDragEvent"];

    return 0;
}

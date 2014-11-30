#include "QInputEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"

// http://qt-project.org/doc/qt-5/qinputevent.html

namespace lua {

void QInputEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["modifiers"] = &QInputEvent::modifiers;
    mt["timestamp"] = &QInputEvent::timestamp;
}

} // namespace lua

int luaopen_Qt5Gui_QInputEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QInputEvent"] = lua::value::table;

    return 0;
}

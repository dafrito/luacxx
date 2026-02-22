#include "QInputMethodQueryEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QVariant.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"

// http://qt-project.org/doc/qt-5/qinputmethodqueryevent.html

namespace lua {

void QInputMethodQueryEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["queries"] = &QInputMethodQueryEvent::queries;
    mt["setValue"] = &QInputMethodQueryEvent::setValue;
    mt["value"] = &QInputMethodQueryEvent::value;
}

} // namespace lua

int QInputMethodQueryEvent_new(lua_State* const state)
{
    lua::make<QInputMethodQueryEvent>(state,
        lua::get<Qt::InputMethodQueries>(state, 1)
    );

    return 1;
}

int luaopen_Qt5Gui_QInputMethodQueryEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QInputMethodQueryEvent"] = lua::value::table;
    env["QInputMethodQueryEvent"]["new"] = QInputMethodQueryEvent_new;
    auto t = env["QInputMethodQueryEvent"];

    return 0;
}

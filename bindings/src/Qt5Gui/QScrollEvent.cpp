#include "QScrollEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPointF.hpp"

// http://qt-project.org/doc/qt-5/qscrollevent.html

namespace lua {

void QScrollEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["contentPos"] = &QScrollEvent::contentPos;
    mt["overshootDistance"] = &QScrollEvent::overshootDistance;
    mt["scrollState"] = &QScrollEvent::scrollState;
}

} // namespace lua

int QScrollEvent_new(lua_State* const state)
{
    lua::make<QScrollEvent>(state,
        lua::get<const QPointF&>(state, 1),
        lua::get<const QPointF&>(state, 2),
        lua::get<QScrollEvent::ScrollState>(state, 3)
    );

    return 1;
}

int luaopen_Qt5Gui_QScrollEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QScrollEvent"] = lua::value::table;
    env["QScrollEvent"]["new"] = QScrollEvent_new;
    auto t = env["QScrollEvent"];

    // enum QScrollEvent::ScrollState
    t["ScrollStarted"] = QScrollEvent::ScrollStarted;
    t["ScrollUpdated"] = QScrollEvent::ScrollUpdated;
    t["ScrollFinished"] = QScrollEvent::ScrollFinished;

    return 0;
}

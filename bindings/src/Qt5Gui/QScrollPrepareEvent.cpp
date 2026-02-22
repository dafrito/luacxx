#include "QScrollPrepareEvent.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QSizeF.hpp"

// http://qt-project.org/doc/qt-5/qscrollprepareevent.html

namespace lua {

void QScrollPrepareEvent_metatable(lua_State* const state, const int pos)
{
    lua::QEvent_metatable(state, pos);

    lua::index mt(state, pos);
    mt["contentPos"] = &QScrollPrepareEvent::contentPos;
    mt["contentPosRange"] = &QScrollPrepareEvent::contentPosRange;
    mt["setContentPos"] = &QScrollPrepareEvent::setContentPos;
    mt["setContentPosRange"] = &QScrollPrepareEvent::setContentPosRange;
    mt["setViewportSize"] = &QScrollPrepareEvent::setViewportSize;
    mt["startPos"] = &QScrollPrepareEvent::startPos;
    mt["viewportSize"] = &QScrollPrepareEvent::viewportSize;
}

} // namespace lua

int QScrollPrepareEvent_new(lua_State* const state)
{
    lua::make<QScrollPrepareEvent>(state,
        lua::get<const QPointF&>(state, 1)
    );

    return 1;
}

int luaopen_Qt5Gui_QScrollPrepareEvent(lua_State* const state)
{
    lua::thread env(state);

    env["QScrollPrepareEvent"] = lua::value::table;
    env["QScrollPrepareEvent"]["new"] = QScrollPrepareEvent_new;
    auto t = env["QScrollPrepareEvent"];

    return 0;
}

#include "QGraphicsPathItem.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Gui/QPainterPath.hpp"

// https://qt-project.org/doc/qt-5/qgraphicspathitem.html

namespace lua {

void QGraphicsPathItem_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractGraphicsShapeItem_metatable(state, pos);

    lua::index mt(state, pos);
    mt["path"] = &QGraphicsPathItem::path;
    mt["setPath"] = &QGraphicsPathItem::setPath;
}

} // namespace lua

int QGraphicsPathItem_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QGraphicsPathItem()
        lua::make<QGraphicsPathItem>(state);
        break;
    case 1:
        if (lua::is_type<QPainterPath>(state, 1)) {
            // QGraphicsPathItem(const QPainterPath & path)
            lua::make<QGraphicsPathItem>(state,
                lua::get<const QPainterPath&>(state, 1)
            );
        } else {
            // QGraphicsPathItem(QGraphicsItem * parent)
            lua::make<QGraphicsPathItem>(state,
                lua::get<QGraphicsItem*>(state, 1)
            );
        }
        break;
    case 2:
        // QGraphicsPathItem(const QPainterPath & path, QGraphicsItem * parent)
        lua::make<QGraphicsPathItem>(state,
            lua::get<const QPainterPath&>(state, 1),
            lua::get<QGraphicsItem*>(state, 2)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsPathItem(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsPathItem"] = lua::value::table;
    env["QGraphicsPathItem"]["new"] = QGraphicsPathItem_new;
    auto t = env["QGraphicsPathItem"];

    return 0;
}

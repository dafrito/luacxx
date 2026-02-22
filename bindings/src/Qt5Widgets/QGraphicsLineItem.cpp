#include "QGraphicsLineItem.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QLineF.hpp"
#include "../Qt5Gui/QPen.hpp"

// http://qt-project.org/doc/qt-5/qgraphicslineitem.html

int QGraphicsLineItem_setLine(lua_State* const state)
{
    auto self = lua::get<QGraphicsLineItem*>(state, 1);

    if (lua_gettop(state) == 2) {
        // void setLine(const QLineF & line)
        self->setLine(
            lua::get<const QLineF&>(state, 2)
        );
    } else {
        // void setLine(qreal x1, qreal y1, qreal x2, qreal y2)
        self->setLine(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<qreal>(state, 5)
        );
    }

    return 0;
}

namespace lua {

void QGraphicsLineItem_metatable(lua_State* const state, const int pos)
{
    lua::QGraphicsItem_metatable(state, pos);

    lua::index mt(state, pos);
    mt["line"] = &QGraphicsLineItem::line;
    mt["pen"] = &QGraphicsLineItem::pen;
    mt["setLine"] = QGraphicsLineItem_setLine;
    mt["setPen"] = &QGraphicsLineItem::setPen;
}

} // namespace lua

int QGraphicsLineItem_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QGraphicsLineItem()
        lua::make<QGraphicsLineItem>(state);
        break;
    case 1:
        if (lua::is_type<QLineF>(state, 1)) {
            lua::make<QGraphicsLineItem>(state,
                lua::get<const QLineF&>(state, 1)
            );
        } else {
            lua::make<QGraphicsLineItem>(state,
                lua::get<QGraphicsItem*>(state, 1)
            );
        }
        break;
    case 2:
        lua::make<QGraphicsLineItem>(state,
            lua::get<const QLineF&>(state, 1),
            lua::get<QGraphicsItem*>(state, 2)
        );
        break;
    case 4:
        // QGraphicsLineItem(qreal x1, qreal y1, qreal x2, qreal y2)
        lua::make<QGraphicsLineItem>(state,
            lua::get<qreal>(state, 1),
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        );
        break;
    case 5:
        // QGraphicsLineItem(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent)
        lua::make<QGraphicsLineItem>(state,
            lua::get<qreal>(state, 1),
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4),
            lua::get<QGraphicsItem*>(state, 5)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsLineItem(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsLineItem"] = lua::value::table;
    env["QGraphicsLineItem"]["new"] = QGraphicsLineItem_new;
    auto t = env["QGraphicsLineItem"];

    return 0;
}

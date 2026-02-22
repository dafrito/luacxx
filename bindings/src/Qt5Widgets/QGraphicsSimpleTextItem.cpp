#include "QGraphicsSimpleTextItem.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QString.hpp"
#include "../Qt5Gui/QFont.hpp"

// https://qt-project.org/doc/qt-5/qgraphicssimpletextitem.html

namespace lua {

void QGraphicsSimpleTextItem_metatable(lua_State* const state, const int pos)
{
    lua::QAbstractGraphicsShapeItem_metatable(state, pos);

    lua::index mt(state, pos);
    mt["font"] = &QGraphicsSimpleTextItem::font;
    mt["setFont"] = &QGraphicsSimpleTextItem::setFont;
    mt["setText"] = &QGraphicsSimpleTextItem::setText;
    mt["text"] = &QGraphicsSimpleTextItem::text;
}

} // namespace lua

int QGraphicsSimpleTextItem_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QGraphicsSimpleTextItem()
        lua::make<QGraphicsSimpleTextItem>(state);
        break;
    case 1:
        if (lua::is_type<QGraphicsItem>(state, 1)) {
            // QGraphicsSimpleTextItem(QGraphicsItem * parent)
            lua::make<QGraphicsSimpleTextItem>(state,
                lua::get<QGraphicsItem*>(state, 1)
            );
        } else {
            // QGraphicsSimpleTextItem(const QString& text)
            lua::make<QGraphicsSimpleTextItem>(state,
                lua::get<QString>(state, 1)
            );
        }
        break;
    case 2:
        // QGraphicsSimpleTextItem(const QString& text, QGraphicsItem * parent)
        lua::make<QGraphicsSimpleTextItem>(state,
            lua::get<QString>(state, 1),
            lua::get<QGraphicsItem*>(state, 2)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsSimpleTextItem(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsSimpleTextItem"] = lua::value::table;
    env["QGraphicsSimpleTextItem"]["new"] = QGraphicsSimpleTextItem_new;
    auto t = env["QGraphicsSimpleTextItem"];

    return 0;
}

#include "QGraphicsTextItem.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Gui/QColor.hpp"
#include "../Qt5Gui/QTextDocument.hpp"
#include "../Qt5Gui/QFont.hpp"
#include "../Qt5Gui/QTextCursor.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"

// https://qt-project.org/doc/qt-5/qgraphicstextitem.html

namespace lua {

void QGraphicsTextItem_metatable(lua_State* const state, const int pos)
{
    lua::QGraphicsObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["adjustSize"] = &QGraphicsTextItem::adjustSize;
    mt["defaultTextColor"] = &QGraphicsTextItem::defaultTextColor;
    mt["document"] = &QGraphicsTextItem::document;
    mt["font"] = &QGraphicsTextItem::font;
    mt["openExternalLinks"] = &QGraphicsTextItem::openExternalLinks;
    mt["setDefaultTextColor"] = &QGraphicsTextItem::setDefaultTextColor;
    mt["setDocument"] = &QGraphicsTextItem::setDocument;
    mt["setFont"] = &QGraphicsTextItem::setFont;
    mt["setHtml"] = &QGraphicsTextItem::setHtml;
    mt["setOpenExternalLinks"] = &QGraphicsTextItem::setOpenExternalLinks;
    mt["setPlainText"] = &QGraphicsTextItem::setPlainText;
    mt["setTabChangesFocus"] = &QGraphicsTextItem::setTabChangesFocus;
    mt["setTextCursor"] = &QGraphicsTextItem::setTextCursor;
    mt["setTextInteractionFlags"] = &QGraphicsTextItem::setTextInteractionFlags;
    mt["setTextWidth"] = &QGraphicsTextItem::setTextWidth;
    mt["tabChangesFocus"] = &QGraphicsTextItem::tabChangesFocus;
    mt["textCursor"] = &QGraphicsTextItem::textCursor;
    mt["textInteractionFlags"] = &QGraphicsTextItem::textInteractionFlags;
    mt["textWidth"] = &QGraphicsTextItem::textWidth;
    mt["toHtml"] = &QGraphicsTextItem::toHtml;
    mt["toPlainText"] = &QGraphicsTextItem::toPlainText;
}

} // namespace lua

int QGraphicsTextItem_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QGraphicsTextItem()
        lua::make<QGraphicsTextItem>(state);
        break;
    case 1:
        if (lua::is_type<QGraphicsItem>(state, 1)) {
            // QGraphicsTextItem(QGraphicsItem * parent)
            lua::make<QGraphicsTextItem>(state,
                lua::get<QGraphicsItem*>(state, 1)
            );
        } else {
            // QGraphicsTextItem(const QString& text)
            lua::make<QGraphicsTextItem>(state,
                lua::get<QString>(state, 1)
            );
        }
        break;
    case 2:
        // QGraphicsTextItem(const QString& text, QGraphicsItem * parent)
        lua::make<QGraphicsTextItem>(state,
            lua::get<QString>(state, 1),
            lua::get<QGraphicsItem*>(state, 2)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsTextItem(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsTextItem"] = lua::value::table;
    env["QGraphicsTextItem"]["new"] = QGraphicsTextItem_new;
    auto t = env["QGraphicsTextItem"];

    return 0;
}

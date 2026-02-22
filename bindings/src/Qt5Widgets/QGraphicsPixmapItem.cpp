#include "QGraphicsPixmapItem.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Gui/QPixmap.hpp"
#include "../Qt5Core/QPointF.hpp"

int QGraphicsPixmapItem_setOffset(lua_State* const state)
{
    auto self = lua::get<QGraphicsPixmapItem*>(state, 1);

    if (lua_gettop(state) == 2) {
        self->setOffset(
            lua::get<const QPointF&>(state, 2)
        );
    } else {
        self->setOffset(
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3)
        );
    }

    return 1;
}

namespace lua {

void QGraphicsPixmapItem_metatable(lua_State* const state, const int pos)
{
    lua::QGraphicsItem_metatable(state, pos);

    lua::index mt(state, pos);
    mt["offset"] = &QGraphicsPixmapItem::offset;
    mt["pixmap"] = &QGraphicsPixmapItem::pixmap;
    mt["setOffset"] = QGraphicsPixmapItem_setOffset;
    mt["setPixmap"] = &QGraphicsPixmapItem::setPixmap;
    mt["setShapeMode"] = &QGraphicsPixmapItem::setShapeMode;
    mt["setTransformationMode"] = &QGraphicsPixmapItem::setTransformationMode;
    mt["shapeMode"] = &QGraphicsPixmapItem::shapeMode;
    mt["transformationMode"] = &QGraphicsPixmapItem::transformationMode;
}

} // namespace lua

int QGraphicsPixmapItem_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QGraphicsPixmapItem()
        lua::make<QGraphicsPixmapItem>(state);
        break;
    case 1:
        if (lua::is_type<QPixmap>(state, 1)) {
            // QGraphicsPixmapItem(const QPixmap & pixmap)
            lua::make<QGraphicsPixmapItem>(state,
                lua::get<const QPixmap&>(state, 1)
            );
        } else {
            // QGraphicsPixmapItem(QGraphicsItem * parent)
            lua::make<QGraphicsPixmapItem>(state,
                lua::get<QGraphicsItem*>(state, 1)
            );
        }
        break;
    case 2:
        // QGraphicsPixmapItem(const QPixmap & pixmap, QGraphicsItem * parent)
        lua::make<QGraphicsPixmapItem>(state,
            lua::get<const QPixmap&>(state, 1),
            lua::get<QGraphicsItem*>(state, 2)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsPixmapItem(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsPixmapItem"] = lua::value::table;
    env["QGraphicsPixmapItem"]["new"] = QGraphicsPixmapItem_new;
    auto t = env["QGraphicsPixmapItem"];

    // enum QGraphicsPixmapItem::ShapeMode
    t["MaskShape"] = QGraphicsPixmapItem::MaskShape;
    t["BoundingRectShape"] = QGraphicsPixmapItem::BoundingRectShape;
    t["HeuristicMaskShape"] = QGraphicsPixmapItem::HeuristicMaskShape;

    return 0;
}

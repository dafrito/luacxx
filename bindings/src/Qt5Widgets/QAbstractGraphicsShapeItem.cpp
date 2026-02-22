#include "QAbstractGraphicsShapeItem.hpp"
#include "../convert/callable.hpp"
#include "../convert/const_char_p.hpp"
#include "../thread.hpp"

#include "../Qt5Gui/QPen.hpp"
#include "../Qt5Gui/QBrush.hpp"

// https://qt-project.org/doc/qt-5/qabstractgraphicsshapeitem.html

namespace lua {

void QAbstractGraphicsShapeItem_metatable(lua_State* const state, const int pos)
{
    lua::QGraphicsItem_metatable(state, pos);

    lua::index mt(state, pos);
    mt["brush"] = &QAbstractGraphicsShapeItem::brush;
    mt["pen"] = &QAbstractGraphicsShapeItem::pen;
    mt["setBrush"] = &QAbstractGraphicsShapeItem::setBrush;
    mt["setPen"] = &QAbstractGraphicsShapeItem::setPen;
}

} // namespace lua

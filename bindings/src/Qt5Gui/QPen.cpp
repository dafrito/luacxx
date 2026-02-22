#include "QPen.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QVector.hpp"
#include "QBrush.hpp"
#include "../Qt5Core/Qt.hpp"
#include "QColor.hpp"

void lua::QPen_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["brush"] = &QPen::brush;
    mt["capStyle"] = &QPen::capStyle;
    mt["color"] = &QPen::color;
    mt["dashOffset"] = &QPen::dashOffset;
    mt["dashPattern"] = &QPen::dashPattern;
    mt["isCosmetic"] = &QPen::isCosmetic;
    mt["joinStyle"] = &QPen::joinStyle;
    mt["miterLimit"] = &QPen::miterLimit;
    mt["setBrush"] = &QPen::setBrush;
    mt["setCapStyle"] = &QPen::setCapStyle;
    mt["setColor"] = &QPen::setColor;
    mt["setCosmetic"] = &QPen::setCosmetic;
    mt["setDashOffset"] = &QPen::setDashOffset;
    mt["setDashPattern"] = &QPen::setDashPattern;
    mt["setJoinStyle"] = &QPen::setJoinStyle;
    mt["setMiterLimit"] = &QPen::setMiterLimit;
    mt["setStyle"] = &QPen::setStyle;
    mt["setWidth"] = &QPen::setWidth;
    mt["setWidthF"] = &QPen::setWidthF;
    mt["style"] = &QPen::style;
    mt["swap"] = &QPen::swap;
    mt["width"] = &QPen::width;
    mt["widthF"] = &QPen::widthF;
}

/*


*/
int QPen_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
        // QPen()
        lua::make<QPen>(state);
        break;
    case 1:
        // QPen(Qt::PenStyle style)
        // QPen(const QColor & color)
        // QPen(const QPen & pen)
        if (lua::is_type<QColor>(state, 1)) {
            lua::make<QPen>(state, lua::get<const QColor&>(state, 1));
        } else if (lua::is_type<QPen>(state, 1)) {
            lua::make<QPen>(state, lua::get<const QPen&>(state, 1));
        } else {
            lua::make<QPen>(state, lua::get<Qt::PenStyle>(state, 1));
        }
        break;
    case 2:
        // QPen(const QBrush & brush, qreal width)
        lua::make<QPen>(state,
            lua::get<const QBrush&>(state, 1),
            lua::get<qreal>(state, 2)
        );
    case 3:
        // QPen(const QBrush& brush, qreal width, Qt::PenStyle style)
        lua::make<QPen>(state,
            lua::get<const QBrush&>(state, 1),
            lua::get<qreal>(state, 2),
            lua::get<Qt::PenStyle>(state, 3)
        );
        break;
    case 4:
        // QPen(const QBrush& brush, qreal width, Qt::PenStyle style, Qt::PenCapStyle cap)
        lua::make<QPen>(state,
            lua::get<const QBrush&>(state, 1),
            lua::get<qreal>(state, 2),
            lua::get<Qt::PenStyle>(state, 3),
            lua::get<Qt::PenCapStyle>(state, 4)
        );
        break;
    case 5:
    default:
        // QPen(const QBrush&, qreal width, Qt::PenStyle, Qt::PenCapStyle, Qt::PenJoinStyle)
        lua::make<QPen>(state,
            lua::get<const QBrush&>(state, 1),
            lua::get<qreal>(state, 2),
            lua::get<Qt::PenStyle>(state, 3),
            lua::get<Qt::PenCapStyle>(state, 4),
            lua::get<Qt::PenJoinStyle>(state, 5)
        );
        break;
    }

    return 1;
}

int luaopen_Qt5Gui_QPen(lua_State* const state)
{
    lua::thread env(state);

    env["QPen"] = lua::value::table;
    env["QPen"]["new"] = QPen_new;

    return 0;
}

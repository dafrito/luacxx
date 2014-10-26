#include "QPixmap.hpp"

#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QSize.hpp"
#include "QPaintDevice.hpp"
#include "QColor.hpp"
#include "QBitmap.hpp"
#include "QImage.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"

int QPixmap_fill(lua_State* const state)
{
    return 0;
}

int QPixmap_loadFromData(lua_State* const state)
{
    return 0;
}

int QPixmap_transformed(lua_State* const state)
{
    return 0;
}

int QPixmap_scroll(lua_State* const state)
{
    return 0;
}

int QPixmap_scaled(lua_State* const state)
{
    return 0;
}

int QPixmap_save(lua_State* const state)
{
    return 0;
}

void lua::QPixmap_metatable(lua_State* const state, const int pos)
{
    lua::QPaintDevice_metatable(state, pos);

    lua::index mt(state, pos);
    mt["createHeuristicMask"] = &QPixmap::createHeuristicMask;
    mt["createMaskFromColor"] = &QPixmap::createMaskFromColor;
    mt["depth"] = &QPixmap::depth;
    mt["detach"] = &QPixmap::detach;
    mt["devicePixelRatio"] = &QPixmap::devicePixelRatio;
    mt["fill"] = QPixmap_fill;
    mt["hasAlpha"] = &QPixmap::hasAlpha;
    mt["hasAlphaChannel"] = &QPixmap::hasAlphaChannel;
    mt["height"] = &QPixmap::height;
    mt["isNull"] = &QPixmap::isNull;
    mt["isQBitmap"] = &QPixmap::isQBitmap;
    mt["load"] = &QPixmap::load;
    mt["loadFromData"] = QPixmap_loadFromData;
    mt["mask"] = &QPixmap::mask;
    mt["rect"] = &QPixmap::rect;
    mt["save"] = QPixmap_save;
    mt["scaled"] = QPixmap_scaled;
    mt["scaledToHeight"] = &QPixmap::scaledToHeight;
    mt["scaledToWidth"] = &QPixmap::scaledToWidth;
    mt["scroll"] = QPixmap_scroll;
    mt["setDevicePixelRatio"] = &QPixmap::setDevicePixelRatio;
    mt["setMask"] = &QPixmap::setMask;
    mt["size"] = &QPixmap::size;
    mt["swap"] = &QPixmap::swap;
    mt["toImage"] = &QPixmap::toImage;
    mt["transformed"] = QPixmap_transformed;
    mt["width"] = &QPixmap::width;
}

int QPixmap_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QPixmap()
        lua::make<QPixmap>(state);
    } else if (lua_gettop(state) == 2 && lua_type(state, 1) == LUA_TNUMBER) {
        // QPixmap(int width, int height)
        lua::make<QPixmap>(state, lua::get<int>(state, 1), lua::get<int>(state, 2));
    } else if (lua::is_type<QPixmap>(state, 1)) {
        // QPixmap(const QPixmap & pixmap)
        lua::make<QPixmap>(state, lua::get<const QPixmap&>(state, 1));
    } else if (lua::is_type<QSize>(state, 1)) {
        // QPixmap(const QSize & size)
        lua::make<QPixmap>(state, lua::get<const QSize&>(state, 1));
    } else {
        // QPixmap(const QString & fileName, const char * format = 0, Qt::ImageConversionFlags flags = Qt::AutoColor)
        switch (lua_gettop(state)) {
        case 1:
            lua::make<QPixmap>(state, lua::get<QString>(state, 1));
            break;
        case 2:
            lua::make<QPixmap>(state, lua::get<QString>(state, 1), lua::get<const char*>(state, 2));
            break;
        default:
            lua::make<QPixmap>(state, lua::get<QString>(state, 1), lua::get<const char*>(state, 2), lua::get<Qt::ImageConversionFlags>(state, 3));
            break;
        }
    }
    // TODO QPixmap(const char * const[] xpm)

    lua::make<QPixmap>(state);

    return 1;
}

int luaopen_Qt5Gui_QPixmap(lua_State* const state)
{
    lua::thread env(state);

    env["QPixmap"] = lua::value::table;
    env["QPixmap"]["new"] = QPixmap_new;

    return 0;
}

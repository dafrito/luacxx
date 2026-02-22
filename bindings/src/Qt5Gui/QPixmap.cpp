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
#include "../Qt5Core/QIODevice.hpp"
#include "../Qt5Core/QByteArray.hpp"
#include "QRegion.hpp"
#include "QTransform.hpp"
#include "QMatrix.hpp"

int QPixmap_fill(lua_State* const state)
{
    auto self = lua::get<QPixmap*>(state, 1);

    if (lua_gettop(state) == 0) {
        self->fill();
    } else {
        self->fill(lua::get<const QColor&>(state, 2));
    }
    return 0;
}

int QPixmap_loadFromData(lua_State* const state)
{
    auto self = lua::get<QPixmap*>(state, 1);

    if (lua::is_type<QByteArray>(state, 2)) {
        // bool    loadFromData(const QByteArray & data, const char * format = 0, Qt::ImageConversionFlags flags = Qt::AutoColor)
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->loadFromData(
                lua::get<const QByteArray&>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->loadFromData(
                lua::get<const QByteArray&>(state, 2),
                lua::get<const char*>(state, 3)
            ));
            break;
        case 4:
        default:
            lua::push(state, self->loadFromData(
                lua::get<const QByteArray&>(state, 2),
                lua::get<const char*>(state, 3),
                lua::get<Qt::ImageConversionFlags>(state, 4)
            ));
            break;
        }
    } else {
        // bool    loadFromData(const uchar * data, uint len, const char * format = 0, Qt::ImageConversionFlags flags = Qt::AutoColor)
        switch (lua_gettop(state)) {
        case 3:
            lua::push(state, self->loadFromData(
                lua::get<const uchar*>(state, 2),
                lua::get<uint>(state, 3)
            ));
            break;
        case 4:
            lua::push(state, self->loadFromData(
                lua::get<const uchar*>(state, 2),
                lua::get<uint>(state, 3),
                lua::get<const char*>(state, 4)
            ));
            break;
        case 5:
        default:
            lua::push(state, self->loadFromData(
                lua::get<const uchar*>(state, 2),
                lua::get<uint>(state, 3),
                lua::get<const char*>(state, 4),
                lua::get<Qt::ImageConversionFlags>(state, 5)
            ));
            break;
        }
    }
    return 1;
}

int QPixmap_transformed(lua_State* const state)
{
    auto self = lua::get<QPixmap*>(state, 1);

    if (lua::is_type<QMatrix>(state, 2)) {
        // QPixmap     transformed(const QMatrix & matrix, Qt::TransformationMode mode = Qt::FastTransformation) const
        if (lua_gettop(state) == 2) {
            lua::push(state, self->transformed(
                lua::get<const QMatrix&>(state, 2)
            ));
        } else {
            lua::push(state, self->transformed(
                lua::get<const QMatrix&>(state, 2),
                lua::get<Qt::TransformationMode>(state, 3)
            ));
        }
    } else {
        // QPixmap     transformed(const QTransform & transform, Qt::TransformationMode mode = Qt::FastTransformation) const
        if (lua_gettop(state) == 2) {
            lua::push(state, self->transformed(
                lua::get<const QTransform&>(state, 2)
            ));
        } else {
            lua::push(state, self->transformed(
                lua::get<const QTransform&>(state, 2),
                lua::get<Qt::TransformationMode>(state, 3)
            ));
        }
    }
    return 1;
}

int QPixmap_scroll(lua_State* const state)
{
    auto self = lua::get<QPixmap*>(state, 1);

    if (lua::is_type<QRect>(state, 4)) {
        // void    scroll(int dx, int dy, const QRect & rect, QRegion * exposed = 0)
        if (lua_gettop(state) > 4) {
            self->scroll(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<const QRect&>(state, 4),
                lua::get<QRegion*>(state, 5)
            );
        } else {
            self->scroll(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<const QRect&>(state, 4)
            );
        }
    } else {
        // void    scroll(int dx, int dy, int x, int y, int width, int height, QRegion * exposed = 0)
        if (lua_gettop(state) > 7) {
            self->scroll(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4),
                lua::get<int>(state, 5),
                lua::get<int>(state, 6),
                lua::get<int>(state, 7),
                lua::get<QRegion*>(state, 8)
            );
        } else {
            self->scroll(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<int>(state, 4),
                lua::get<int>(state, 5),
                lua::get<int>(state, 6),
                lua::get<int>(state, 7)
            );
        }
    }
    return 0;
}

int QPixmap_scaled(lua_State* const state)
{
    auto self = lua::get<QPixmap*>(state, 1);

    if (lua::is_type<QSize>(state, 2)) {
        // QPixmap     scaled(const QSize & size, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio, Qt::TransformationMode transformMode = Qt::FastTransformation) const
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->scaled(
                lua::get<const QSize&>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->scaled(
                lua::get<const QSize&>(state, 2),
                lua::get<Qt::AspectRatioMode>(state, 3)
            ));
            break;
        case 4:
        default:
            lua::push(state, self->scaled(
                lua::get<const QSize&>(state, 2),
                lua::get<Qt::AspectRatioMode>(state, 3),
                lua::get<Qt::TransformationMode>(state, 4)
            ));
            break;
        }
    } else {
        // QPixmap     scaled(int width, int height, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio, Qt::TransformationMode transformMode = Qt::FastTransformation) const
        switch (lua_gettop(state)) {
        case 3:
            lua::push(state, self->scaled(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3)
            ));
            break;
        case 4:
            lua::push(state, self->scaled(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<Qt::AspectRatioMode>(state, 4)
            ));
            break;
        case 5:
        default:
            lua::push(state, self->scaled(
                lua::get<int>(state, 2),
                lua::get<int>(state, 3),
                lua::get<Qt::AspectRatioMode>(state, 4),
                lua::get<Qt::TransformationMode>(state, 5)
            ));
            break;
        }
    }
    return 1;
}

int QPixmap_save(lua_State* const state)
{
    auto self = lua::get<QPixmap*>(state, 1);

    if (lua::is_type<QIODevice>(state, 2)) {
        // bool save(QIODevice * device, const char * format = 0, int quality = -1) const
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->save(
                lua::get<QIODevice*>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->save(
                lua::get<QIODevice*>(state, 2),
                lua::get<const char*>(state, 3)
            ));
            break;
        case 4:
        default:
            lua::push(state, self->save(
                lua::get<QIODevice*>(state, 2),
                lua::get<const char*>(state, 3),
                lua::get<int>(state, 4)
            ));
            break;
        }
    } else {
        // bool save(const QString & fileName, const char * format = 0, int quality = -1) const
        switch (lua_gettop(state)) {
        case 2:
            lua::push(state, self->save(
                lua::get<QString>(state, 2)
            ));
            break;
        case 3:
            lua::push(state, self->save(
                lua::get<QString>(state, 2),
                lua::get<const char*>(state, 3)
            ));
            break;
        case 4:
        default:
            lua::push(state, self->save(
                lua::get<QString>(state, 2),
                lua::get<const char*>(state, 3),
                lua::get<int>(state, 4)
            ));
            break;
        }
    }
    return 1;
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
    return 1;
}

int luaopen_Qt5Gui_QPixmap(lua_State* const state)
{
    lua::thread env(state);

    env["QPixmap"] = lua::value::table;
    env["QPixmap"]["new"] = QPixmap_new;

    return 0;
}

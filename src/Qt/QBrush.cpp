#include "QBrush.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QGradient.hpp"
#include "QMatrix.hpp"
#include "QPixmap.hpp"
#include "QImage.hpp"
#include "QTransform.hpp"

#include <QBrush>

//  void  setColor(const QColor & color)
//  void  setColor(Qt::GlobalColor color)
int QBrush_setColor(lua_State* const state)
{
    auto brush = lua::get<QBrush*>(state, 1);
    if (lua::class_name(state, 2) == lua::Metatable<QColor>::name) {
        brush->setColor(lua::get<QColor&>(state, 2));
    } else {
        brush->setColor(lua::get<Qt::GlobalColor>(state, 2));
    }
    return 0;
}

void lua::QBrush_metatable(const lua::index& mt)
{
    mt["color"] = &QBrush::color;
    mt["gradient"] = &QBrush::gradient;
    mt["isOpaque"] = &QBrush::isOpaque;
    mt["matrix"] = &QBrush::matrix;
    mt["setColor"] = QBrush_setColor;
    mt["setMatrix"] = &QBrush::setMatrix;
    mt["setStyle"] = &QBrush::setStyle;
    mt["setTexture"] = &QBrush::setTexture;
    mt["setTextureImage"] = &QBrush::setTextureImage;
    mt["setTransform"] = &QBrush::setTransform;
    mt["style"] = &QBrush::style;
    mt["swap"] = &QBrush::swap;
    mt["texture"] = &QBrush::texture;
    mt["textureImage"] = &QBrush::textureImage;
    mt["transform"] = &QBrush::transform;
}

int QBrush_new(lua_State* const state)
{
    if (lua_gettop(state) <= 1) {
        // QBrush()
        lua::make<QBrush>(state);
        return 1;
    }

    if (lua_gettop(state) == 2) {
        if (lua::is_type<QColor>(state, 2)) {
            // QBrush(const QColor & color)
            lua::make<QBrush>(state, lua::get<const QColor&>(state, 2));
            return 1;
        }
        if (lua::is_type<QPixmap>(state, 2)) {
            // QBrush(const QPixmap & pixmap)
            lua::make<QBrush>(state, lua::get<const QPixmap&>(state, 2));
            return 1;
        }
        if (lua::is_type<QImage>(state, 2)) {
            // QBrush(const QImage & image)
            lua::make<QBrush>(state, lua::get<const QImage&>(state, 2));
            return 1;
        }
        if (lua::is_type<QBrush>(state, 2)) {
            // QBrush(const QBrush & image)
            lua::make<QBrush>(state, lua::get<const QBrush&>(state, 2));
            return 1;
        }

        if (lua::is_type<Qt::BrushStyle>(state, 2)) {
            lua::make<QBrush>(state, lua::get<Qt::BrushStyle>(state, 2));
            return 1;
        }

        lua::make<QBrush>(state, lua::get<const QGradient&>(state, 2));
        return 1;
    }

    if (lua::is_type<QColor>(state, 2)) {
        if (lua::is_type<QPixmap>(state, 3)) {
            // QBrush(const QColor & color, const QPixmap & pixmap)
            lua::make<QBrush>(state,
                lua::get<const QColor&>(state, 2),
                lua::get<const QPixmap&>(state, 3)
            );
            return 1;
        }

        // QBrush(const QColor & color, Qt::BrushStyle style)
        lua::make<QBrush>(state,
            lua::get<const QColor&>(state, 2),
            lua::get<Qt::BrushStyle>(state, 3)
        );
        return 1;

    }

    if (lua::is_type<QPixmap>(state, 3)) {
        // QBrush(Qt::GlobalColor color, const QPixmap & pixmap)
        lua::make<QBrush>(state,
            lua::get<Qt::GlobalColor>(state, 2),
            lua::get<const QPixmap&>(state, 3)
        );
        return 1;
    }

    // QBrush(Qt::GlobalColor color, Qt::BrushStyle style)
    lua::make<QBrush>(state,
        lua::get<Qt::GlobalColor>(state, 2),
        lua::get<Qt::BrushStyle>(state, 3)
    );
    return 1;
}

int luaopen_luacxx_QBrush(lua_State* const state)
{
    lua::thread env(state);

    env["QBrush"] = lua::value::table;
    env["QBrush"]["new"] = QBrush_new;

    return 0;
}

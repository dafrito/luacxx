#include "QTransform.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QTransform>

int QTransform_map(lua_State* const state)
{
    auto self = lua::get<QTransform*>(state, 1);

    if (lua_gettop(state) == 2) {
        if (lua::is_type<QPointF>(state, 2)) {
            // QPointF map(const QPointF & p) const
            lua::push(state, self->map(lua::get<const QLineF&>(state, 2)));
            return 1;
        }
        if (lua::is_type<QPoint>(state, 2)) {
            // QPoint map(const QPoint & p) const
            lua::push(state, self->map(lua::get<const QPoint&>(state, 2)));
            return 1;
        }
        if (lua::is_type<QLineF>(state, 2)) {
            // QLineF map(const QLineF & p) const
            lua::push(state, self->map(lua::get<const QPointF&>(state, 2)));
            return 1;
        }
        if (lua::is_type<QLine>(state, 2)) {
            // QLine map(const QLine & p) const
            lua::push(state, self->map(lua::get<const QLine&>(state, 2)));
            return 1;
        }
        if (lua::is_type<QPolygonF>(state, 2)) {
            // QPolygonF map(const QPolygonF & p) const
            lua::push(state, self->map(lua::get<const QPolygonF&>(state, 2)));
            return 1;
        }
        if (lua::is_type<QPolygon>(state, 2)) {
            // QPolygon map(const QPolygon & p) const
            lua::push(state, self->map(lua::get<const QPolygon&>(state, 2)));
            return 1;
        }
        if (lua::is_type<QRegion>(state, 2)) {
            // QRegion map(const QRegion & p) const
            lua::push(state, self->map(lua::get<const QRegion&>(state, 2)));
            return 1;
        }

        // QPainterPath map(const QPainterPath & p) const
        lua::push(state, self->map(lua::get<const QPainterPath&>(state, 2)));
        return 1;
    }
    qreal tx=0, ty=0;

    self->map(
        lua::get<qreal>(state, 2),
        lua::get<qreal>(state, 3),
        &tx,
        &ty
    );

    lua::push(state, tx, ty);
    return 2;
}

int QTransform_mapRect(lua_State* const state)
{
    auto self = lua::get<QTransform*>(state, 1);
    if (lua::is_type<QRectF>(state, 2)) {
        // QRectF  mapRect(const QRectF & rectangle) const
        lua::push(state, self->mapRect(lua::get<const QRectF&>(state, 2)));
        return 1;
    }
    // QRect   mapRect(const QRect & rectangle) const
    lua::push(state, self->mapRect(lua::get<const QRect&>(state, 2)));
    return 1;
}

void lua::QTransform_metatable(const lua::index& mt)
{
    mt["m11"] = &QTransform::m11;
    mt["m12"] = &QTransform::m12;
    mt["m13"] = &QTransform::m13;
    mt["m21"] = &QTransform::m21;
    mt["m22"] = &QTransform::m22;
    mt["m23"] = &QTransform::m23;
    mt["m31"] = &QTransform::m31;
    mt["m32"] = &QTransform::m32;
    mt["m33"] = &QTransform::m33;
    mt["adjoint"] = &QTransform::adjoint;
    mt["determinant"] = &QTransform::determinant;
    mt["dx"] = &QTransform::dx;
    mt["dy"] = &QTransform::dy;
    mt["inverted"] = &QTransform::inverted;
    mt["isAffine"] = &QTransform::isAffine;
    mt["isIdentity"] = &QTransform::isIdentity;
    mt["isInvertible"] = &QTransform::isInvertible;
    mt["isRotating"] = &QTransform::isRotating;
    mt["isScaling"] = &QTransform::isScaling;
    mt["isTranslating"] = &QTransform::isTranslating;
    mt["map"] = QTransform_map;
    mt["mapRect"] = QTransform_mapRect;
    mt["mapToPolygon"] = &QTransform::mapToPolygon;
    mt["reset"] = &QTransform::reset;
    mt["rotate"] = &QTransform::rotate;
    mt["rotateRadians"] = &QTransform::rotateRadians;
    mt["scale"] = &QTransform::scale;
    mt["setMatrix"] = &QTransform::setMatrix;
    mt["shear"] = &QTransform::shear;
    mt["toAffine"] = &QTransform::toAffine;
    mt["translate"] = &QTransform::translate;
    mt["transposed"] = &QTransform::transposed;
    mt["type"] = &QTransform::type;
}

int QTransform_new(lua_State* const state)
{
    if (lua_gettop(state) <= 1) {
        //  QTransform()
        lua::make<QTransform>(state);
        return 1;
    }

    if (lua_gettop(state) == 7) {
        //  QTransform(
        //      qreal m11, qreal m12,
        //      qreal m21, qreal m22,
        //      qreal dx, qreal dy)
        lua::make<QTransform>(state,
            lua::get<qreal>(state, 2), // m11
            lua::get<qreal>(state, 3), // m12
            lua::get<qreal>(state, 4), // m21
            lua::get<qreal>(state, 5), // m22
            lua::get<qreal>(state, 6), // dx
            lua::get<qreal>(state, 7) // dy
        );
        return 1;
    }

    if (lua_gettop(state) == 2) {
        // QTransform(const QMatrix & matrix)
        lua::make<QTransform>(state, lua::get<const QMatrix&>(state, 2));
        return 1;
    }

    if (lua_gettop(state) == 9) {
        lua::make<QTransform>(state,
            lua::get<qreal>(state, 2), // m11
            lua::get<qreal>(state, 3), // m12
            lua::get<qreal>(state, 4), // m13
            lua::get<qreal>(state, 5), // m21
            lua::get<qreal>(state, 6), // m22
            lua::get<qreal>(state, 7), // m23
            lua::get<qreal>(state, 8), // m31
            lua::get<qreal>(state, 9) // m32
        );
        return 1;
    }

    lua::make<QTransform>(state,
        lua::get<qreal>(state, 2), // m11
        lua::get<qreal>(state, 3), // m12
        lua::get<qreal>(state, 4), // m13
        lua::get<qreal>(state, 5), // m21
        lua::get<qreal>(state, 6), // m22
        lua::get<qreal>(state, 7), // m23
        lua::get<qreal>(state, 8), // m31
        lua::get<qreal>(state, 9), // m32
        lua::get<qreal>(state, 10) // m33
    );

    return 1;
}

int luaopen_Qt5Gui_QTransform(lua_State* const state)
{
    lua::thread env(state);

    env["QTransform"] = lua::value::table;
    env["QTransform"]["new"] = QTransform_new;

    return 0;
}

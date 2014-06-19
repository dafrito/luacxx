#include "QTransform.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QTransform>

int QTransform_map(lua_State* const state)
{
    return 0;
}

int QTransform_mapRect(lua_State* const state)
{
    return 0;
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
    lua::make<QTransform>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QTransform(lua_State* const state)
{
    lua::thread env(state);

    env["QTransform"] = lua::value::table;
    env["QTransform"]["new"] = QTransform_new;

    return 0;
}

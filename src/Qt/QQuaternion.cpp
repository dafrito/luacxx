#include "QQuaternion.hpp"
#include "QVector3D.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "../type/numeric.hpp"

#include <QQuaternion>

int QQuaternion_setVector(lua::state* const state)
{
    return 0;
}

int QQuaternion_mul(lua::state* const state)
{
    auto quat = lua::make<QQuaternion>(
        state, lua::get<QQuaternion&>(state, 1)
    );
    *quat *= lua::get<QQuaternion&>(state, 2);
    return 1;
}

int QQuaternion_multiply(lua::state* const state)
{
    auto quat = lua::get<QQuaternion&>(state, 1);
    quat *= lua::get<QQuaternion&>(state, 2);
    lua_settop(state, 1);
    return 1;
}

std::string QQuaternion_tostring(const QQuaternion& quat)
{
    std::stringstream str;
    str << "QQuaternion("
        << "scalar: " << quat.scalar()
        << ", vector: (" << quat.x()
        << ", " << quat.y()
        << ", " << quat.z()
        << "))";

    return str.str();
}

void lua::QQuaternion_metatable(const lua::index& mt)
{
    mt["conjugate"] = &QQuaternion::conjugate;
    mt["isIdentity"] = &QQuaternion::isIdentity;
    mt["isNull"] = &QQuaternion::isNull;
    mt["length"] = &QQuaternion::length;
    mt["lengthSquared"] = &QQuaternion::lengthSquared;
    mt["normalize"] = &QQuaternion::normalize;
    mt["normalized"] = &QQuaternion::normalized;
    mt["rotatedVector"] = &QQuaternion::rotatedVector;
    mt["scalar"] = &QQuaternion::scalar;
    mt["setScalar"] = &QQuaternion::setScalar;
    mt["setVector"] = QQuaternion_setVector;
    mt["setX"] = &QQuaternion::setX;
    mt["setY"] = &QQuaternion::setY;
    mt["setZ"] = &QQuaternion::setZ;
    mt["toVector4D"] = &QQuaternion::toVector4D;
    mt["vector"] = &QQuaternion::vector;
    mt["x"] = &QQuaternion::x;
    mt["y"] = &QQuaternion::y;
    mt["z"] = &QQuaternion::z;
    mt["__mul"] = QQuaternion_mul;
    mt["multiply"] = QQuaternion_multiply;
    mt["__tostring"] = QQuaternion_tostring;
}

int QQuaternion_new(lua::state* const state)
{
    switch (lua_gettop(state)) {
    case 1:
        lua::make<QQuaternion>(state);
        break;
    case 5:
        lua::make<QQuaternion>(state,
            lua::get<float>(state, 2), // scalar
            lua::get<float>(state, 3), // xpos
            lua::get<float>(state, 4), // ypos
            lua::get<float>(state, 5)  // zpos
        );
        break;
    }
    return 1;
}

int luaopen_luacxx_QQuaternion(lua::state* const state)
{
    lua::thread env(state);

    env["QQuaternion"] = lua::value::table;
    env["QQuaternion"]["new"] = QQuaternion_new;

    return 0;
}

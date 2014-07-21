#include "QQuaternion.hpp"

#include "QVector3D.hpp"
#include "../convert/numeric.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

int QQuaternion_setVector(lua_State* const state)
{
    return 0;
}

int QQuaternion_mul(lua_State* const state)
{
    auto quat = lua::make<QQuaternion>(
        state, lua::get<QQuaternion&>(state, 1)
    );
    *quat *= lua::get<QQuaternion&>(state, 2);
    return 1;
}

int QQuaternion_multiply(lua_State* const state)
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

int QQuaternion_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 1:
        lua::make<QQuaternion>(state);
        break;
    case 3:
        lua::make<QQuaternion>(state,
            lua::get<float>(state, 2), // scalar
            lua::get<const QVector3D&>(state, 3)
        );
        break;
    default:
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

int QQuaternion_benchmark(lua_State* const state)
{
    auto MAX = lua::get<int>(state, 1);
    QQuaternion quat(2, 3, 7, 5);
    for (int i = 0; i < MAX; ++i) {
        quat = quat * QQuaternion(2, 2, 2, 2);
        quat.normalize();
    }
    lua::push(state, quat);
    return 1;
}

int luaopen_Qt5Gui_QQuaternion(lua_State* const state)
{
    lua::thread env(state);

    env["QQuaternion"] = lua::value::table;
    env["QQuaternion"]["new"] = QQuaternion_new;
    env["QQuaternion"]["benchmark"] = QQuaternion_benchmark;

    return 0;
}

#include "QConicalGradient.hpp"
#include "../luacxx/type/function.hpp"
#include "../luacxx/thread.hpp"
#include "QPointF.hpp"

#include <QConicalGradient>

int QConicalGradient_setCenter(lua_State* const state)
{
    auto self = lua::get<QConicalGradient*>(state, 1);
    if (lua_gettop(state) < 3) {
        self->setCenter(lua::get<const QPointF&>(state, 2));
    }
    self->setCenter(lua::get<qreal>(state, 2), lua::get<qreal>(state, 3));
    return 0;
}

void lua::QConicalGradient_metatable(const lua::index& mt)
{
    mt["angle"] = &QConicalGradient::angle;
    mt["center"] = &QConicalGradient::center;
    mt["setAngle"] = &QConicalGradient::setAngle;
    mt["setCenter"] = QConicalGradient_setCenter;
}

int QConicalGradient_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
    case 0:
    case 1:
        lua::make<QConicalGradient>(state);
        break;
    case 3:
        lua::make<QConicalGradient>(state,
            lua::get<const QPointF&>(state, 2),
            lua::get<qreal>(state, 3)
        );
    case 4:
        lua::make<QConicalGradient>(state,
            lua::get<qreal>(state, 2)
            lua::get<qreal>(state, 3)
            lua::get<qreal>(state, 4)
        );
    default:
    }

    return 1;
}

int luaopen_luacxx_QConicalGradient(lua_State* const state)
{
    lua::thread env(state);

    env["QConicalGradient"] = lua::value::table;
    env["QConicalGradient"]["new"] = QConicalGradient_new;

    return 0;
}

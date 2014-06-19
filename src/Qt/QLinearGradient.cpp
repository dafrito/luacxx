#include "QLinearGradient.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QGradient.hpp"

#include <QLinearGradient>

int QLinearGradient_setStart(lua_State* const state)
{
    auto self = lua::get<QLinearGradient*>(state, 1);

    switch (lua_gettop(state)) {
        case 0:
        case 1:
            throw lua::error("QLinearGradient:setStart(qreal, qreal) or QLinearGradient:setStart(QPointF)");
        case 2:
        {
            self->setStart(lua::get<const QPointF&>(state, 2));
            break;
        }
        case 3:
        default:
        {
            self->setStart(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3)
            );
            break;
        }
    }
    return 0;
}

int QLinearGradient_setFinalStop(lua_State* const state)
{
    auto self = lua::get<QLinearGradient*>(state, 1);

    switch (lua_gettop(state)) {
        case 0:
        case 1:
            throw lua::error("QLinearGradient:setFinalStop(qreal, qreal) or QLinearGradient:setFinalStop(QPointF)");
        case 2:
        {
            self->setFinalStop(lua::get<const QPointF&>(state, 2));
            break;
        }
        case 3:
        default:
        {
            self->setFinalStop(
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3)
            );
            break;
        }
    }
    return 0;
}

void lua::QLinearGradient_metatable(const lua::index& mt)
{
    lua::QGradient_metatable(mt);

    mt["finalStop"] = &QLinearGradient::finalStop;
    mt["setFinalStop"] = QLinearGradient_setFinalStop;
    mt["setStart"] = QLinearGradient_setStart;
    mt["start"] = &QLinearGradient::start;
}

int QLinearGradient_new(lua_State* const state)
{
    switch (lua_gettop(state)) {
        case 0:
        case 1:
            lua::make<QLinearGradient>(state);
            break;
        case 2:
            lua::make<QLinearGradient>(state,
                lua::get<const QPointF&>(state, 2),
                lua::get<const QPointF&>(state, 3)
            );
            break;
        case 3:
            throw lua::error("QLinearGradient:new(), QLinearGradient:new(QPointF, QPointF), or QLinearGradient:new(qreal, qreal, qreal, qreal)");
        case 4:
        default:
            lua::make<QLinearGradient>(state,
                lua::get<qreal>(state, 2),
                lua::get<qreal>(state, 3),
                lua::get<qreal>(state, 4),
                lua::get<qreal>(state, 5)
            );
            break;
    }

    return 1;
}

int luaopen_luacxx_QLinearGradient(lua_State* const state)
{
    lua::thread env(state);

    env["QLinearGradient"] = lua::value::table;
    env["QLinearGradient"]["new"] = QLinearGradient_new;

    return 0;
}

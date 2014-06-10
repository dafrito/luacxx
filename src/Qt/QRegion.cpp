#include "QRegion.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QRect.hpp"

#include <QRegion>

void lua::QRegion_metatable(const lua::index& mt)
{
    mt["boundingRect"] = &QRegion::boundingRect;
    //mt["contains"] = &QRegion::contains;
    //mt["intersected"] = &QRegion::intersected;
    //mt["intersects"] = &QRegion::intersects;
    mt["isEmpty"] = &QRegion::isEmpty;
    mt["isNull"] = &QRegion::isNull;
    mt["rectCount"] = &QRegion::rectCount;
    //mt["rects"] = &QRegion::rects;
    //mt["setRects"] = &QRegion::setRects;
    mt["subtracted"] = &QRegion::subtracted;
    mt["swap"] = &QRegion::swap;
    //mt["translate"] = &QRegion::translate;
    //mt["translated"] = &QRegion::translated;
    //mt["united"] = &QRegion::united;
    mt["xored"] = &QRegion::xored;
}

int QRegion_new(lua_State* const state)
{
    lua::make<QRegion>(state);

    auto name = lua::class_name(lua::index(state, 2));
    if (name == lua::Metatable<QRect>::name) {
        if (lua_gettop(state) > 2) {
            lua::make<QRegion>(state,
                lua::get<QRect>(state, 2)
            );
        } else {
            lua::make<QRegion>(state, lua::get<QRect>(state, 2));
        }
    } else {
        lua::make<QRegion>(state);
    }
    return 1;
}

int luaopen_luacxx_QRegion(lua_State* const state)
{
    lua::thread env(state);

    env["QRegion"] = lua::value::table;
    env["QRegion"]["new"] = QRegion_new;

    return 0;
}

#include "QMarginsF.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QMargins.hpp"

namespace lua {

void QMarginsF_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["bottom"] = &QMarginsF::bottom;
    mt["isNull"] = &QMarginsF::isNull;
    mt["left"] = &QMarginsF::left;
    mt["right"] = &QMarginsF::right;
    mt["setBottom"] = &QMarginsF::setBottom;
    mt["setLeft"] = &QMarginsF::setLeft;
    mt["setRight"] = &QMarginsF::setRight;
    mt["setTop"] = &QMarginsF::setTop;
    mt["toMargins"] = &QMarginsF::toMargins;
    mt["top"] = &QMarginsF::top;
}

} // namespace lua

int QMarginsF_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QMarginsF()
        lua::make<QMarginsF>(state);
    } else if (lua_gettop(state) > 1) {
        // QMarginsF(qreal left, qreal top, qreal right, qreal bottom)
        lua::make<QMarginsF>(state,
            lua::get<qreal>(state, 1),
            lua::get<qreal>(state, 2),
            lua::get<qreal>(state, 3),
            lua::get<qreal>(state, 4)
        );
    } else {
        // QMarginsF(const QMargins & margins)
        lua::make<QMarginsF>(state, lua::get<const QMargins&>(state, 1));
    }
    return 1;
}

int luaopen_Qt5Core_QMarginsF(lua_State* const state)
{
    lua::thread env(state);

    env["QMarginsF"] = lua::value::table;
    env["QMarginsF"]["new"] = QMarginsF_new;
    auto t = env["QMarginsF"];

    return 0;
}

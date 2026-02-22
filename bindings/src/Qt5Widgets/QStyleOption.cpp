#include "QStyleOption.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QWidget.hpp"

namespace lua {

void QStyleOption_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);

    mt["initFrom"] = &QStyleOption::initFrom;

    // TODO Public Variables
    // Qt::LayoutDirection  direction
    // QFontMetrics     fontMetrics
    // QPalette     palette
    // QRect    rect
    // QStyle::State    state
    // QObject *    styleObject
    // int  type
    // int  version
}

} // namespace lua

int QStyleOption_new(lua_State* const state)
{
    // TODO QStyleOption
    // QStyleOption(int version = QStyleOption::Version, int type = SO_Default)
    // QStyleOption(const QStyleOption & other)
    lua::make<QStyleOption>(state);
    return 1;
}

int luaopen_Qt5Widgets_QStyleOption(lua_State* const state)
{
    lua::thread env(state);

    env["QStyleOption"] = lua::value::table;
    env["QStyleOption"]["new"] = QStyleOption_new;
    auto t = env["QStyleOption"];

    return 0;
}

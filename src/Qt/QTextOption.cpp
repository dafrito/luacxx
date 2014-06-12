#include "QTextOption.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QTextOption>

void lua::QTextOption_metatable(const lua::index& mt)
{
    mt["alignment"] = &QTextOption::alignment;
    mt["flags"] = &QTextOption::flags;
    mt["setAlignment"] = &QTextOption::setAlignment;
    mt["setFlags"] = &QTextOption::setFlags;
    mt["setTabArray"] = &QTextOption::setTabArray;
    mt["setTabStop"] = &QTextOption::setTabStop;
    mt["setTabs"] = &QTextOption::setTabs;
    mt["setTextDirection"] = &QTextOption::setTextDirection;
    mt["setUseDesignMetrics"] = &QTextOption::setUseDesignMetrics;
    mt["setWrapMode"] = &QTextOption::setWrapMode;
    mt["tabArray"] = &QTextOption::tabArray;
    mt["tabStop"] = &QTextOption::tabStop;
    mt["tabs"] = &QTextOption::tabs;
    mt["textDirection"] = &QTextOption::textDirection;
    mt["useDesignMetrics"] = &QTextOption::useDesignMetrics;
    mt["wrapMode"] = &QTextOption::wrapMode;
}

int QTextOption_new(lua::state* const state)
{
    if (lua_gettop(state) < 2) {
        lua::make<QTextOption>(state);
        return 1;
    }

    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QTextOption(lua::state* const state)
{
    lua::thread env(state);

    env["QTextOption"] = lua::value::table;
    env["QTextOption"]["new"] = QTextOption_new;

    return 0;
}

#include "QTextOption.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"

void lua::QTextOption_Tab_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    // TODO Implement QTextOption::Tab
}

void lua::QTextOption_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
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

int QTextOption_new(lua_State* const state)
{
    if (lua_gettop(state) < 2) {
        lua::make<QTextOption>(state);
        return 1;
    }

    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Gui_QTextOption(lua_State* const state)
{
    lua::thread env(state);

    env["QTextOption"] = lua::value::table;
    env["QTextOption"]["new"] = QTextOption_new;
    auto t = env["QTextOption"];

    // enum QTextOption::Flag
    t["IncludeTrailingSpaces"] = QTextOption::IncludeTrailingSpaces;
    t["ShowTabsAndSpaces"] = QTextOption::ShowTabsAndSpaces;
    t["ShowLineAndParagraphSeparators"] = QTextOption::ShowLineAndParagraphSeparators;
    t["AddSpaceForLineAndParagraphSeparators"] = QTextOption::AddSpaceForLineAndParagraphSeparators;
    t["SuppressColors"] = QTextOption::SuppressColors;

    // enum QTextOption::TabType
    t["LeftTab"] = QTextOption::LeftTab;
    t["RightTab"] = QTextOption::RightTab;
    t["CenterTab"] = QTextOption::CenterTab;
    t["DelimiterTab"] = QTextOption::DelimiterTab;

    // enum QTextOption::WrapMode
    t["NoWrap"] = QTextOption::NoWrap;
    t["WordWrap"] = QTextOption::WordWrap;
    t["ManualWrap"] = QTextOption::ManualWrap;
    t["WrapAnywhere"] = QTextOption::WrapAnywhere;
    t["WrapAtWordBoundaryOrAnywhere"] = QTextOption::WrapAtWordBoundaryOrAnywhere;

    return 0;
}

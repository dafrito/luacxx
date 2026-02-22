#include "QStaticText.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QTransform.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QSizeF.hpp"
#include "../Qt5Core/Qt.hpp"
#include "QTextOption.hpp"

void lua::QStaticText_metatable(lua_State* const state, const int pos)
{
    lua::metatable mt(state, pos);

     mt["performanceHint"] = &QStaticText::performanceHint;
     mt["prepare"] = QStaticText_prepare;
     mt["setPerformanceHint"] = &QStaticText::setPerformanceHint;
     mt["setText"] = &QStaticText::setText;
     mt["setTextFormat"] = &QStaticText::setTextFormat;
     mt["setTextOption"] = &QStaticText::setTextOption;
     mt["setTextWidth"] = &QStaticText::setTextWidth;
     mt["size"] = &QStaticText::size;
     mt["swap"] = &QStaticText::swap;
     mt["text"] = &QStaticText::text;
     mt["textFormat"] = &QStaticText::textFormat;
     mt["textOption"] = &QStaticText::textOption;
     mt["textWidth"] = &QStaticText::textWidth;
}

int QStaticText_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QStaticText()
        lua::make<QStaticText>(state);
    } else if (lua::is_type<QStaticText>(state, 1)) {
        // QStaticText(const QStaticText & other)
        lua::make<QStaticText>(state, lua::get<const QStaticText&>(state, 1));
    } else if (lua::is_type<QString>(state, 1)) {
        // QStaticText(const QString & text)
        lua::make<QStaticText>(state, lua::get<const QString&>(state, 1));
    } else {
        // QStaticText(const QString & text)
        lua::make<QStaticText>(state, lua::get<QString>(state, 1));
    }
    return 1;
}

int luaopen_Qt5Gui_QStaticText(lua_State* const state)
{
    lua::thread env(state);

    env["QStaticText"] = lua::value::table;
    env["QStaticText"]["new"] = QStaticText_new;
    auto t = env["QStaticText"];

    // enum QStaticText::PerformanceHint
    t["ModerateCaching"] = QStaticText::ModerateCaching;
    t["AggressiveCaching"] = QStaticText::AggressiveCaching;

    return 0;
}

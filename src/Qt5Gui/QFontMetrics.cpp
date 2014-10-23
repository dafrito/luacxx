#include "QFontMetrics.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QChar.hpp"
#include "QFont.hpp"
#include "QPaintDevice.hpp"

// http://qt-project.org/doc/qt-5/qfontmetrics.html

int QFontMetrics_boundingRect(lua_State* const state)
{
    return 0;
}

int QFontMetrics_width(lua_State* const state)
{
    return 0;
}

void lua::QFontMetrics_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["ascent"] = &QFontMetrics::ascent;
    mt["averageCharWidth"] = &QFontMetrics::averageCharWidth;
    mt["boundingRect"] = QFontMetrics_boundingRect;
    mt["descent"] = &QFontMetrics::descent;
    mt["elidedText"] = &QFontMetrics::elidedText;
    mt["height"] = &QFontMetrics::height;
    mt["inFont"] = &QFontMetrics::inFont;
    mt["inFontUcs4"] = &QFontMetrics::inFontUcs4;
    mt["leading"] = &QFontMetrics::leading;
    mt["leftBearing"] = &QFontMetrics::leftBearing;
    mt["lineSpacing"] = &QFontMetrics::lineSpacing;
    mt["lineWidth"] = &QFontMetrics::lineWidth;
    mt["maxWidth"] = &QFontMetrics::maxWidth;
    mt["minLeftBearing"] = &QFontMetrics::minLeftBearing;
    mt["minRightBearing"] = &QFontMetrics::minRightBearing;
    mt["overlinePos"] = &QFontMetrics::overlinePos;
    mt["rightBearing"] = &QFontMetrics::rightBearing;
    mt["size"] = &QFontMetrics::size;
    mt["strikeOutPos"] = &QFontMetrics::strikeOutPos;
    mt["swap"] = &QFontMetrics::swap;
    mt["tightBoundingRect"] = &QFontMetrics::tightBoundingRect;
    mt["underlinePos"] = &QFontMetrics::underlinePos;
    mt["width"] = QFontMetrics_width;
    mt["xHeight"] = &QFontMetrics::xHeight;
}

int QFontMetrics_new(lua_State* const state)
{
    if (lua::is_type<QFontMetrics>(state, 2)) {
        lua::make<QFontMetrics>(state, lua::get<const QFontMetrics&>(state, 2));
        return 1;
    }

    if (lua_gettop(state) > 2) {
        lua::make<QFontMetrics>(state,
            lua::get<const QFont&>(state, 2),
            lua::get<QPaintDevice*>(state, 3)
        );
        return 1;
    }

    lua::make<QFontMetrics>(state,
        lua::get<const QFont&>(state, 2)
    );
    return 1;
}

int luaopen_Qt5Gui_QFontMetrics(lua_State* const state)
{
    lua::thread env(state);

    env["QFontMetrics"] = lua::value::table;
    env["QFontMetrics"]["new"] = QFontMetrics_new;

    return 0;
}

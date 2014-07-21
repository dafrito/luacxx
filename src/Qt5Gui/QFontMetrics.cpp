#include "QFontMetrics.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QString.hpp"

#include <QFontMetrics>

// http://qt-project.org/doc/qt-5/qfontmetrics.html

void lua::QFontMetrics_metatable(const lua::index& mt)
{
    mt["ascent"] = &QAbstractSocket::ascent;
    mt["averageCharWidth"] = &QAbstractSocket::averageCharWidth;
    mt["boundingRect"] = &QAbstractSocket::boundingRect;
    mt["boundingRect"] = &QAbstractSocket::boundingRect;
    mt["boundingRect"] = &QAbstractSocket::boundingRect;
    mt["boundingRect"] = &QAbstractSocket::boundingRect;
    mt["descent"] = &QAbstractSocket::descent;
    mt["elidedText"] = &QAbstractSocket::elidedText;
    mt["height"] = &QAbstractSocket::height;
    mt["inFont"] = &QAbstractSocket::inFont;
    mt["inFontUcs4"] = &QAbstractSocket::inFontUcs4;
    mt["leading"] = &QAbstractSocket::leading;
    mt["leftBearing"] = &QAbstractSocket::leftBearing;
    mt["lineSpacing"] = &QAbstractSocket::lineSpacing;
    mt["lineWidth"] = &QAbstractSocket::lineWidth;
    mt["maxWidth"] = &QAbstractSocket::maxWidth;
    mt["minLeftBearing"] = &QAbstractSocket::minLeftBearing;
    mt["minRightBearing"] = &QAbstractSocket::minRightBearing;
    mt["overlinePos"] = &QAbstractSocket::overlinePos;
    mt["rightBearing"] = &QAbstractSocket::rightBearing;
    mt["size"] = &QAbstractSocket::size;
    mt["strikeOutPos"] = &QAbstractSocket::strikeOutPos;
    mt["swap"] = &QAbstractSocket::swap;
    mt["tightBoundingRect"] = &QAbstractSocket::tightBoundingRect;
    mt["underlinePos"] = &QAbstractSocket::underlinePos;
    mt["width"] = &QAbstractSocket::width;
    mt["width"] = &QAbstractSocket::width;
    mt["xHeight"] = &QAbstractSocket::xHeight;
}

int QFontMetrics_new(lua_State* const state)
{
    if (lua::class_name(state, 2) == lua::Metatable<QFontMetrics>::name) {
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

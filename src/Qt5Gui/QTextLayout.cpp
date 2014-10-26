#include "QTextLayout.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QVector.hpp"
#include "../Qt5Core/QString.hpp"
#include "QTextLine.hpp"
#include "QPainter.hpp"
#include "QFont.hpp"
#include "QGlyphRun.hpp"
#include "QTextOption.hpp"

int QTextLayout_draw(lua_State* const state)
{
    return 0;
}
int QTextLayout_drawCursor(lua_State* const state)
{
    return 0;
}
int QTextLayout_glyphRuns(lua_State* const state)
{
    return 0;
}
int QTextLayout_nextCursorPosition(lua_State* const state)
{
    return 0;
}
int QTextLayout_previousCursorPosition(lua_State* const state)
{
    return 0;
}

namespace lua {

void QTextLayout_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["additionalFormats"] = &QTextLayout::additionalFormats;
    mt["beginLayout"] = &QTextLayout::beginLayout;
    mt["boundingRect"] = &QTextLayout::boundingRect;
    mt["cacheEnabled"] = &QTextLayout::cacheEnabled;
    mt["clearAdditionalFormats"] = &QTextLayout::clearAdditionalFormats;
    mt["clearLayout"] = &QTextLayout::clearLayout;
    mt["createLine"] = &QTextLayout::createLine;
    mt["cursorMoveStyle"] = &QTextLayout::cursorMoveStyle;
    mt["draw"] = QTextLayout_draw;
    mt["drawCursor"] = QTextLayout_drawCursor;
    mt["endLayout"] = &QTextLayout::endLayout;
    mt["font"] = &QTextLayout::font;
    mt["glyphRuns"] = QTextLayout_glyphRuns;
    mt["isValidCursorPosition"] = &QTextLayout::isValidCursorPosition;
    mt["leftCursorPosition"] = &QTextLayout::leftCursorPosition;
    mt["lineAt"] = &QTextLayout::lineAt;
    mt["lineCount"] = &QTextLayout::lineCount;
    mt["lineForTextPosition"] = &QTextLayout::lineForTextPosition;
    mt["maximumWidth"] = &QTextLayout::maximumWidth;
    mt["minimumWidth"] = &QTextLayout::minimumWidth;
    mt["nextCursorPosition"] = QTextLayout_nextCursorPosition;
    mt["position"] = &QTextLayout::position;
    mt["preeditAreaPosition"] = &QTextLayout::preeditAreaPosition;
    mt["preeditAreaText"] = &QTextLayout::preeditAreaText;
    mt["previousCursorPosition"] = QTextLayout_previousCursorPosition;
    mt["rightCursorPosition"] = &QTextLayout::rightCursorPosition;
    mt["setAdditionalFormats"] = &QTextLayout::setAdditionalFormats;
    mt["setCacheEnabled"] = &QTextLayout::setCacheEnabled;
    mt["setCursorMoveStyle"] = &QTextLayout::setCursorMoveStyle;
    mt["setFont"] = &QTextLayout::setFont;
    mt["setPosition"] = &QTextLayout::setPosition;
    mt["setPreeditArea"] = &QTextLayout::setPreeditArea;
    mt["setText"] = &QTextLayout::setText;
    mt["setTextOption"] = &QTextLayout::setTextOption;
    mt["text"] = &QTextLayout::text;
    mt["textOption"] = &QTextLayout::textOption;
}

} // namespace lua

int QTextLayout_new(lua_State* const state)
{
    if (lua_gettop(state) == 0) {
        // QTextLayout()
        lua::make<QTextLayout>(state);
    } else if(lua_gettop(state) > 1) {
        // QTextLayout(const QString & text, const QFont & font, QPaintDevice * paintdevice = 0)
        if (lua::is_type<QString>(state, 1)) {
            if (lua_gettop(state) > 2) {
                lua::make<QTextLayout>(state,
                    lua::get<const QString&>(state, 1),
                    lua::get<const QFont&>(state, 2),
                    lua::get<QPaintDevice*>(state, 3)
                );
            } else {
                lua::make<QTextLayout>(state,
                    lua::get<const QString&>(state, 1),
                    lua::get<const QFont&>(state, 2)
                );
            }
        } else {
            if (lua_gettop(state) > 2) {
                lua::make<QTextLayout>(state,
                    lua::get<QString>(state, 1),
                    lua::get<const QFont&>(state, 2),
                    lua::get<QPaintDevice*>(state, 3)
                );
            } else {
                lua::make<QTextLayout>(state,
                    lua::get<QString>(state, 1),
                    lua::get<const QFont&>(state, 2)
                );
            }
        }
    } else if (lua::is_type<QString>(state, 1)) {
        // QTextLayout(const QString & text)
        lua::make<QTextLayout>(state, lua::get<const QString&>(state, 1));
    } else {
        lua::make<QTextLayout>(state, lua::get<QString>(state, 1));
    }

    return 1;
}

int luaopen_Qt5Gui_QTextLayout(lua_State* const state)
{
    lua::thread env(state);

    env["QTextLayout"] = lua::value::table;
    env["QTextLayout"]["new"] = QTextLayout_new;
    auto t = env["QTextLayout"];

    // enum QTextLayout::CursorMode
    t["SkipCharacters"] = QTextLayout::SkipCharacters;
    t["SkipWords"] = QTextLayout::SkipWords;

    return 0;
}

#include "QTextLine.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QPainter.hpp"
#include "../Qt5Core/QPointF.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QList.hpp"
#include "QGlyphRun.hpp"
#include "QTextLayout.hpp"

int QTextLine_draw(lua_State* const state)
{
    return 0;
}
int QTextLine_glyphRuns(lua_State* const state)
{
    return 0;
}
int QTextLine_setNumColumns(lua_State* const state)
{
    return 0;
}
int QTextLine_xToCursor(lua_State* const state)
{
    return 0;
}
int QTextLine_cursorToX(lua_State* const state)
{
    return 0;
}

namespace lua {

void QTextLine_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["ascent"] = &QTextLine::ascent;
    mt["cursorToX"] = QTextLine_cursorToX;
    mt["descent"] = &QTextLine::descent;
    mt["draw"] = QTextLine_draw;
    mt["glyphRuns"] = QTextLine_glyphRuns;
    mt["height"] = &QTextLine::height;
    mt["horizontalAdvance"] = &QTextLine::horizontalAdvance;
    mt["isValid"] = &QTextLine::isValid;
    mt["leading"] = &QTextLine::leading;
    mt["leadingIncluded"] = &QTextLine::leadingIncluded;
    mt["lineNumber"] = &QTextLine::lineNumber;
    mt["naturalTextRect"] = &QTextLine::naturalTextRect;
    mt["naturalTextWidth"] = &QTextLine::naturalTextWidth;
    mt["position"] = &QTextLine::position;
    mt["rect"] = &QTextLine::rect;
    mt["setLeadingIncluded"] = &QTextLine::setLeadingIncluded;
    mt["setLineWidth"] = &QTextLine::setLineWidth;
    mt["setNumColumns"] = QTextLine_setNumColumns;
    mt["setPosition"] = &QTextLine::setPosition;
    mt["textLength"] = &QTextLine::textLength;
    mt["textStart"] = &QTextLine::textStart;
    mt["width"] = &QTextLine::width;
    mt["x"] = &QTextLine::x;
    mt["xToCursor"] = QTextLine_xToCursor;
    mt["y"] = &QTextLine::y;
}

} // namespace lua

int QTextLine_new(lua_State* const state)
{
    lua::make<QTextLine>(state);
    return 1;
}

int luaopen_Qt5Gui_QTextLine(lua_State* const state)
{
    lua::thread env(state);

    env["QTextLine"] = lua::value::table;
    env["QTextLine"]["new"] = QTextLine_new;
    auto t = env["QTextLine"];

    // enum QTextLine::CursorPosition
    t["CursorBetweenCharacters"] = QTextLine::CursorBetweenCharacters;
    t["CursorOnCharacter"] = QTextLine::CursorOnCharacter;

    // enum QTextLine::Edge
    t["Leading"] = QTextLine::Leading;
    t["Trailing"] = QTextLine::Trailing;

    return 0;
}

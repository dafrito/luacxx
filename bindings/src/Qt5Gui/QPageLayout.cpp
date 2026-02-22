#include "QPageLayout.hpp"
#include "../convert/callable.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Core/QMargins.hpp"
#include "../Qt5Core/QMarginsF.hpp"
#include "QPageSize.hpp"

int QPageLayout_fullRect(lua_State* const state)
{
    return 0;
}
int QPageLayout_margins(lua_State* const state)
{
    return 0;
}
int QPageLayout_paintRect(lua_State* const state)
{
    return 0;
}
int QPageLayout_setPageSize(lua_State* const state)
{
    return 0;
}

namespace lua {

void QPageLayout_metatable(lua_State* const state, const int pos)
{
    lua::index mt(state, pos);
    mt["fullRect"] = QPageLayout_fullRect;
    mt["fullRectPixels"] = &QPageLayout::fullRectPixels;
    mt["fullRectPoints"] = &QPageLayout::fullRectPoints;
    mt["isEquivalentTo"] = &QPageLayout::isEquivalentTo;
    mt["isValid"] = &QPageLayout::isValid;
    mt["margins"] = QPageLayout_margins;
    mt["marginsPixels"] = &QPageLayout::marginsPixels;
    mt["marginsPoints"] = &QPageLayout::marginsPoints;
    mt["maximumMargins"] = &QPageLayout::maximumMargins;
    mt["minimumMargins"] = &QPageLayout::minimumMargins;
    mt["mode"] = &QPageLayout::mode;
    mt["orientation"] = &QPageLayout::orientation;
    mt["pageSize"] = &QPageLayout::pageSize;
    mt["paintRect"] = QPageLayout_paintRect;
    mt["paintRectPixels"] = &QPageLayout::paintRectPixels;
    mt["paintRectPoints"] = &QPageLayout::paintRectPoints;
    mt["setBottomMargin"] = &QPageLayout::setBottomMargin;
    mt["setLeftMargin"] = &QPageLayout::setLeftMargin;
    mt["setMargins"] = &QPageLayout::setMargins;
    mt["setMinimumMargins"] = &QPageLayout::setMinimumMargins;
    mt["setMode"] = &QPageLayout::setMode;
    mt["setOrientation"] = &QPageLayout::setOrientation;
    mt["setPageSize"] = QPageLayout_setPageSize;
    mt["setRightMargin"] = &QPageLayout::setRightMargin;
    mt["setTopMargin"] = &QPageLayout::setTopMargin;
    mt["setUnits"] = &QPageLayout::setUnits;
    mt["swap"] = &QPageLayout::swap;
    mt["units"] = &QPageLayout::units;
}

} // namespace lua

int QPageLayout_new(lua_State* const state)
{
    // TODO QPageLayout(const QPageSize & pageSize, Orientation orientation, const QMarginsF & margins, Unit units = Point, const QMarginsF & minMargins = QMarginsF( 0, 0, 0, 0 ))
    // TODO QPageLayout(const QPageLayout & other)
    // QPageLayout()
    lua::make<QPageLayout>(state);

    return 1;
}

int luaopen_Qt5Gui_QPageLayout(lua_State* const state)
{
    lua::thread env(state);

    env["QPageLayout"] = lua::value::table;
    env["QPageLayout"]["new"] = QPageLayout_new;
    auto t = env["QPageLayout"];

    // enum QPageLayout::Mode
    t["StandardMode"] = QPageLayout::StandardMode;
    t["FullPageMode"] = QPageLayout::FullPageMode;

    // enum QPageLayout::Orientation
    t["Portrait"] = QPageLayout::Portrait;
    t["Landscape"] = QPageLayout::Landscape;

    // enum QPageLayout::Unit
    t["Millimeter"] = QPageLayout::Millimeter;
    t["Point"] = QPageLayout::Point;
    t["Inch"] = QPageLayout::Inch;
    t["Pica"] = QPageLayout::Pica;
    t["Didot"] = QPageLayout::Didot;
    t["Cicero"] = QPageLayout::Cicero;

    return 0;
}

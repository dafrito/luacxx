#include "QAbstractScrollArea.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "QFrame.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/QSize.hpp"
#include "QScrollBar.hpp"
#include "QWidget.hpp"

void lua::QAbstractScrollArea_metatable(lua_State* const state, const int pos)
{
    lua::QFrame_metatable(state, pos);

    lua::index mt(state, pos);
    mt["addScrollBarWidget"] = &QAbstractScrollArea::addScrollBarWidget;
    mt["cornerWidget"] = &QAbstractScrollArea::cornerWidget;
    mt["horizontalScrollBar"] = &QAbstractScrollArea::horizontalScrollBar;
    mt["horizontalScrollBarPolicy"] = &QAbstractScrollArea::horizontalScrollBarPolicy;
    mt["maximumViewportSize"] = &QAbstractScrollArea::maximumViewportSize;
    // QWidgetList     scrollBarWidgets(Qt::Alignment alignment)
    mt["setCornerWidget"] = &QAbstractScrollArea::setCornerWidget;
    mt["setHorizontalScrollBar"] = &QAbstractScrollArea::setHorizontalScrollBar;
    mt["setHorizontalScrollBarPolicy"] = &QAbstractScrollArea::setHorizontalScrollBarPolicy;
    mt["setSizeAdjustPolicy"] = &QAbstractScrollArea::setSizeAdjustPolicy;
    mt["setVerticalScrollBar"] = &QAbstractScrollArea::setVerticalScrollBar;
    mt["setVerticalScrollBarPolicy"] = &QAbstractScrollArea::setVerticalScrollBarPolicy;
    mt["setViewport"] = &QAbstractScrollArea::setViewport;
    mt["setupViewport"] = &QAbstractScrollArea::setupViewport;
    mt["sizeAdjustPolicy"] = &QAbstractScrollArea::sizeAdjustPolicy;
    mt["verticalScrollBar"] = &QAbstractScrollArea::verticalScrollBar;
    mt["verticalScrollBarPolicy"] = &QAbstractScrollArea::verticalScrollBarPolicy;
    mt["viewport"] = &QAbstractScrollArea::viewport;
}

int luaopen_Qt5Widgets_QAbstractScrollArea(lua_State* const state)
{
    lua::thread env(state);

    env["QAbstractScrollArea"] = lua::value::table;
    auto t = env["QAbstractScrollArea"];

    // enum QAbstractScrollArea::SizeAdjustPolicy
    t["AdjustIgnored"] = QAbstractScrollArea::AdjustIgnored;
    t["AdjustToContents"] = QAbstractScrollArea::AdjustToContents;
    t["AdjustToContentsOnFirstShow"] = QAbstractScrollArea::AdjustToContentsOnFirstShow;

    return 0;
}

#include "QGraphicsWidget.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Gui/QFont.hpp"
#include "QAction.hpp"
#include "../Qt5Gui/QPalette.hpp"
#include "../Qt5Core/QRectF.hpp"
#include "../Qt5Core/QSizeF.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QList.hpp"
#include "QStyle.hpp"
#include "../Qt5Gui/QKeySequence.hpp"
#include "../Qt5Gui/QPainter.hpp"
#include "QWidget.hpp"
// #include "QStyleOptionGraphicsItem.hpp"
// #include "QGraphicsLayout.hpp"
#include "QGraphicsObject.hpp"
#include "QGraphicsLayoutItem.hpp"
#include "QGraphicsLayout.hpp"

#include <QGraphicsWidget>

int QGraphicsWidget_getWindowFrameMargins(lua_State* const state)
{
    return 0;
}
int QGraphicsWidget_paintWindowFrame(lua_State* const state)
{
    return 0;
}
int QGraphicsWidget_resize(lua_State* const state)
{
    return 0;
}
int QGraphicsWidget_setAttribute(lua_State* const state)
{
    return 0;
}
int QGraphicsWidget_setGeometry(lua_State* const state)
{
    return 0;
}
int QGraphicsWidget_setShortcutAutoRepeat(lua_State* const state)
{
    return 0;
}
int QGraphicsWidget_setShortcutEnabled(lua_State* const state)
{
    return 0;
}

void lua::QGraphicsWidget_metatable(lua_State* const state, const int pos)
{
    lua::QGraphicsObject_metatable(state, pos);
    lua::QGraphicsLayoutItem_metatable(state, pos);

    lua::index mt(state, pos);
    mt["actions"] = &QGraphicsWidget::actions;
    mt["addAction"] = &QGraphicsWidget::addAction;
    mt["addActions"] = &QGraphicsWidget::addActions;
    mt["adjustSize"] = &QGraphicsWidget::adjustSize;
    mt["autoFillBackground"] = &QGraphicsWidget::autoFillBackground;
    mt["focusPolicy"] = &QGraphicsWidget::focusPolicy;
    mt["focusWidget"] = &QGraphicsWidget::focusWidget;
    mt["font"] = &QGraphicsWidget::font;
    mt["getWindowFrameMargins"] = QGraphicsWidget_getWindowFrameMargins;
    mt["grabShortcut"] = &QGraphicsWidget::grabShortcut;
    mt["insertAction"] = &QGraphicsWidget::insertAction;
    mt["insertActions"] = &QGraphicsWidget::insertActions;
    mt["isActiveWindow"] = &QGraphicsWidget::isActiveWindow;
    mt["layout"] = &QGraphicsWidget::layout;
    mt["layoutDirection"] = &QGraphicsWidget::layoutDirection;
    mt["paintWindowFrame"] = QGraphicsWidget_paintWindowFrame;
    mt["palette"] = &QGraphicsWidget::palette;
    mt["rect"] = &QGraphicsWidget::rect;
    mt["releaseShortcut"] = &QGraphicsWidget::releaseShortcut;
    mt["removeAction"] = &QGraphicsWidget::removeAction;
    mt["resize"] = QGraphicsWidget_resize;
    mt["setAttribute"] = QGraphicsWidget_setAttribute;
    mt["setAutoFillBackground"] = &QGraphicsWidget::setAutoFillBackground;
    mt["setContentsMargins"] = &QGraphicsWidget::setContentsMargins;
    mt["setFocusPolicy"] = &QGraphicsWidget::setFocusPolicy;
    mt["setFont"] = &QGraphicsWidget::setFont;
    mt["setGeometry"] = QGraphicsWidget_setGeometry;
    mt["setLayout"] = &QGraphicsWidget::setLayout;
    mt["setLayoutDirection"] = &QGraphicsWidget::setLayoutDirection;
    mt["setPalette"] = &QGraphicsWidget::setPalette;
    mt["setShortcutAutoRepeat"] = QGraphicsWidget_setShortcutAutoRepeat;
    mt["setShortcutEnabled"] = QGraphicsWidget_setShortcutEnabled;
    mt["setStyle"] = &QGraphicsWidget::setStyle;
    mt["setWindowFlags"] = &QGraphicsWidget::setWindowFlags;
    mt["setWindowFrameMargins"] = &QGraphicsWidget::setWindowFrameMargins;
    mt["setWindowTitle"] = &QGraphicsWidget::setWindowTitle;
    mt["size"] = &QGraphicsWidget::size;
    mt["style"] = &QGraphicsWidget::style;
    mt["testAttribute"] = &QGraphicsWidget::testAttribute;
    mt["unsetLayoutDirection"] = &QGraphicsWidget::unsetLayoutDirection;
    mt["unsetWindowFrameMargins"] = &QGraphicsWidget::unsetWindowFrameMargins;
    mt["windowFlags"] = &QGraphicsWidget::windowFlags;
    mt["windowFrameGeometry"] = &QGraphicsWidget::windowFrameGeometry;
    mt["windowFrameRect"] = &QGraphicsWidget::windowFrameRect;
    mt["windowTitle"] = &QGraphicsWidget::windowTitle;
    mt["windowType"] = &QGraphicsWidget::windowType;
}

int QGraphicsWidget_new(lua_State* const state)
{
    // QGraphicsWidget(QGraphicsItem * parent = 0, Qt::WindowFlags wFlags = 0)
    lua::make<QGraphicsWidget>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_Qt5Widgets_QGraphicsWidget(lua_State* const state)
{
    lua::thread env(state);

    env["QGraphicsWidget"] = lua::value::table;
    env["QGraphicsWidget"]["new"] = QGraphicsWidget_new;

    return 0;
}

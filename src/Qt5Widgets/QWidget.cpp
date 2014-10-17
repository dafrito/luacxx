#include "QWidget.hpp"

#include "QAction.hpp"
#include "../algorithm.hpp"
#include "../reference.hpp"
#include "../convert/callable.hpp"
#include "../Qt5Core/QMargins.hpp"
#include "../Qt5Core/QObject.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/QRect.hpp"
#include "../Qt5Gui/QRegion.hpp"
#include "../Qt5Gui/QWindow.hpp"
#include "../Qt5Gui/QPalette.hpp"
#include "../Qt5Gui/QCursor.hpp"
#include "../Qt5Gui/QFont.hpp"
#include "../Qt5Gui/QFontInfo.hpp"
#include "../Qt5Gui/QFontMetrics.hpp"
#include "../Qt5Gui/QKeySequence.hpp"
#include "../Qt5Gui/QIcon.hpp"
#include "../Qt5Gui/QIcon.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QLocale.hpp"
#include "../Qt5Core/QByteArray.hpp"
#include "QLayout.hpp"
#include "QGraphicsEffect.hpp"
#include "QStyle.hpp"
#include "../Qt5Core/QVariant.hpp"
#include "QSizePolicy.hpp"
#include "QGraphicsProxyWidget.hpp"

#include <cassert>
#include <functional>

// https://qt-project.org/doc/qt-5/qwidget.html

int QWidget_childAt(lua_State* const state)
{
    return 0;
}
int QWidget_getContentsMargins(lua_State* const state)
{
    return 0;
}
int QWidget_grab(lua_State* const state)
{
    return 0;
}
int QWidget_grabGesture(lua_State* const state)
{
    return 0;
}
int QWidget_grabMouse(lua_State* const state)
{
    return 0;
}
int QWidget_move(lua_State* const state)
{
    return 0;
}
int QWidget_render(lua_State* const state)
{
    return 0;
}
int QWidget_repaint(lua_State* const state)
{
    return 0;
}
int QWidget_resize(lua_State* const state)
{
    return 0;
}
int QWidget_scroll(lua_State* const state)
{
    return 0;
}
int QWidget_setAttribute(lua_State* const state)
{
    return 0;
}
int QWidget_setBaseSize(lua_State* const state)
{
    return 0;
}
int QWidget_setContentsMargins(lua_State* const state)
{
    return 0;
}
int QWidget_setFixedSize(lua_State* const state)
{
    return 0;
}
int QWidget_setFocus(lua_State* const state)
{
    return 0;
}
int QWidget_setGeometry(lua_State* const state)
{
    return 0;
}
int QWidget_setMask(lua_State* const state)
{
    return 0;
}
int QWidget_setMaximumSize(lua_State* const state)
{
    return 0;
}
int QWidget_setMinimumSize(lua_State* const state)
{
    return 0;
}
int QWidget_setParent(lua_State* const state)
{
    return 0;
}
int QWidget_setShortcutAutoRepeat(lua_State* const state)
{
    return 0;
}
int QWidget_setShortcutEnabled(lua_State* const state)
{
    return 0;
}
int QWidget_setSizeIncrement(lua_State* const state)
{
    return 0;
}
int QWidget_setSizePolicy(lua_State* const state)
{
    return 0;
}
int QWidget_update(lua_State* const state)
{
    return 0;
}

void lua::QWidget_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["acceptDrops"] = &QWidget::acceptDrops;
    mt["accessibleDescription"] = &QWidget::accessibleDescription;
    mt["accessibleName"] = &QWidget::accessibleName;
    mt["actions"] = &QWidget::actions;
    mt["activateWindow"] = &QWidget::activateWindow;
    mt["addAction"] = &QWidget::addAction;
    mt["addActions"] = &QWidget::addActions;
    mt["adjustSize"] = &QWidget::adjustSize;
    mt["autoFillBackground"] = &QWidget::autoFillBackground;
    mt["backgroundRole"] = &QWidget::backgroundRole;
    mt["backingStore"] = &QWidget::backingStore;
    mt["baseSize"] = &QWidget::baseSize;
    mt["childAt"] = QWidget_childAt;
    mt["childrenRect"] = &QWidget::childrenRect;
    mt["childrenRegion"] = &QWidget::childrenRegion;
    mt["clearFocus"] = &QWidget::clearFocus;
    mt["clearMask"] = &QWidget::clearMask;
    mt["contentsMargins"] = &QWidget::contentsMargins;
    mt["contentsRect"] = &QWidget::contentsRect;
    mt["contextMenuPolicy"] = &QWidget::contextMenuPolicy;
    mt["cursor"] = &QWidget::cursor;
    mt["effectiveWinId"] = &QWidget::effectiveWinId;
    mt["ensurePolished"] = &QWidget::ensurePolished;
    mt["focusPolicy"] = &QWidget::focusPolicy;
    mt["focusProxy"] = &QWidget::focusProxy;
    mt["focusWidget"] = &QWidget::focusWidget;
    mt["font"] = &QWidget::font;
    mt["fontInfo"] = &QWidget::fontInfo;
    mt["fontMetrics"] = &QWidget::fontMetrics;
    mt["foregroundRole"] = &QWidget::foregroundRole;
    mt["frameGeometry"] = &QWidget::frameGeometry;
    mt["frameSize"] = &QWidget::frameSize;
    mt["geometry"] = &QWidget::geometry;
    mt["childAt"] = QWidget_childAt;
    mt["getContentsMargins"] = QWidget_getContentsMargins;
    mt["grab"] = QWidget_grab;
    mt["grabGesture"] = QWidget_grabGesture;
    mt["grabKeyboard"] = &QWidget::grabKeyboard;
    mt["grabMouse"] = QWidget_grabMouse;
    mt["grabShortcut"] = &QWidget::grabShortcut;
    mt["graphicsEffect"] = &QWidget::graphicsEffect;
    mt["graphicsProxyWidget"] = &QWidget::graphicsProxyWidget;

    // Only in Embedded Linux
    // mt["hasEditFocus"] = &QWidget::hasEditFocus;

    mt["hasFocus"] = &QWidget::hasFocus;
    mt["hasHeightForWidth"] = &QWidget::hasHeightForWidth;
    mt["hasMouseTracking"] = &QWidget::hasMouseTracking;
    mt["height"] = &QWidget::height;
    mt["heightForWidth"] = &QWidget::heightForWidth;
    mt["inputMethodHints"] = &QWidget::inputMethodHints;
    mt["inputMethodQuery"] = &QWidget::inputMethodQuery;
    mt["insertAction"] = &QWidget::insertAction;
    mt["insertActions"] = &QWidget::insertActions;
    mt["isActiveWindow"] = &QWidget::isActiveWindow;
    mt["isAncestorOf"] = &QWidget::isAncestorOf;
    mt["isEnabled"] = &QWidget::isEnabled;
    mt["isEnabledTo"] = &QWidget::isEnabledTo;
    mt["isFullScreen"] = &QWidget::isFullScreen;
    mt["isHidden"] = &QWidget::isHidden;
    mt["isMaximized"] = &QWidget::isMaximized;
    mt["isMinimized"] = &QWidget::isMinimized;
    mt["isModal"] = &QWidget::isModal;
    mt["isVisible"] = &QWidget::isVisible;
    mt["isVisibleTo"] = &QWidget::isVisibleTo;
    mt["isWindow"] = &QWidget::isWindow;
    mt["isWindowModified"] = &QWidget::isWindowModified;
    mt["layout"] = &QWidget::layout;
    mt["layoutDirection"] = &QWidget::layoutDirection;
    mt["locale"] = &QWidget::locale;
    //mt["macCGHandle"] = &QWidget::macCGHandle;
    //mt["macQDHandle"] = &QWidget::macQDHandle;
    mt["mapFrom"] = &QWidget::mapFrom;
    mt["mapFromGlobal"] = &QWidget::mapFromGlobal;
    mt["mapFromParent"] = &QWidget::mapFromParent;
    mt["mapTo"] = &QWidget::mapTo;
    mt["mapToGlobal"] = &QWidget::mapToGlobal;
    mt["mapToParent"] = &QWidget::mapToParent;
    mt["mask"] = &QWidget::mask;
    mt["maximumHeight"] = &QWidget::maximumHeight;
    mt["maximumSize"] = &QWidget::maximumSize;
    mt["maximumWidth"] = &QWidget::maximumWidth;
    mt["minimumHeight"] = &QWidget::minimumHeight;
    mt["minimumSize"] = &QWidget::minimumSize;
    mt["minimumSizeHint"] = &QWidget::minimumSizeHint;
    mt["minimumWidth"] = &QWidget::minimumWidth;
    mt["move"] = QWidget_move;
    mt["nativeParentWidget"] = &QWidget::nativeParentWidget;
    mt["nextInFocusChain"] = &QWidget::nextInFocusChain;
    mt["normalGeometry"] = &QWidget::normalGeometry;
    mt["overrideWindowFlags"] = &QWidget::overrideWindowFlags;
    mt["palette"] = &QWidget::palette;
    mt["parentWidget"] = &QWidget::parentWidget;
    mt["pos"] = &QWidget::pos;
    mt["previousInFocusChain"] = &QWidget::previousInFocusChain;
    mt["rect"] = &QWidget::rect;
    mt["releaseKeyboard"] = &QWidget::releaseKeyboard;
    mt["releaseMouse"] = &QWidget::releaseMouse;
    mt["releaseShortcut"] = &QWidget::releaseShortcut;
    mt["removeAction"] = &QWidget::removeAction;
    mt["render"] = QWidget_render;
    mt["repaint"] = QWidget_repaint;
    mt["resize"] = QWidget_resize;
    mt["restoreGeometry"] = &QWidget::restoreGeometry;
    mt["saveGeometry"] = &QWidget::saveGeometry;
    mt["scroll"] = QWidget_scroll;
    mt["setAcceptDrops"] = &QWidget::setAcceptDrops;
    mt["setAccessibleDescription"] = &QWidget::setAccessibleDescription;
    mt["setAccessibleName"] = &QWidget::setAccessibleName;
    mt["setAttribute"] = QWidget_setAttribute;
    mt["setAutoFillBackground"] = &QWidget::setAutoFillBackground;
    mt["setBackgroundRole"] = &QWidget::setBackgroundRole;
    mt["setBaseSize"] = QWidget_setBaseSize;
    mt["setContentsMargins"] = QWidget_setContentsMargins;
    mt["setContextMenuPolicy"] = &QWidget::setContextMenuPolicy;
    mt["setCursor"] = &QWidget::setCursor;
    //mt["setEditFocus"] = &QWidget::setEditFocus;
    mt["setFixedHeight"] = &QWidget::setFixedHeight;
    mt["setFixedSize"] = QWidget_setFixedSize;
    mt["setFixedWidth"] = &QWidget::setFixedWidth;
    mt["setFocus"] = QWidget_setFocus;
    mt["setFocusPolicy"] = &QWidget::setFocusPolicy;
    mt["setFocusProxy"] = &QWidget::setFocusProxy;
    mt["setFont"] = &QWidget::setFont;
    mt["setForegroundRole"] = &QWidget::setForegroundRole;
    mt["setGeometry"] = QWidget_setGeometry;
    mt["setGraphicsEffect"] = &QWidget::setGraphicsEffect;
    mt["setInputMethodHints"] = &QWidget::setInputMethodHints;
    mt["setLayout"] = &QWidget::setLayout;
    mt["setLayoutDirection"] = &QWidget::setLayoutDirection;
    mt["setLocale"] = &QWidget::setLocale;
    mt["setMask"] = QWidget_setMask;
    mt["setMaximumHeight"] = &QWidget::setMaximumHeight;
    mt["setMaximumSize"] = QWidget_setMaximumSize;
    mt["setMaximumWidth"] = &QWidget::setMaximumWidth;
    mt["setMinimumHeight"] = &QWidget::setMinimumHeight;
    mt["setMinimumSize"] = QWidget_setMinimumSize;
    mt["setMinimumWidth"] = &QWidget::setMinimumWidth;
    mt["setMouseTracking"] = &QWidget::setMouseTracking;
    mt["setPalette"] = &QWidget::setPalette;
    mt["setParent"] = QWidget_setParent;
    mt["setShortcutAutoRepeat"] = QWidget_setShortcutAutoRepeat;
    mt["setShortcutEnabled"] = QWidget_setShortcutEnabled;
    mt["setSizeIncrement"] = QWidget_setSizeIncrement;
    mt["setSizePolicy"] = QWidget_setSizePolicy;
    mt["setStatusTip"] = &QWidget::setStatusTip;
    mt["setStyle"] = &QWidget::setStyle;
    mt["setToolTip"] = &QWidget::setToolTip;
    mt["setToolTipDuration"] = &QWidget::setToolTipDuration;
    mt["setUpdatesEnabled"] = &QWidget::setUpdatesEnabled;
    mt["setWhatsThis"] = &QWidget::setWhatsThis;
    mt["setWindowFilePath"] = &QWidget::setWindowFilePath;
    mt["setWindowFlags"] = &QWidget::setWindowFlags;
    mt["setWindowIcon"] = &QWidget::setWindowIcon;
    mt["setWindowIconText"] = &QWidget::setWindowIconText;
    mt["setWindowModality"] = &QWidget::setWindowModality;
    mt["setWindowOpacity"] = &QWidget::setWindowOpacity;
    mt["setWindowRole"] = &QWidget::setWindowRole;
    mt["setWindowState"] = &QWidget::setWindowState;
    //mt["setupUi"] = &QWidget::setupUi;
    mt["size"] = &QWidget::size;
    mt["sizeHint"] = &QWidget::sizeHint;
    mt["sizeIncrement"] = &QWidget::sizeIncrement;
    mt["sizePolicy"] = &QWidget::sizePolicy;
    mt["stackUnder"] = &QWidget::stackUnder;
    mt["statusTip"] = &QWidget::statusTip;
    mt["style"] = &QWidget::style;
    mt["styleSheet"] = &QWidget::styleSheet;
    mt["testAttribute"] = &QWidget::testAttribute;
    mt["toolTip"] = &QWidget::toolTip;
    mt["toolTipDuration"] = &QWidget::toolTipDuration;
    mt["underMouse"] = &QWidget::underMouse;
    mt["ungrabGesture"] = &QWidget::ungrabGesture;
    mt["unsetCursor"] = &QWidget::unsetCursor;
    mt["unsetLayoutDirection"] = &QWidget::unsetLayoutDirection;
    mt["unsetLocale"] = &QWidget::unsetLocale;
    mt["update"] = QWidget_update;
    mt["updateGeometry"] = &QWidget::updateGeometry;
    mt["updatesEnabled"] = &QWidget::updatesEnabled;
    mt["visibleRegion"] = &QWidget::visibleRegion;
    mt["whatsThis"] = &QWidget::whatsThis;
    mt["width"] = &QWidget::width;
    mt["winId"] = &QWidget::winId;
    mt["window"] = &QWidget::window;
    mt["windowFilePath"] = &QWidget::windowFilePath;
    mt["windowFlags"] = &QWidget::windowFlags;
    mt["windowHandle"] = &QWidget::windowHandle;
    mt["windowIcon"] = &QWidget::windowIcon;
    mt["windowIconText"] = &QWidget::windowIconText;
    mt["windowModality"] = &QWidget::windowModality;
    mt["windowOpacity"] = &QWidget::windowOpacity;
    mt["windowRole"] = &QWidget::windowRole;
    mt["windowState"] = &QWidget::windowState;
    mt["windowTitle"] = &QWidget::windowTitle;
    mt["windowType"] = &QWidget::windowType;
    mt["x"] = &QWidget::x;
    //mt["x11PictureHandle"] = &QWidget::x11PictureHandle;
    mt["y"] = &QWidget::y;
}

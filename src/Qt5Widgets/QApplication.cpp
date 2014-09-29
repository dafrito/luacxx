#include "QApplication.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include <QApplication>
#include "../Qt5Gui/QGuiApplication.hpp"
#include "../Qt5Gui/QFont.hpp"
#include "../Qt5Gui/QIcon.hpp"
#include "../Qt5Gui/QFontMetrics.hpp"
#include "../Qt5Core/QCoreApplication.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QString.hpp"
#include "../Qt5Core/Qt.hpp"
#include "../Qt5Core/QObject.hpp"
#include "QWidget.hpp"
#include "QStyle.hpp"

void lua::QApplication_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);
    lua::QGuiApplication_metatable(mt);

    mt["styleSheet"] = &QApplication::styleSheet;
}

int QApplication_alert(lua_State* const state)
{
    return 0;
}

int QApplication_font(lua_State* const state)
{
    return 0;
}

int QApplication_palette(lua_State* const state)
{
    return 0;
}
int QApplication_setEffectEnabled(lua_State* const state)
{
    return 0;
}
int QApplication_setFont(lua_State* const state)
{
    return 0;
}
int QApplication_setPalette(lua_State* const state)
{
    return 0;
}
int QApplication_setStyle(lua_State* const state)
{
    return 0;
}
int QApplication_topLevelAt(lua_State* const state)
{
    return 0;
}
int QApplication_widgetAt(lua_State* const state)
{
    return 0;
}

int luaopen_Qt5Widgets_QApplication(lua_State* const state)
{
    lua::thread env(state);

    env["QApplication"] = lua::value::table;
    env["QApplication"]["new"] = lua::QCoreApplication_new<QApplication>;
    auto t = env["QApplication"];

    t["activeModalWidget"] = &QApplication::activeModalWidget;
    t["activePopupWidget"] = &QApplication::activePopupWidget;
    t["activeWindow"] = &QApplication::activeWindow;
    t["alert"] = QApplication_alert;
    // QWidgetList     allWidgets()
    t["beep"] = &QApplication::beep;
    t["colorSpec"] = &QApplication::colorSpec;
    t["cursorFlashTime"] = &QApplication::cursorFlashTime;
    // QDesktopWidget *    desktop()
    t["doubleClickInterval"] = &QApplication::doubleClickInterval;
    t["exec"] = &QApplication::exec;
    t["focusWidget"] = &QApplication::focusWidget;
    t["font"] = QApplication_font;
    t["fontMetrics"] = &QApplication::fontMetrics;
    t["globalStrut"] = &QApplication::globalStrut;
    t["isEffectEnabled"] = &QApplication::isEffectEnabled;
    t["keyboardInputInterval"] = &QApplication::keyboardInputInterval;
    // Only in embeedded Linux and Windows CE
    //t["navigationMode"] = &QApplication::navigationMode;
    //t["setNavigationMode"] = &QApplication::setNavigationMode;
    t["palette"] = QApplication_palette;
    t["setActiveWindow"] = &QApplication::setActiveWindow;
    t["setColorSpec"] = &QApplication::setColorSpec;
    t["setCursorFlashTime"] = &QApplication::setCursorFlashTime;
    t["setDoubleClickInterval"] = &QApplication::setDoubleClickInterval;
    t["setEffectEnabled"] = QApplication_setEffectEnabled;
    t["setFont"] = QApplication_setFont;
    t["setGlobalStrut"] = &QApplication::setGlobalStrut;
    t["setKeyboardInputInterval"] = &QApplication::setKeyboardInputInterval;
    t["setPalette"] = QApplication_setPalette;
    t["setStartDragDistance"] = &QApplication::setStartDragDistance;
    t["setStartDragTime"] = &QApplication::setStartDragTime;
    t["setStyle"] = QApplication_setStyle;
    t["setWheelScrollLines"] = &QApplication::setWheelScrollLines;
    t["setWindowIcon"] = &QApplication::setWindowIcon;
    t["startDragDistance"] = &QApplication::startDragDistance;
    t["startDragTime"] = &QApplication::startDragTime;
    t["style"] = &QApplication::style;
    t["topLevelAt"] = QApplication_topLevelAt;
    // QWidgetList     topLevelWidgets()
    t["wheelScrollLines"] = &QApplication::wheelScrollLines;
    t["widgetAt"] = QApplication_widgetAt;
    t["windowIcon"] = &QApplication::windowIcon;

    return 0;
}

#include "QWindow.hpp"
#include "../Qt5Core/QObservable.hpp"
#include "QSurface.hpp"
#include "../Qt5Core/QObject.hpp"
#include "QScreen.hpp"
#include "../Qt5Core/QSize.hpp"
#include "../Qt5Core/QRect.hpp"
#include "QIcon.hpp"
#include "QSurfaceFormat.hpp"
#include "../Qt5Core/QPoint.hpp"
#include "../Qt5Core/Qt.hpp"
#include "QCursor.hpp"
#include "../Qt5Core/QFlags.hpp"
#include "../Qt5Core/QMargins.hpp"
#include "QRegion.hpp"

#include "../convert/callable.hpp"
#include "../convert/numeric.hpp"
#include "../thread.hpp"

#include <QScreen>

// http://qt-project.org/doc/qt-5/qwindow.html

// void     resize(const QSize & newSize)
// void     resize(int w, int h)
int QWindow_resize(lua_State* const state)
{
    auto self = lua::get<QWindow*>(state, 1);
    if (lua_gettop(state) == 2) {
        self->resize(lua::get<const QSize&>(state, 2));
    } else {
        self->resize(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        );
    }

    return 0;
}

int QWindow_setGeometry(lua_State* const state)
{
    auto self = lua::get<QWindow*>(state, 1);
    if (lua_gettop(state) == 2) {
        self->setGeometry(lua::get<const QRect&>(state, 2));
    } else {
        self->setGeometry(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3),
            lua::get<int>(state, 4),
            lua::get<int>(state, 5)
        );
    }
    return 0;
}

int QWindow_setPosition(lua_State* const state)
{
    auto self = lua::get<QWindow*>(state, 1);
    if (lua_gettop(state) == 2) {
        self->setPosition(lua::get<const QPoint&>(state, 2));
    } else {
        self->setPosition(
            lua::get<int>(state, 2),
            lua::get<int>(state, 3)
        );
    }
    return 0;
}


void lua::QWindow_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);
    lua::QSurface_metatable(state, pos);

    lua::index mt(state, pos);
    mt["baseSize"] = &QWindow::baseSize;
    mt["contentOrientation"] = &QWindow::contentOrientation;
    mt["create"] = &QWindow::create;
    mt["cursor"] = &QWindow::cursor;
    mt["destroy"] = &QWindow::destroy;
    mt["devicePixelRatio"] = &QWindow::devicePixelRatio;
    mt["filePath"] = &QWindow::filePath;
    mt["flags"] = &QWindow::flags;
    mt["focusObject"] = &QWindow::focusObject;
    mt["frameGeometry"] = &QWindow::frameGeometry;
    mt["frameMargins"] = &QWindow::frameMargins;
    mt["framePosition"] = &QWindow::framePosition;
    mt["geometry"] = &QWindow::geometry;
    mt["height"] = &QWindow::height;
    mt["icon"] = &QWindow::icon;
    mt["isActive"] = &QWindow::isActive;
    mt["isAncestorOf"] = &QWindow::isAncestorOf;
    mt["isExposed"] = &QWindow::isExposed;
    mt["isModal"] = &QWindow::isModal;
    mt["isTopLevel"] = &QWindow::isTopLevel;
    mt["isVisible"] = &QWindow::isVisible;
    mt["mapFromGlobal"] = &QWindow::mapFromGlobal;
    mt["mapToGlobal"] = &QWindow::mapToGlobal;
    mt["mask"] = &QWindow::mask;
    mt["maximumHeight"] = &QWindow::maximumHeight;
    mt["maximumSize"] = &QWindow::maximumSize;
    mt["maximumWidth"] = &QWindow::maximumWidth;
    mt["minimumHeight"] = &QWindow::minimumHeight;
    mt["minimumSize"] = &QWindow::minimumSize;
    mt["minimumWidth"] = &QWindow::minimumWidth;
    mt["modality"] = &QWindow::modality;
    mt["opacity"] = &QWindow::opacity;
    mt["parent"] = &QWindow::parent;
    mt["position"] = &QWindow::position;
    mt["reportContentOrientationChange"] = &QWindow::reportContentOrientationChange;
    mt["requestedFormat"] = &QWindow::requestedFormat;
    mt["resize"] = QWindow_resize;
    mt["screen"] = &QWindow::screen;
    mt["setBaseSize"] = &QWindow::setBaseSize;
    mt["setCursor"] = &QWindow::setCursor;
    mt["setFilePath"] = &QWindow::setFilePath;
    mt["setFlags"] = &QWindow::setFlags;
    mt["setFormat"] = &QWindow::setFormat;
    mt["setFramePosition"] = &QWindow::setFramePosition;
    mt["setGeometry"] = QWindow_setGeometry;
    mt["setIcon"] = &QWindow::setIcon;
    mt["setKeyboardGrabEnabled"] = &QWindow::setKeyboardGrabEnabled;
    mt["setMask"] = &QWindow::setMask;
    mt["setMaximumSize"] = &QWindow::setMaximumSize;
    mt["setMinimumSize"] = &QWindow::setMinimumSize;
    mt["setModality"] = &QWindow::setModality;
    mt["setMouseGrabEnabled"] = &QWindow::setMouseGrabEnabled;
    mt["setOpacity"] = &QWindow::setOpacity;
    mt["setParent"] = &QWindow::setParent;
    mt["setPosition"] = QWindow_setPosition;
    mt["setScreen"] = &QWindow::setScreen;
    mt["setSizeIncrement"] = &QWindow::setSizeIncrement;
    mt["setSurfaceType"] = &QWindow::setSurfaceType;
    mt["setTransientParent"] = &QWindow::setTransientParent;
    mt["setVisibility"] = &QWindow::setVisibility;
    mt["setWindowState"] = &QWindow::setWindowState;
    mt["sizeIncrement"] = &QWindow::sizeIncrement;
    mt["title"] = &QWindow::title;
    mt["transientParent"] = &QWindow::transientParent;
    mt["type"] = &QWindow::type;
    mt["unsetCursor"] = &QWindow::unsetCursor;
    mt["visibility"] = &QWindow::visibility;
    mt["width"] = &QWindow::width;
    mt["windowState"] = &QWindow::windowState;
    mt["x"] = &QWindow::x;
    mt["y"] = &QWindow::y;
}

int QWindow_new(lua_State* const state)
{
    typedef lua::QObservable<QWindow> Window;

    // Did we get an extra argument?
    if (lua_gettop(state) > 1 && lua_type(state, 1) != LUA_TNIL) {
        // We did, so find out what it is
        auto parent = lua::get<QObject*>(state, 1);
        if (!parent) {
            // Not recognized, so bail.
            throw lua::error("A QWindow or QScreen must be provided for QWindow.new(parent)");
        }

        if (parent->inherits("QWindow")) {
            lua::make<Window>(state, state, lua::get<QWindow*>(state, 1));
        } else {
            lua::make<Window>(state, state, lua::get<QScreen*>(state, 1));
        }
        return 1;

    }

    // Create a QWindow within Lua
    lua::make<Window>(state, state);
    return 1;
}

int luaopen_Qt5Gui_QWindow(lua_State* const state)
{
    lua::thread env(state);
    lua_settop(state, 0);

    env["QWindow"] = lua::value::table;
    env["QWindow"]["new"] = QWindow_new;
    auto t = env["QWindow"];

    env["fromWinId"] = &QWindow::fromWinId;

    // enum QWindow::AncestorMode
    t["ExcludeTransients"] = QWindow::ExcludeTransients;
    t["IncludeTransients"] = QWindow::IncludeTransients;

    // enum QWindow::Visibility
    t["Windowed"] = QWindow::Windowed;
    t["Minimized"] = QWindow::Minimized;
    t["Maximized"] = QWindow::Maximized;
    t["FullScreen"] = QWindow::FullScreen;
    t["AutomaticVisibility"] = QWindow::AutomaticVisibility;
    t["Hidden"] = QWindow::Hidden;

    return 0;
}

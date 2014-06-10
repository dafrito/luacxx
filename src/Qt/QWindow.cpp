#include "QWindow.hpp"
#include "QObject.hpp"
#include "QObservable.hpp"

#include "../type/function.hpp"
#include "../thread.hpp"

#include <QScreen>

void lua::QWindow_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);

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
    //mt["resize"] = &QWindow::resize;
    //mt["resize"] = &QWindow::resize;
    mt["screen"] = &QWindow::screen;
    mt["setBaseSize"] = &QWindow::setBaseSize;
    mt["setCursor"] = &QWindow::setCursor;
    mt["setFilePath"] = &QWindow::setFilePath;
    mt["setFlags"] = &QWindow::setFlags;
    mt["setFormat"] = &QWindow::setFormat;
    mt["setFramePosition"] = &QWindow::setFramePosition;
    //mt["setGeometry"] = &QWindow::setGeometry;
    //mt["setGeometry"] = &QWindow::setGeometry;
    mt["setIcon"] = &QWindow::setIcon;
    mt["setKeyboardGrabEnabled"] = &QWindow::setKeyboardGrabEnabled;
    mt["setMask"] = &QWindow::setMask;
    mt["setMaximumSize"] = &QWindow::setMaximumSize;
    mt["setMinimumSize"] = &QWindow::setMinimumSize;
    mt["setModality"] = &QWindow::setModality;
    mt["setMouseGrabEnabled"] = &QWindow::setMouseGrabEnabled;
    mt["setOpacity"] = &QWindow::setOpacity;
    mt["setParent"] = &QWindow::setParent;
    //mt["setPosition"] = &QWindow::setPosition;
    //mt["setPosition"] = &QWindow::setPosition;
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
    if (lua_gettop(state) > 1 && lua_type(state, 2) != LUA_TNIL) {
        // We did, so find out what it is
        auto parent = lua::get<QObject*>(state, 2);
        if (!parent) {
            // Not recognized, so bail.
            throw lua::error("A QWindow or QScreen must be provided for QWindow:new(parent)");
        }

        if (parent->inherits("QWindow")) {
            lua::make<Window>(state, state, lua::get<QWindow*>(state, 2));
        } else {
            lua::make<Window>(state, state, lua::get<QScreen*>(state, 2));
        }
        lua_replace(state, 1);
        lua_settop(state, 1);
        return 1;

    }

    // Create a QWindow within Lua
    lua_settop(state, 0);
    lua::make<Window>(state, state);
    return 1;
}

int luaopen_luacxx_QWindow(lua_State* const state)
{
    lua::thread env(state);
    lua_settop(state, 0);

    env["QWindow"] = lua::value::table;
    env["QWindow"]["new"] = QWindow_new;

    return 0;
}

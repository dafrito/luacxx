#include "QWindow.hpp"
#include "QObject.hpp"
#include "QObservable.hpp"

#include "../type/function.hpp"
#include "../thread.hpp"

void lua::QWindow_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);
    mt["create"] = &QWindow::create;
    mt["destroy"] = &QWindow::destroy;
    mt["isExposed"] = &QWindow::isExposed;
    mt["isModal"] = &QWindow::isModal;
    mt["isTopLevel"] = &QWindow::isTopLevel;
    mt["isVisible"] = &QWindow::isVisible;
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

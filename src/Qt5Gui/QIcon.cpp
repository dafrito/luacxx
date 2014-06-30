#include "QIcon.hpp"
#include "../luacxx/convert/callable.hpp"
#include "../luacxx/thread.hpp"

#include "../Qt5Core/QSize.hpp"
#include "QWindow.hpp"
#include "../Qt5Core/QList.hpp"
#include "QPixmap.hpp"
#include "QPainter.hpp"
#include "QIcon.hpp"
#include "../Qt5Core/QStringList.hpp"

// http://qt-project.org/doc/qt-5/qicon.html

int QIcon_actualSize(lua_State* const state)
{
    return 0;
}

int QIcon_addFile(lua_State* const state)
{
    return 0;
}

int QIcon_addPixmap(lua_State* const state)
{
    return 0;
}

int QIcon_availableSizes(lua_State* const state)
{
    return 0;
}

int QIcon_paint(lua_State* const state)
{
    return 0;
}

int QIcon_pixmap(lua_State* const state)
{
    return 0;
}

void lua::QIcon_metatable(const lua::index& mt)
{
    mt["actualSize"] = QIcon_actualSize;
    mt["addFile"] = QIcon_addFile;
    mt["addPixmap"] = QIcon_addPixmap;
    mt["availableSizes"] = QIcon_availableSizes;
    mt["cacheKey"] = &QIcon::cacheKey;
    mt["isNull"] = &QIcon::isNull;
    mt["name"] = &QIcon::name;
    mt["paint"] = QIcon_paint;
    mt["pixmap"] = QIcon_pixmap;
    mt["swap"] = &QIcon::swap;
}

int QIcon_new(lua_State* const state)
{
    if (lua_gettop(state) < 1) {
        // QIcon()
        lua::make<QIcon>(state);
        return 1;
    }

    if (lua_type(state, 2) == LUA_TSTRING) {
        // QIcon(const QString & fileName)
        lua::make<QIcon>(state, lua::get<const char*>(state, 2));
        return 1;
    }

    if (lua::class_name(state, 2) == lua::Metatable<QIconEngine>::name) {
        // QIcon(QIconEngine * engine)
        lua::make<QIcon>(state, lua::get<QIconEngine*>(state, 2));
        return 1;
    }

    if (lua::class_name(state, 2) == lua::Metatable<QIcon>::name) {
        // QIcon(const QIcon & other)
        lua::make<QIcon>(state, lua::get<const QIcon&>(state, 2));
        return 1;
    }

    // QIcon(const QPixmap & pixmap)
    lua::make<QIcon>(state, lua::get<const QPixmap&>(state, 2));
    return 1;
}

int luaopen_Qt5Gui_QIcon(lua_State* const state)
{
    lua::thread env(state);

    env["QIcon"] = lua::value::table;
    auto t = env["QIcon"];

    t["new"] = QIcon_new;
    t["fromTheme"] = &QIcon::fromTheme;
    t["hasThemeIcon"] = &QIcon::hasThemeIcon;
    t["setThemeName"] = &QIcon::setThemeName;
    t["setThemeSearchPaths"] = &QIcon::setThemeSearchPaths;
    t["themeName"] = &QIcon::themeName;
    t["themeSearchPaths"] = &QIcon::themeSearchPaths;

    // enum QIcon::Mode
    t["Normal"] = QIcon::Normal;
    t["Disabled"] = QIcon::Disabled;
    t["Active"] = QIcon::Active;
    t["Selected"] = QIcon::Selected;

    // enum QIcon::State
    t["Off"] = QIcon::Off;
    t["On"] = QIcon::On;

    return 0;
}

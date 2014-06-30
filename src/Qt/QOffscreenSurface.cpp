#include "QOffscreenSurface.hpp"
#include "../luacxx/type/function.hpp"
#include "../luacxx/thread.hpp"
#include "QSurface.hpp"

#include <QOffscreenSurface>

void lua::QOffscreenSurface_metatable(const lua::index& mt)
{
    lua::QSurface_metatable(mt);

    mt["create"] = &QOffscreenSurface::create;
    mt["destroy"] = &QOffscreenSurface::destroy;
    mt["isValid"] = &QOffscreenSurface::isValid;
    mt["requestedFormat"] = &QOffscreenSurface::requestedFormat;
    mt["screen"] = &QOffscreenSurface::screen;
    mt["setFormat"] = &QOffscreenSurface::setFormat;
    mt["setScreen"] = &QOffscreenSurface::setScreen;
}

int QOffscreenSurface_new(lua_State* const state)
{
    lua::make<QOffscreenSurface>(state);
    // TODO Set up object-specific methods

    return 1;
}

int luaopen_luacxx_QOffscreenSurface(lua_State* const state)
{
    lua::thread env(state);

    env["QOffscreenSurface"] = lua::value::table;
    env["QOffscreenSurface"]["new"] = QOffscreenSurface_new;

    return 0;
}

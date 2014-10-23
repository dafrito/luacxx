#include "QSurface.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"

#include "../Qt5Core/QObject.hpp"
#include "QSurfaceFormat.hpp"
#include "../Qt5Core/QSize.hpp"

void lua::QSurface_metatable(lua_State* const state, const int pos)
{
    lua::QObject_metatable(state, pos);

    lua::index mt(state, pos);
    mt["format"] = &QSurface::format;
    mt["size"] = &QSurface::size;
    mt["surfaceClass"] = &QSurface::surfaceClass;
    mt["surfaceType"] = &QSurface::surfaceType;

    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    mt["supportsOpenGL"] = &QSurface::supportsOpenGL;
    #endif
}

int luaopen_Qt5Gui_QTcpSocket(lua_State* const state)
{
    lua::thread env(state);

    env["QSurface"] = lua::value::table;
    auto t = env["QSurface"];

    // enum QSurface::SurfaceClass
    t["Window"] = QSurface::Window;
    t["Offscreen"] = QSurface::Offscreen;

    // enum QSurface::SurfaceType
    t["RasterSurface"] = QSurface::RasterSurface;
    t["OpenGLSurface"] = QSurface::OpenGLSurface;

    return 0;
}


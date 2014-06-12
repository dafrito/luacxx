#include "QSurface.hpp"
#include "QObject.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QSurface>

void lua::QSurface_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);
    mt["format"] = &QSurface::format;
    mt["size"] = &QSurface::size;
    mt["surfaceClass"] = &QSurface::surfaceClass;
    mt["surfaceType"] = &QSurface::surfaceType;

    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    mt["supportsOpenGL"] = &QSurface::supportsOpenGL;
    #endif
}

int luaopen_luacxx_QTcpSocket(lua::state* const state)
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


#include "QOpenGLContext.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"
#include "QScreen.hpp"
#include "QOpenGLContextGroup.hpp"
#include "QOpenGLFunctions.hpp"
#include "QList.hpp"
#include "QSet.hpp"
#include "QObject.hpp"
#include "QSurface.hpp"

#include <QOpenGLContext>

int QOpenGLContext_versionFunctions(lua_State* const state)
{
    return 0;
}

void lua::QOpenGLContext_metatable(const lua::index& mt)
{
    lua::QObject_metatable(mt);

    mt["create"] = &QOpenGLContext::create;
    mt["defaultFramebufferObject"] = &QOpenGLContext::defaultFramebufferObject;
    mt["doneCurrent"] = &QOpenGLContext::doneCurrent;
    //mt["extensions"] = &QOpenGLContext::extensions;
    mt["format"] = &QOpenGLContext::format;
    mt["functions"] = &QOpenGLContext::functions;
    mt["getProcAddress"] = &QOpenGLContext::getProcAddress;
    mt["hasExtension"] = &QOpenGLContext::hasExtension;
    mt["isValid"] = &QOpenGLContext::isValid;
    mt["makeCurrent"] = &QOpenGLContext::makeCurrent;
    mt["screen"] = &QOpenGLContext::screen;
    mt["setFormat"] = &QOpenGLContext::setFormat;
    mt["setScreen"] = &QOpenGLContext::setScreen;
    mt["setShareContext"] = &QOpenGLContext::setShareContext;
    mt["shareContext"] = &QOpenGLContext::shareContext;
    mt["shareGroup"] = &QOpenGLContext::shareGroup;
    mt["surface"] = &QOpenGLContext::surface;
    mt["swapBuffers"] = &QOpenGLContext::swapBuffers;
    mt["versionFunctions"] = QOpenGLContext_versionFunctions;

    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    mt["isOpenGLES"] = &QOpenGLContext::isOpenGLES;
    #endif
}

int QOpenGLContext_new(lua::state* const state)
{
    lua::make<QOpenGLContext>(state);
    return 1;
}

int luaopen_luacxx_QOpenGLContext(lua::state* const state)
{
    lua::thread env(state);

    env["QOpenGLContext"] = lua::value::table;
    env["QOpenGLContext"]["new"] = QOpenGLContext_new;

    return 0;
}

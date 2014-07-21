#include "QOpenGLContext.hpp"
#include "../convert/callable.hpp"
#include "../thread.hpp"
#include "QScreen.hpp"
#include "QOpenGLContextGroup.hpp"
#include "QOpenGLFunctions.hpp"
#include "../Qt5Core/QList.hpp"
#include "../Qt5Core/QSet.hpp"
#include "../Qt5Core/QObject.hpp"
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

int QOpenGLContext_new(lua_State* const state)
{
    lua::make<QOpenGLContext>(state);
    return 1;
}

int luaopen_Qt5Gui_QOpenGLContext(lua_State* const state)
{
    lua::thread env(state);

    env["QOpenGLContext"] = lua::value::table;
    env["QOpenGLContext"]["new"] = QOpenGLContext_new;

    return 0;
}

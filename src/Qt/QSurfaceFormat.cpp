#include "QSurfaceFormat.hpp"
#include "../type/function.hpp"
#include "../thread.hpp"

#include <QSurfaceFormat>

void lua::QSurfaceFormat_metatable(const lua::index& mt)
{
    mt["alphaBufferSize"] = &QSurfaceFormat::alphaBufferSize;
    mt["blueBufferSize"] = &QSurfaceFormat::blueBufferSize;
    mt["depthBufferSize"] = &QSurfaceFormat::depthBufferSize;
    mt["greenBufferSize"] = &QSurfaceFormat::greenBufferSize;
    mt["hasAlpha"] = &QSurfaceFormat::hasAlpha;
    mt["majorVersion"] = &QSurfaceFormat::majorVersion;
    mt["minorVersion"] = &QSurfaceFormat::minorVersion;
    mt["profile"] = &QSurfaceFormat::profile;
    mt["redBufferSize"] = &QSurfaceFormat::redBufferSize;
    mt["renderableType"] = &QSurfaceFormat::renderableType;
    mt["samples"] = &QSurfaceFormat::samples;
    mt["setAlphaBufferSize"] = &QSurfaceFormat::setAlphaBufferSize;
    mt["setBlueBufferSize"] = &QSurfaceFormat::setBlueBufferSize;
    mt["setDepthBufferSize"] = &QSurfaceFormat::setDepthBufferSize;
    mt["setGreenBufferSize"] = &QSurfaceFormat::setGreenBufferSize;
    mt["setMajorVersion"] = &QSurfaceFormat::setMajorVersion;
    mt["setMinorVersion"] = &QSurfaceFormat::setMinorVersion;
    mt["setOption"] = &QSurfaceFormat::setOption;
    mt["setProfile"] = &QSurfaceFormat::setProfile;
    mt["setRedBufferSize"] = &QSurfaceFormat::setRedBufferSize;
    mt["setRenderableType"] = &QSurfaceFormat::setRenderableType;
    mt["setSamples"] = &QSurfaceFormat::setSamples;
    mt["setStencilBufferSize"] = &QSurfaceFormat::setStencilBufferSize;
    mt["setStereo"] = &QSurfaceFormat::setStereo;
    mt["setSwapBehavior"] = &QSurfaceFormat::setSwapBehavior;
    mt["setVersion"] = &QSurfaceFormat::setVersion;
    mt["stencilBufferSize"] = &QSurfaceFormat::stencilBufferSize;
    mt["stereo"] = &QSurfaceFormat::stereo;
    mt["swapBehavior"] = &QSurfaceFormat::swapBehavior;
    mt["testOption"] = &QSurfaceFormat::testOption;
    mt["version"] = &QSurfaceFormat::version;

    #if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
    mt["options"] = &QSurfaceFormat::options;
    mt["setOptions"] = &QSurfaceFormat::setOptions;

    mt["swapInterval"] = &QSurfaceFormat::swapInterval;
    mt["setSwapInterval"] = &QSurfaceFormat::setSwapInterval;
    #endif
}

/*

QSurfaceFormat()
QSurfaceFormat(FormatOptions options)
QSurfaceFormat(const QSurfaceFormat & other)

*/
int QSurfaceFormat_new(lua_State* const state)
{
    if (lua_gettop(state) < 2) {
        lua::make<QSurfaceFormat>(state);
        return 1;
    }
    if (lua::class_name(state, 2) == lua::Metatable<QSurfaceFormat>::name) {
        lua::make<QSurfaceFormat>(state, lua::get<const QSurfaceFormat&>(state, 2));
        return 1;
    }

    lua::make<QSurfaceFormat>(state,
        lua::get<QSurfaceFormat::FormatOptions>(state, 2)
    );
    return 1;
}

int luaopen_luacxx_QSurfaceFormat(lua_State* const state)
{
    lua::thread env(state);

    env["QSurfaceFormat"] = lua::value::table;
    env["QSurfaceFormat"]["new"] = QSurfaceFormat_new;
    auto t = env["QSurfaceFormat"];

    // enum QSurfaceFormat::FormatOption
    // flags QSurfaceFormat::FormatOptions
    t["StereoBuffers"] = QSurfaceFormat::StereoBuffers;
    t["DebugContext"] = QSurfaceFormat::DebugContext;
    t["DeprecatedFunctions"] = QSurfaceFormat::DeprecatedFunctions;

    // enum QSurfaceFormat::OpenGLContextProfile
    t["NoProfile"] = QSurfaceFormat::NoProfile;
    t["CoreProfile"] = QSurfaceFormat::CoreProfile;
    t["CompatibilityProfile"] = QSurfaceFormat::CompatibilityProfile;

    // enum QSurfaceFormat::RenderableType
    t["DefaultRenderableType"] = QSurfaceFormat::DefaultRenderableType;
    t["OpenGL"] = QSurfaceFormat::OpenGL;
    t["OpenGLES"] = QSurfaceFormat::OpenGLES;
    t["OpenVG"] = QSurfaceFormat::OpenVG;

    // enum QSurfaceFormat::SwapBehavior
    t["DefaultSwapBehavior"] = QSurfaceFormat::DefaultSwapBehavior;
    t["SingleBuffer"] = QSurfaceFormat::SingleBuffer;
    t["DoubleBuffer"] = QSurfaceFormat::DoubleBuffer;
    t["TripleBuffer"] = QSurfaceFormat::TripleBuffer;

    return 0;
}

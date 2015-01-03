#include "egl.hpp"

#include "thread.hpp"

#include "convert/vector.hpp"

int _eglInitialize(lua_State* const state)
{
    EGLint major, minor;

    lua::push(state, eglInitialize(
        lua::get<EGLDisplay>(state, 1),
        &major,
        &minor
    ));

    lua::push(state, major, minor);

    return 3;
}

int _eglGetConfigs(lua_State* const state)
{
    if (lua_gettop(state) == 2) {
        // local err, configs, num_config = eglGetConfigs(display, config_size)
        auto config_size = lua::get<EGLint>(state, 2);
        int num_config;

        std::vector<EGLConfig> configs;
        configs.reserve(config_size);

        lua::push(state, eglGetConfigs(
            lua::get<EGLDisplay>(state, 1),
            &configs[0],
            config_size,
            &num_config
        ));
        lua::push(state, configs);
        lua::push(state, num_config);
        return 3;
    }

    lua::push(state, eglGetConfigs(
        lua::get<EGLDisplay>(state, 1),
        lua::get<EGLConfig*>(state, 2),
        lua::get<EGLint>(state, 3),
        lua::get<EGLint*>(state, 4)
    ));

    return 1;
}

int _eglChooseConfig(lua_State* const state)
{
    std::vector<EGLint> attrib_list;
    lua::store(attrib_list, state, 2);

    auto config_size = lua::get<EGLint>(state, 2);
    int num_config;

    std::vector<EGLConfig> configs;
    configs.reserve(config_size);

    lua::push(state, eglChooseConfig(
        lua::get<EGLDisplay>(state, 1),
        &attrib_list[0],
        &configs[0],
        config_size,
        &num_config
    ));

    configs.resize(num_config);
    lua::push(state, configs);
    lua::push(state, num_config);

    return 3;
}

int _eglGetConfigAttrib(lua_State* const state)
{
    EGLint value;
    lua::push(state, eglGetConfigAttrib(
        lua::get<EGLDisplay>(state, 1),
        lua::get<EGLConfig&>(state, 2),
        lua::get<EGLint>(state, 3),
        &value
    ));
    lua::push(state, value);

    return 2;
}

int _eglCreateWindowSurface(lua_State* const state)
{
    std::vector<EGLint> attrib_list;
    if (lua_gettop(state) > 3) {
        lua::store(attrib_list, state, 4);
    } else {
        attrib_list.push_back(EGL_NONE);
    }

    lua::push(state, eglCreateWindowSurface(
        lua::get<EGLDisplay>(state, 1),
        lua::get<EGLConfig>(state, 2),
        lua::get<EGLNativeWindowType>(state, 3),
        &attrib_list[0]
    ));
    return 1;
}

int _eglCreatePbufferSurface(lua_State* const state)
{
    std::vector<EGLint> attrib_list;
    if (lua_gettop(state) > 3) {
        lua::store(attrib_list, state, 4);
    } else {
        attrib_list.push_back(EGL_NONE);
    }

    lua::push(state, eglCreatePbufferSurface(
        lua::get<EGLDisplay>(state, 1),
        lua::get<EGLConfig&>(state, 2),
        &attrib_list[0]
    ));
    return 1;
}

int _eglCreatePbufferFromClientBuffer(lua_State* const state)
{
    std::vector<EGLint> attrib_list;
    if (lua_gettop(state) > 4) {
        lua::store(attrib_list, state, 5);
    } else {
        attrib_list.push_back(EGL_NONE);
    }

    lua::push(state, eglCreatePbufferFromClientBuffer(
        lua::get<EGLDisplay>(state, 1),
        lua::get<EGLenum>(state, 2),
        lua::get<EGLClientBuffer>(state, 3),
        lua::get<EGLConfig>(state, 4),
        &attrib_list[1]
    ));
    return 1;
}

int _eglCreatePixmapSurface(lua_State* const state)
{
    std::vector<EGLint> attrib_list;
    if (lua_gettop(state) > 3) {
        lua::store(attrib_list, state, 4);
    } else {
        attrib_list.push_back(EGL_NONE);
    }

    lua::push(state, eglCreatePixmapSurface(
        lua::get<EGLDisplay>(state, 1),
        lua::get<EGLConfig&>(state, 2),
        lua::get<EGLNativePixmapType>(state, 3),
        &attrib_list[0]
    ));
    return 1;
}

int _eglQuerySurface(lua_State* const state)
{
    EGLint value;
    lua::push(state, eglQuerySurface(
        lua::get<EGLDisplay>(state, 1),
        lua::get<EGLSurface>(state, 2),
        lua::get<EGLint>(state, 3),
        &value
    ));
    lua::push(state, value);
    return 0;
}

int _eglCreateContext(lua_State* const state)
{
    std::vector<EGLint> attrib_list;
    if (lua_gettop(state) < 4 || lua_type(state, 4) == LUA_TNIL) {
        attrib_list.push_back(EGL_NONE);
    } else {
        lua::store(attrib_list, state, 4);
    }

    lua::push(state, eglCreateContext(
        lua::get<EGLDisplay>(state, 1),
        lua::get<EGLConfig>(state, 2),
        lua::get<EGLContext>(state, 3),
        &attrib_list[0]
    ));
    return 0;
}

int _eglQueryContext(lua_State* const state)
{
    EGLint value;
    lua::push(state, eglQueryContext(
        lua::get<EGLDisplay>(state, 1),
        lua::get<EGLContext>(state, 2),
        lua::get<EGLint>(state, 3),
        &value)
    );
    lua::push(state, value);
    return 0;
}

int luaopen_egl(lua_State* const state)
{
    lua::thread env(state);

    /* EGL Functions */

    env["eglGetError"] = eglGetError;

    env["eglGetDisplay"] = eglGetDisplay;
    env["eglInitialize"] = _eglInitialize;
    env["eglTerminate"] = eglTerminate;

    env["eglQueryString"] = eglQueryString;

    env["eglGetConfigs"] = _eglGetConfigs;
    env["eglChooseConfig"] = _eglChooseConfig;
    env["eglGetConfigAttrib"] = _eglGetConfigAttrib;

    env["eglCreateWindowSurface"] = _eglCreateWindowSurface;
    env["eglCreatePbufferSurface"] = _eglCreatePbufferSurface;
    env["eglCreatePixmapSurface"] = _eglCreatePixmapSurface;
    env["eglDestroySurface"] = eglDestroySurface;
    env["eglQuerySurface"] = _eglQuerySurface;

    env["eglBindAPI"] = eglBindAPI;
    env["eglQueryAPI"] = eglQueryAPI;

    env["eglWaitClient"] = eglWaitClient;

    env["eglReleaseThread"] = eglReleaseThread;

    env["eglCreatePbufferFromClientBuffer"] = _eglCreatePbufferFromClientBuffer;

    env["eglSurfaceAttrib"] = eglSurfaceAttrib;
    env["eglBindTexImage"] = eglBindTexImage;
    env["eglReleaseTexImage"] = eglReleaseTexImage;

    env["eglSwapInterval"] = eglSwapInterval;

    env["eglCreateContext"] = _eglCreateContext;
    env["eglDestroyContext"] = eglDestroyContext;
    env["eglMakeCurrent"] = eglMakeCurrent;

    env["eglGetCurrentContext"] = eglGetCurrentContext;
    env["eglGetCurrentSurface"] = eglGetCurrentSurface;
    env["eglGetCurrentDisplay"] = eglGetCurrentDisplay;
    env["eglQueryContext"] = _eglQueryContext;

    env["eglWaitGL"] = eglWaitGL;
    env["eglWaitNative"] = eglWaitNative;
    env["eglSwapBuffers"] = eglSwapBuffers;
    env["eglCopyBuffers"] = eglCopyBuffers;

    /* EGL Versioning */
    env["EGL_VERSION_1_0"] = EGL_VERSION_1_0;
    env["EGL_VERSION_1_1"] = EGL_VERSION_1_1;
    env["EGL_VERSION_1_2"] = EGL_VERSION_1_2;
    env["EGL_VERSION_1_3"] = EGL_VERSION_1_3;
    env["EGL_VERSION_1_4"] = EGL_VERSION_1_4;

    /* EGL Enumerants. Bitmasks and other exceptional cases aside, most
     * enums are assigned unique values starting at 0x3000.
     */

    /* EGL aliases */
    env["EGL_FALSE"] = EGL_FALSE;
    env["EGL_TRUE"] = EGL_TRUE;

    /* Out-of-band handle values */
    env["EGL_DEFAULT_DISPLAY"] = EGL_DEFAULT_DISPLAY;
    env["EGL_NO_CONTEXT"] = EGL_NO_CONTEXT;
    env["EGL_NO_DISPLAY"] = EGL_NO_DISPLAY;
    env["EGL_NO_SURFACE"] = EGL_NO_SURFACE;

    /* Out-of-band attribute value */
    env["EGL_DONT_CARE"] = EGL_DONT_CARE;

    /* Errors / GetError return values */
    env["EGL_SUCCESS"] = EGL_SUCCESS;
    env["EGL_NOT_INITIALIZED"] = EGL_NOT_INITIALIZED;
    env["EGL_BAD_ACCESS"] = EGL_BAD_ACCESS;
    env["EGL_BAD_ALLOC"] = EGL_BAD_ALLOC;
    env["EGL_BAD_ATTRIBUTE"] = EGL_BAD_ATTRIBUTE;
    env["EGL_BAD_CONFIG"] = EGL_BAD_CONFIG;
    env["EGL_BAD_CONTEXT"] = EGL_BAD_CONTEXT;
    env["EGL_BAD_CURRENT_SURFACE"] = EGL_BAD_CURRENT_SURFACE;
    env["EGL_BAD_DISPLAY"] = EGL_BAD_DISPLAY;
    env["EGL_BAD_MATCH"] = EGL_BAD_MATCH;
    env["EGL_BAD_NATIVE_PIXMAP"] = EGL_BAD_NATIVE_PIXMAP;
    env["EGL_BAD_NATIVE_WINDOW"] = EGL_BAD_NATIVE_WINDOW;
    env["EGL_BAD_PARAMETER"] = EGL_BAD_PARAMETER;
    env["EGL_BAD_SURFACE"] = EGL_BAD_SURFACE;
    env["EGL_CONTEXT_LOST"] = EGL_CONTEXT_LOST;

    /* Reserved 0x300F-0x301F for additional errors */

    /* Config attributes */
    env["EGL_BUFFER_SIZE"] = EGL_BUFFER_SIZE;
    env["EGL_ALPHA_SIZE"] = EGL_ALPHA_SIZE;
    env["EGL_BLUE_SIZE"] = EGL_BLUE_SIZE;
    env["EGL_GREEN_SIZE"] = EGL_GREEN_SIZE;
    env["EGL_RED_SIZE"] = EGL_RED_SIZE;
    env["EGL_DEPTH_SIZE"] = EGL_DEPTH_SIZE;
    env["EGL_STENCIL_SIZE"] = EGL_STENCIL_SIZE;
    env["EGL_CONFIG_CAVEAT"] = EGL_CONFIG_CAVEAT;
    env["EGL_CONFIG_ID"] = EGL_CONFIG_ID;
    env["EGL_LEVEL"] = EGL_LEVEL;
    env["EGL_MAX_PBUFFER_HEIGHT"] = EGL_MAX_PBUFFER_HEIGHT;
    env["EGL_MAX_PBUFFER_PIXELS"] = EGL_MAX_PBUFFER_PIXELS;
    env["EGL_MAX_PBUFFER_WIDTH"] = EGL_MAX_PBUFFER_WIDTH;
    env["EGL_NATIVE_RENDERABLE"] = EGL_NATIVE_RENDERABLE;
    env["EGL_NATIVE_VISUAL_ID"] = EGL_NATIVE_VISUAL_ID;
    env["EGL_NATIVE_VISUAL_TYPE"] = EGL_NATIVE_VISUAL_TYPE;
    env["EGL_SAMPLES"] = EGL_SAMPLES;
    env["EGL_SAMPLE_BUFFERS"] = EGL_SAMPLE_BUFFERS;
    env["EGL_SURFACE_TYPE"] = EGL_SURFACE_TYPE;
    env["EGL_TRANSPARENT_TYPE"] = EGL_TRANSPARENT_TYPE;
    env["EGL_TRANSPARENT_BLUE_VALUE"] = EGL_TRANSPARENT_BLUE_VALUE;
    env["EGL_TRANSPARENT_GREEN_VALUE"] = EGL_TRANSPARENT_GREEN_VALUE;
    env["EGL_TRANSPARENT_RED_VALUE"] = EGL_TRANSPARENT_RED_VALUE;
    env["EGL_NONE"] = EGL_NONE;
    env["EGL_BIND_TO_TEXTURE_RGB"] = EGL_BIND_TO_TEXTURE_RGB;
    env["EGL_BIND_TO_TEXTURE_RGBA"] = EGL_BIND_TO_TEXTURE_RGBA;
    env["EGL_MIN_SWAP_INTERVAL"] = EGL_MIN_SWAP_INTERVAL;
    env["EGL_MAX_SWAP_INTERVAL"] = EGL_MAX_SWAP_INTERVAL;
    env["EGL_LUMINANCE_SIZE"] = EGL_LUMINANCE_SIZE;
    env["EGL_ALPHA_MASK_SIZE"] = EGL_ALPHA_MASK_SIZE;
    env["EGL_COLOR_BUFFER_TYPE"] = EGL_COLOR_BUFFER_TYPE;
    env["EGL_RENDERABLE_TYPE"] = EGL_RENDERABLE_TYPE;
    env["EGL_MATCH_NATIVE_PIXMAP"] = EGL_MATCH_NATIVE_PIXMAP;
    env["EGL_CONFORMANT"] = EGL_CONFORMANT;

    /* Reserved 0x3041-0x304F for additional config attributes */

    /* Config attribute values */
    env["EGL_SLOW_CONFIG"] = EGL_SLOW_CONFIG;
    env["EGL_NON_CONFORMANT_CONFIG"] = EGL_NON_CONFORMANT_CONFIG;
    env["EGL_TRANSPARENT_RGB"] = EGL_TRANSPARENT_RGB;
    env["EGL_RGB_BUFFER"] = EGL_RGB_BUFFER;
    env["EGL_LUMINANCE_BUFFER"] = EGL_LUMINANCE_BUFFER;

    /* More config attribute values, for EGL_TEXTURE_FORMAT */
    env["EGL_NO_TEXTURE"] = EGL_NO_TEXTURE;
    env["EGL_TEXTURE_RGB"] = EGL_TEXTURE_RGB;
    env["EGL_TEXTURE_RGBA"] = EGL_TEXTURE_RGBA;
    env["EGL_TEXTURE_2D"] = EGL_TEXTURE_2D;

    /* Config attribute mask bits */
    env["EGL_PBUFFER_BIT"] = EGL_PBUFFER_BIT;
    env["EGL_PIXMAP_BIT"] = EGL_PIXMAP_BIT;
    env["EGL_WINDOW_BIT"] = EGL_WINDOW_BIT;
    env["EGL_VG_COLORSPACE_LINEAR_BIT"] = EGL_VG_COLORSPACE_LINEAR_BIT;
    env["EGL_VG_ALPHA_FORMAT_PRE_BIT"] = EGL_VG_ALPHA_FORMAT_PRE_BIT;
    env["EGL_MULTISAMPLE_RESOLVE_BOX_BIT"] = EGL_MULTISAMPLE_RESOLVE_BOX_BIT;
    env["EGL_SWAP_BEHAVIOR_PRESERVED_BIT"] = EGL_SWAP_BEHAVIOR_PRESERVED_BIT;

    env["EGL_OPENGL_ES_BIT"] = EGL_OPENGL_ES_BIT;
    env["EGL_OPENVG_BIT"] = EGL_OPENVG_BIT;
    env["EGL_OPENGL_ES2_BIT"] = EGL_OPENGL_ES2_BIT;
    env["EGL_OPENGL_BIT"] = EGL_OPENGL_BIT;

    /* QueryString targets */
    env["EGL_VENDOR"] = EGL_VENDOR;
    env["EGL_VERSION"] = EGL_VERSION;
    env["EGL_EXTENSIONS"] = EGL_EXTENSIONS;
    env["EGL_CLIENT_APIS"] = EGL_CLIENT_APIS;

    /* QuerySurface / SurfaceAttrib / CreatePbufferSurface targets */
    env["EGL_HEIGHT"] = EGL_HEIGHT;
    env["EGL_WIDTH"] = EGL_WIDTH;
    env["EGL_LARGEST_PBUFFER"] = EGL_LARGEST_PBUFFER;
    env["EGL_TEXTURE_FORMAT"] = EGL_TEXTURE_FORMAT;
    env["EGL_TEXTURE_TARGET"] = EGL_TEXTURE_TARGET;
    env["EGL_MIPMAP_TEXTURE"] = EGL_MIPMAP_TEXTURE;
    env["EGL_MIPMAP_LEVEL"] = EGL_MIPMAP_LEVEL;
    env["EGL_RENDER_BUFFER"] = EGL_RENDER_BUFFER;
    env["EGL_VG_COLORSPACE"] = EGL_VG_COLORSPACE;
    env["EGL_VG_ALPHA_FORMAT"] = EGL_VG_ALPHA_FORMAT;
    env["EGL_HORIZONTAL_RESOLUTION"] = EGL_HORIZONTAL_RESOLUTION;
    env["EGL_VERTICAL_RESOLUTION"] = EGL_VERTICAL_RESOLUTION;
    env["EGL_PIXEL_ASPECT_RATIO"] = EGL_PIXEL_ASPECT_RATIO;
    env["EGL_SWAP_BEHAVIOR"] = EGL_SWAP_BEHAVIOR;
    env["EGL_MULTISAMPLE_RESOLVE"] = EGL_MULTISAMPLE_RESOLVE;

    /* EGL_RENDER_BUFFER values / BindTexImage / ReleaseTexImage buffer targets */
    env["EGL_BACK_BUFFER"] = EGL_BACK_BUFFER;
    env["EGL_SINGLE_BUFFER"] = EGL_SINGLE_BUFFER;

    /* OpenVG color spaces */
    env["EGL_VG_COLORSPACE_sRGB"] = EGL_VG_COLORSPACE_sRGB;
    env["EGL_VG_COLORSPACE_LINEAR"] = EGL_VG_COLORSPACE_LINEAR;

    /* OpenVG alpha formats */
    env["EGL_VG_ALPHA_FORMAT_NONPRE"] = EGL_VG_ALPHA_FORMAT_NONPRE;
    env["EGL_VG_ALPHA_FORMAT_PRE"] = EGL_VG_ALPHA_FORMAT_PRE;

    /* Constant scale factor by which fractional display resolutions &
     * aspect ratio are scaled when queried as integer values.
     */
    env["EGL_DISPLAY_SCALING"] = EGL_DISPLAY_SCALING;

    /* Unknown display resolution/aspect ratio */
    env["EGL_UNKNOWN"] = EGL_UNKNOWN;

    /* Back buffer swap behaviors */
    env["EGL_BUFFER_PRESERVED"] = EGL_BUFFER_PRESERVED;
    env["EGL_BUFFER_DESTROYED"] = EGL_BUFFER_DESTROYED;

    /* CreatePbufferFromClientBuffer buffer types */
    env["EGL_OPENVG_IMAGE"] = EGL_OPENVG_IMAGE;

    /* QueryContext targets */
    env["EGL_CONTEXT_CLIENT_TYPE"] = EGL_CONTEXT_CLIENT_TYPE;

    /* CreateContext attributes */
    env["EGL_CONTEXT_CLIENT_VERSION"] = EGL_CONTEXT_CLIENT_VERSION;

    /* Multisample resolution behaviors */
    env["EGL_MULTISAMPLE_RESOLVE_DEFAULT"] = EGL_MULTISAMPLE_RESOLVE_DEFAULT;
    env["EGL_MULTISAMPLE_RESOLVE_BOX"] = EGL_MULTISAMPLE_RESOLVE_BOX;

    /* BindAPI/QueryAPI targets */
    env["EGL_OPENGL_ES_API"] = EGL_OPENGL_ES_API;
    env["EGL_OPENVG_API"] = EGL_OPENVG_API;
    env["EGL_OPENGL_API"] = EGL_OPENGL_API;

    /* GetCurrentSurface targets */
    env["EGL_DRAW"] = EGL_DRAW;
    env["EGL_READ"] = EGL_READ;

    /* WaitNative engines */
    env["EGL_CORE_NATIVE_ENGINE"] = EGL_CORE_NATIVE_ENGINE;

    /* EGL 1.2 tokens renamed for consistency in EGL 1.3 */
    env["EGL_COLORSPACE"] = EGL_COLORSPACE;
    env["EGL_ALPHA_FORMAT"] = EGL_ALPHA_FORMAT;
    env["EGL_COLORSPACE_sRGB"] = EGL_COLORSPACE_sRGB;
    env["EGL_COLORSPACE_LINEAR"] = EGL_COLORSPACE_LINEAR;
    env["EGL_ALPHA_FORMAT_NONPRE"] = EGL_ALPHA_FORMAT_NONPRE;
    env["EGL_ALPHA_FORMAT_PRE"] = EGL_ALPHA_FORMAT_PRE;

    /* EGL extensions must request enum blocks from the Khronos
     * API Registrar, who maintains the enumerant registry. Submit
     * a bug in Khronos Bugzilla against task "Registry".
     */

    return 0;
}

#include "gbm.hpp"

#include "luacxx/convert/callable.hpp"
#include "luacxx/thread.hpp"

#include <gbm.h>

int _gbm_bo_write(lua_State* const state)
{
    return 0;
}

int _gbm_bo_set_user_data(lua_State* const state)
{
    return 0;
}

int _gbm_bo_get_user_data(lua_State* const state)
{
    return 0;
}

int luaopen_gbm(lua_State* const state)
{
    lua::thread env(state);

    /** Format of the allocated buffer */
    env["GBM_BO_FORMAT_XRGB8888"] = GBM_BO_FORMAT_XRGB8888;
    env["GBM_BO_FORMAT_ARGB8888"] = GBM_BO_FORMAT_ARGB8888; 

    env["GBM_FORMAT_BIG_ENDIAN"] = GBM_FORMAT_BIG_ENDIAN;

    /* color index */
    env["GBM_FORMAT_C8"] = GBM_FORMAT_C8;

    /* 8 bpp RGB */
    env["GBM_FORMAT_RGB332"] = GBM_FORMAT_RGB332;
    env["GBM_FORMAT_BGR233"] = GBM_FORMAT_BGR233;

    /* 16 bpp RGB */
    env["GBM_FORMAT_XRGB4444"] = GBM_FORMAT_XRGB4444;
    env["GBM_FORMAT_XBGR4444"] = GBM_FORMAT_XBGR4444;
    env["GBM_FORMAT_RGBX4444"] = GBM_FORMAT_RGBX4444;
    env["GBM_FORMAT_BGRX4444"] = GBM_FORMAT_BGRX4444;

    env["GBM_FORMAT_ARGB4444"] = GBM_FORMAT_ARGB4444;
    env["GBM_FORMAT_ABGR4444"] = GBM_FORMAT_ABGR4444;
    env["GBM_FORMAT_RGBA4444"] = GBM_FORMAT_RGBA4444;
    env["GBM_FORMAT_BGRA4444"] = GBM_FORMAT_BGRA4444;

    env["GBM_FORMAT_XRGB1555"] = GBM_FORMAT_XRGB1555;
    env["GBM_FORMAT_XBGR1555"] = GBM_FORMAT_XBGR1555;
    env["GBM_FORMAT_RGBX5551"] = GBM_FORMAT_RGBX5551;
    env["GBM_FORMAT_BGRX5551"] = GBM_FORMAT_BGRX5551;

    env["GBM_FORMAT_ARGB1555"] = GBM_FORMAT_ARGB1555;
    env["GBM_FORMAT_ABGR1555"] = GBM_FORMAT_ABGR1555;
    env["GBM_FORMAT_RGBA5551"] = GBM_FORMAT_RGBA5551;
    env["GBM_FORMAT_BGRA5551"] = GBM_FORMAT_BGRA5551;

    env["GBM_FORMAT_RGB565"] = GBM_FORMAT_RGB565;
    env["GBM_FORMAT_BGR565"] = GBM_FORMAT_BGR565;

    /* 24 bpp RGB */
    env["GBM_FORMAT_RGB888"] = GBM_FORMAT_RGB888;
    env["GBM_FORMAT_BGR888"] = GBM_FORMAT_BGR888;

    /* 32 bpp RGB */
    env["GBM_FORMAT_XRGB8888"] = GBM_FORMAT_XRGB8888;
    env["GBM_FORMAT_XBGR8888"] = GBM_FORMAT_XBGR8888;
    env["GBM_FORMAT_RGBX8888"] = GBM_FORMAT_RGBX8888;
    env["GBM_FORMAT_BGRX8888"] = GBM_FORMAT_BGRX8888;

    env["GBM_FORMAT_ARGB8888"] = GBM_FORMAT_ARGB8888;
    env["GBM_FORMAT_ABGR8888"] = GBM_FORMAT_ABGR8888;
    env["GBM_FORMAT_RGBA8888"] = GBM_FORMAT_RGBA8888;
    env["GBM_FORMAT_BGRA8888"] = GBM_FORMAT_BGRA8888;

    env["GBM_FORMAT_XRGB2101010"] = GBM_FORMAT_XRGB2101010;
    env["GBM_FORMAT_XBGR2101010"] = GBM_FORMAT_XBGR2101010;
    env["GBM_FORMAT_RGBX1010102"] = GBM_FORMAT_RGBX1010102;
    env["GBM_FORMAT_BGRX1010102"] = GBM_FORMAT_BGRX1010102;

    env["GBM_FORMAT_ARGB2101010"] = GBM_FORMAT_ARGB2101010;
    env["GBM_FORMAT_ABGR2101010"] = GBM_FORMAT_ABGR2101010;
    env["GBM_FORMAT_RGBA1010102"] = GBM_FORMAT_RGBA1010102;
    env["GBM_FORMAT_BGRA1010102"] = GBM_FORMAT_BGRA1010102;

    /* packed YCbCr */
    env["GBM_FORMAT_YUYV"] = GBM_FORMAT_YUYV;
    env["GBM_FORMAT_YVYU"] = GBM_FORMAT_YVYU;
    env["GBM_FORMAT_UYVY"] = GBM_FORMAT_UYVY;
    env["GBM_FORMAT_VYUY"] = GBM_FORMAT_VYUY;

    env["GBM_FORMAT_AYUV"] = GBM_FORMAT_AYUV;

    /*
    * 2 plane YCbCr
    * index 0 = Y plane, [7:0] Y
    * index 1 = Cr:Cb plane, [15:0] Cr:Cb little endian
    * or
    * index 1 = Cb:Cr plane, [15:0] Cb:Cr little endian
    */
    env["GBM_FORMAT_NV12"] = GBM_FORMAT_NV12;
    env["GBM_FORMAT_NV21"] = GBM_FORMAT_NV21;
    env["GBM_FORMAT_NV16"] = GBM_FORMAT_NV16;
    env["GBM_FORMAT_NV61"] = GBM_FORMAT_NV61;

    /*
    * 3 plane YCbCr
    * index 0: Y plane, [7:0] Y
    * index 1: Cb plane, [7:0] Cb
    * index 2: Cr plane, [7:0] Cr
    * or
    * index 1: Cr plane, [7:0] Cr
    * index 2: Cb plane, [7:0] Cb
    */
    env["GBM_FORMAT_YUV410"] = GBM_FORMAT_YUV410;
    env["GBM_FORMAT_YVU410"] = GBM_FORMAT_YVU410;
    env["GBM_FORMAT_YUV411"] = GBM_FORMAT_YUV411;
    env["GBM_FORMAT_YVU411"] = GBM_FORMAT_YVU411;
    env["GBM_FORMAT_YUV420"] = GBM_FORMAT_YUV420;
    env["GBM_FORMAT_YVU420"] = GBM_FORMAT_YVU420;
    env["GBM_FORMAT_YUV422"] = GBM_FORMAT_YUV422;
    env["GBM_FORMAT_YVU422"] = GBM_FORMAT_YVU422;
    env["GBM_FORMAT_YUV444"] = GBM_FORMAT_YUV444;
    env["GBM_FORMAT_YVU444"] = GBM_FORMAT_YVU444;

    // enum gbm_bo_flags
    env["GBM_BO_USE_SCANOUT"] = GBM_BO_USE_SCANOUT;
    env["GBM_BO_USE_CURSOR_64X64"] = GBM_BO_USE_CURSOR_64X64;
    env["GBM_BO_USE_RENDERING"] = GBM_BO_USE_RENDERING;
    env["GBM_BO_USE_WRITE"] = GBM_BO_USE_WRITE;

    env["gbm_device_get_fd"] = gbm_device_get_fd;
    env["gbm_device_get_backend_name"] = gbm_device_get_backend_name;
    env["gbm_device_is_format_supported"] = gbm_device_is_format_supported;
    env["gbm_device_destroy"] = gbm_device_destroy;
    env["gbm_create_device"] = gbm_create_device;
    env["gbm_bo_create"] = gbm_bo_create;

    env["GBM_BO_IMPORT_WL_BUFFER"] = GBM_BO_IMPORT_WL_BUFFER;
    env["GBM_BO_IMPORT_EGL_IMAGE"] = GBM_BO_IMPORT_EGL_IMAGE;

    env["gbm_bo_import"] = gbm_bo_import;
    env["gbm_bo_get_width"] = gbm_bo_get_width;
    env["gbm_bo_get_height"] = gbm_bo_get_height;
    env["gbm_bo_get_stride"] = gbm_bo_get_stride;
    env["gbm_bo_get_format"] = gbm_bo_get_format;
    env["gbm_bo_get_device"] = gbm_bo_get_device;

    env["gbm_bo_get_handle"] = gbm_bo_get_handle;

    env["gbm_bo_write"] = _gbm_bo_write;
    env["gbm_bo_set_user_data"] = _gbm_bo_set_user_data;
    env["gbm_bo_get_user_data"] = _gbm_bo_get_user_data;

    env["gbm_bo_destroy"] = gbm_bo_destroy;
    env["gbm_surface_create"] = gbm_surface_create;
    env["gbm_surface_lock_front_buffer"] = gbm_surface_lock_front_buffer;
    env["gbm_surface_release_buffer"] = gbm_surface_release_buffer;
    env["gbm_surface_has_free_buffers"] = gbm_surface_has_free_buffers;
    env["gbm_surface_destroy"] = gbm_surface_destroy;

    return 0;
}

#include <xf86drmMode.hpp>

#include "luacxx/stack.hpp"
#include "luacxx/thread.hpp"
#include "luacxx/convert/numeric.hpp"
#include "luacxx/convert/callable.hpp"
#include "luacxx/convert/vector.hpp"

int _drmModeDirtyFB(lua_State* const state)
{
    if (lua_gettop(state) == 3) {
        std::vector<drm_clip_rect> clips;
        lua::store(clips, state, 3);
        lua::push(state, drmModeDirtyFB(
            lua::get<int>(state, 1),
            lua::get<uint32_t>(state, 2),
            &clips[0],
            clips.size()
        ));
    } else {
        lua::push(state, drmModeDirtyFB(
            lua::get<int>(state, 1),
            lua::get<uint32_t>(state, 2),
            lua::get<drm_clip_rect*>(state, 3),
            lua::get<uint32_t>(state, 4)
        ));
    }
    return 1;
}

int _drmModeAddFB(lua_State* const state)
{
    uint32_t buf_id;
    lua::push(state, drmModeAddFB(
        lua::get<int>(state, 1),
        lua::get<uint32_t>(state, 2), // width
        lua::get<uint32_t>(state, 3), // height
        lua::get<uint8_t>(state, 4), // depth
        lua::get<uint8_t>(state, 5), // bpp
        lua::get<uint32_t>(state, 6), // pitch
        lua::get<uint32_t>(state, 7), // bo_handle
        &buf_id
    ));
    lua::push(state, buf_id);
    return 2;
}

int _drmModeAddFB2(lua_State* const state)
{
    std::vector<uint32_t> bo_handles;
    lua::store(bo_handles, state, 5);
    bo_handles.resize(4);

    std::vector<uint32_t> pitches;
    lua::store(pitches, state, 6);
    pitches.resize(4);

    std::vector<uint32_t> offsets;
    lua::store(offsets, state, 7);
    offsets.resize(4);

    uint32_t buf_id;
    lua::push(state, drmModeAddFB2(
        lua::get<int>(state, 1),
        lua::get<uint32_t>(state, 2), // width
        lua::get<uint32_t>(state, 3), // height
        lua::get<uint32_t>(state, 4), // pixel format,
        &bo_handles[0], // bo_handles
        &pitches[0], // pitches
        &offsets[0], // offsets
        &buf_id,
        lua::get<uint32_t>(state, 8)
    ));
    lua::push(state, buf_id);
    return 2;
}

int _drmModeSetCrtc(lua_State* const state)

{
    if (lua_gettop(state) > 7) {
        lua::push(state, drmModeSetCrtc(
            lua::get<int>(state, 1), // fd
            lua::get<uint32_t>(state, 2), // crtcId
            lua::get<uint32_t>(state, 3), // bufferId
            lua::get<uint32_t>(state, 4), // x
            lua::get<uint32_t>(state, 5), // y
            lua::get<uint32_t*>(state, 6), // connectors
            lua::get<int>(state, 7), // count
            lua::get<drmModeModeInfoPtr>(state, 8) // mode
        ));
        return 1;
    }

    std::vector<uint32_t> connectors;
    if (lua_type(state, 6) == LUA_TTABLE) {
        lua::store(connectors, state, 6);
    } else {
        connectors.push_back(lua::get<uint32_t>(state, 6));
    }

    lua::push(state, drmModeSetCrtc(
        lua::get<int>(state, 1), // fd
        lua::get<uint32_t>(state, 2), // crtcId
        lua::get<uint32_t>(state, 3), // bufferId
        lua::get<uint32_t>(state, 4), // x
        lua::get<uint32_t>(state, 5), // y
        &connectors[0], // connectors
        connectors.size(), // count
        lua::get<drmModeModeInfoPtr>(state, 8) // mode
    ));
    return 1;
}

int _drmModeCrtcSetGamma(lua_State* const state)
{
    // extern int drmModeCrtcSetGamma(int fd, uint32_t crtc_id, uint32_t size, uint16_t *red, uint16_t *green, uint16_t *blue);
    auto size = lua::get<uint32_t>(state, 3);

    std::vector<uint16_t> red;
    lua::store(red, state, 4);
    red.resize(size);

    std::vector<uint16_t> green;
    lua::store(green, state, 4);
    green.resize(size);

    std::vector<uint16_t> blue;
    lua::store(blue, state, 4);
    blue.resize(size);

    lua::push(state, drmModeCrtcSetGamma(
        lua::get<int>(state, 1), // fd
        lua::get<uint32_t>(state, 2), // crtc_id
        size,
        &red[0],
        &green[0],
        &blue[0]
    ));

    return 1;
}

int _drmModeCrtcGetGamma(lua_State* const state)
{
    // extern int drmModeCrtcGetGamma(int fd, uint32_t crtc_id, uint32_t size, uint16_t *red, uint16_t *green, uint16_t *blue);
    auto size = lua::get<uint32_t>(state, 3);

    std::vector<uint16_t> red;
    red.resize(size);

    std::vector<uint16_t> green;
    green.resize(size);

    std::vector<uint16_t> blue;
    blue.resize(size);

    lua::push(state, drmModeCrtcGetGamma(
        lua::get<int>(state, 1), // fd
        lua::get<uint32_t>(state, 2), // crtc_id
        size,
        &red[0],
        &green[0],
        &blue[0]
    ));

    return 1;
}

int luaopen_xf86drmMode(lua_State* const state)
{
    // TODO drmEventContext pointers
    lua::thread env(state);

    env["drmModeFreeModeInfo"] = drmModeFreeModeInfo;
    env["drmModeFreeResources"] = drmModeFreeResources;
    env["drmModeFreeFB"] = drmModeFreeFB;
    env["drmModeFreeCrtc"] = drmModeFreeCrtc;
    env["drmModeFreeConnector"] = drmModeFreeConnector;
    env["drmModeFreeEncoder"] = drmModeFreeEncoder;
    env["drmModeFreePlane"] = drmModeFreePlane;
    env["drmModeFreePlaneResources"] = drmModeFreePlaneResources;

    /**
     * Retrieves all of the resources associated with a card.
     */
    env["drmModeGetResources"] = drmModeGetResources;

    /*
     * FrameBuffer manipulation.
     */

    /**
     * Retrive information about framebuffer bufferId
     */
    env["drmModeGetFB"] = drmModeGetFB;

    /**
     * Creates a new framebuffer with an buffer object as its scanout buffer.
     */
    env["drmModeAddFB"] = _drmModeAddFB;
    /* ...with a specific pixel format */
    env["drmModeAddFB2"] = _drmModeAddFB2;

    /**
     * Destroys the given framebuffer.
     */
    env["drmModeRmFB"] = drmModeRmFB;

    /**
     * Mark a region of a framebuffer as dirty.
     */
    env["drmModeDirtyFB"] = _drmModeDirtyFB;

    /*
     * Crtc functions
     */

    /**
     * Retrive information about the ctrt crtcId
     */
    env["drmModeGetCrtc"] = drmModeGetCrtc;

    /**
     * Set the mode on a crtc crtcId with the given mode modeId.
     */
    env["drmModeSetCrtc"] = _drmModeSetCrtc;

    /*
     * Cursor functions
     */

    /**
     * Set the cursor on crtc
     */
    env["drmModeSetCursor"] = drmModeSetCursor;
    env["drmModeSetCursor2"] = drmModeSetCursor2;

    /**
     * Move the cursor on crtc
     */
    env["drmModeMoveCursor"] = drmModeMoveCursor;

    /**
     * Encoder functions
     */
    env["drmModeGetEncoder"] = drmModeGetEncoder;

    /*
     * Connector manipulation
     */

    /**
     * Retrive information about the connector connectorId.
     */
    env["drmModeGetConnector"] = drmModeGetConnector;

    /**
     * Attaches the given mode to an connector.
     */
    env["drmModeAttachMode"] = drmModeAttachMode;

    /**
     * Detaches a mode from the connector
     * must be unused, by the given mode.
     */
    env["drmModeDetachMode"] = drmModeDetachMode;

    env["drmModeGetProperty"] = drmModeGetProperty;
    env["drmModeFreeProperty"] = drmModeFreeProperty;

    env["drmModeGetPropertyBlob"] = drmModeGetPropertyBlob;
    env["drmModeFreePropertyBlob"] = drmModeFreePropertyBlob;
    env["drmModeConnectorSetProperty"] = drmModeConnectorSetProperty;

    env["drmCheckModesettingSupported"] = drmCheckModesettingSupported;

    env["drmModeCrtcSetGamma"] = _drmModeCrtcSetGamma;
    env["drmModeCrtcGetGamma"] = _drmModeCrtcGetGamma;
    env["drmModePageFlip"] = drmModePageFlip;

    env["drmModeGetPlaneResources"] = drmModeGetPlaneResources;
    env["drmModeGetPlane"] = drmModeGetPlane;
    env["drmModeSetPlane"] = drmModeSetPlane;

    env["drmModeObjectGetProperties"] = drmModeObjectGetProperties;
    env["drmModeFreeObjectProperties"] = drmModeFreeObjectProperties;
    env["drmModeObjectSetProperty"] = drmModeObjectSetProperty;

    env["DRM_DISPLAY_INFO_LEN"] = DRM_DISPLAY_INFO_LEN;
    env["DRM_CONNECTOR_NAME_LEN"] = DRM_CONNECTOR_NAME_LEN;
    env["DRM_DISPLAY_MODE_LEN"] = DRM_DISPLAY_MODE_LEN;
    env["DRM_PROP_NAME_LEN"] = DRM_PROP_NAME_LEN;

    env["DRM_MODE_TYPE_BUILTIN"] = DRM_MODE_TYPE_BUILTIN;
    env["DRM_MODE_TYPE_CLOCK_C"] = DRM_MODE_TYPE_CLOCK_C;
    env["DRM_MODE_TYPE_CRTC_C"] = DRM_MODE_TYPE_CRTC_C;
    env["DRM_MODE_TYPE_PREFERRED"] = DRM_MODE_TYPE_PREFERRED;
    env["DRM_MODE_TYPE_DEFAULT"] = DRM_MODE_TYPE_DEFAULT;
    env["DRM_MODE_TYPE_USERDEF"] = DRM_MODE_TYPE_USERDEF;
    env["DRM_MODE_TYPE_DRIVER"] = DRM_MODE_TYPE_DRIVER;

    /* Video mode flags */
    /* bit compatible with the xorg definitions. */
    env["DRM_MODE_FLAG_PHSYNC"] = DRM_MODE_FLAG_PHSYNC;
    env["DRM_MODE_FLAG_NHSYNC"] = DRM_MODE_FLAG_NHSYNC;
    env["DRM_MODE_FLAG_PVSYNC"] = DRM_MODE_FLAG_PVSYNC;
    env["DRM_MODE_FLAG_NVSYNC"] = DRM_MODE_FLAG_NVSYNC;
    env["DRM_MODE_FLAG_INTERLACE"] = DRM_MODE_FLAG_INTERLACE;
    env["DRM_MODE_FLAG_DBLSCAN"] = DRM_MODE_FLAG_DBLSCAN;
    env["DRM_MODE_FLAG_CSYNC"] = DRM_MODE_FLAG_CSYNC;
    env["DRM_MODE_FLAG_PCSYNC"] = DRM_MODE_FLAG_PCSYNC;
    env["DRM_MODE_FLAG_NCSYNC"] = DRM_MODE_FLAG_NCSYNC;
    env["DRM_MODE_FLAG_HSKEW"] = DRM_MODE_FLAG_HSKEW;
    env["DRM_MODE_FLAG_BCAST"] = DRM_MODE_FLAG_BCAST;
    env["DRM_MODE_FLAG_PIXMUX"] = DRM_MODE_FLAG_PIXMUX;
    env["DRM_MODE_FLAG_DBLCLK"] = DRM_MODE_FLAG_DBLCLK;
    env["DRM_MODE_FLAG_CLKDIV2"] = DRM_MODE_FLAG_CLKDIV2;
    env["DRM_MODE_FLAG_3D_MASK"] = DRM_MODE_FLAG_3D_MASK;
    env["DRM_MODE_FLAG_3D_NONE"] = DRM_MODE_FLAG_3D_NONE;
    env["DRM_MODE_FLAG_3D_FRAME_PACKING"] = DRM_MODE_FLAG_3D_FRAME_PACKING;
    env["DRM_MODE_FLAG_3D_FIELD_ALTERNATIVE"] = DRM_MODE_FLAG_3D_FIELD_ALTERNATIVE;
    env["DRM_MODE_FLAG_3D_LINE_ALTERNATIVE"] = DRM_MODE_FLAG_3D_LINE_ALTERNATIVE;
    env["DRM_MODE_FLAG_3D_SIDE_BY_SIDE_FULL"] = DRM_MODE_FLAG_3D_SIDE_BY_SIDE_FULL;
    env["DRM_MODE_FLAG_3D_L_DEPTH"] = DRM_MODE_FLAG_3D_L_DEPTH;
    env["DRM_MODE_FLAG_3D_L_DEPTH_GFX_GFX_DEPTH"] = DRM_MODE_FLAG_3D_L_DEPTH_GFX_GFX_DEPTH;
    env["DRM_MODE_FLAG_3D_TOP_AND_BOTTOM"] = DRM_MODE_FLAG_3D_TOP_AND_BOTTOM;
    env["DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF"] = DRM_MODE_FLAG_3D_SIDE_BY_SIDE_HALF;

    /* DPMS flags */
    /* bit compatible with the xorg definitions. */
    env["DRM_MODE_DPMS_ON"] = DRM_MODE_DPMS_ON;
    env["DRM_MODE_DPMS_STANDBY"] = DRM_MODE_DPMS_STANDBY;
    env["DRM_MODE_DPMS_SUSPEND"] = DRM_MODE_DPMS_SUSPEND;
    env["DRM_MODE_DPMS_OFF"] = DRM_MODE_DPMS_OFF;

    /* Scaling mode options */
    env["DRM_MODE_SCALE_NONE"] = DRM_MODE_SCALE_NONE;
    env["DRM_MODE_SCALE_FULLSCREEN"] = DRM_MODE_SCALE_FULLSCREEN;
    env["DRM_MODE_SCALE_CENTER"] = DRM_MODE_SCALE_CENTER;
    env["DRM_MODE_SCALE_ASPECT"] = DRM_MODE_SCALE_ASPECT;

    /* Dithering mode options */
    env["DRM_MODE_DITHERING_OFF"] = DRM_MODE_DITHERING_OFF;
    env["DRM_MODE_DITHERING_ON"] = DRM_MODE_DITHERING_ON;

    env["DRM_MODE_ENCODER_NONE"] = DRM_MODE_ENCODER_NONE;
    env["DRM_MODE_ENCODER_DAC"] = DRM_MODE_ENCODER_DAC;
    env["DRM_MODE_ENCODER_TMDS"] = DRM_MODE_ENCODER_TMDS;
    env["DRM_MODE_ENCODER_LVDS"] = DRM_MODE_ENCODER_LVDS;
    env["DRM_MODE_ENCODER_TVDAC"] = DRM_MODE_ENCODER_TVDAC;
    env["DRM_MODE_ENCODER_VIRTUAL"] = DRM_MODE_ENCODER_VIRTUAL;
    env["DRM_MODE_ENCODER_DSI"] = DRM_MODE_ENCODER_DSI;

    env["DRM_MODE_SUBCONNECTOR_Automatic"] = DRM_MODE_SUBCONNECTOR_Automatic;
    env["DRM_MODE_SUBCONNECTOR_Unknown"] = DRM_MODE_SUBCONNECTOR_Unknown;
    env["DRM_MODE_SUBCONNECTOR_DVID"] = DRM_MODE_SUBCONNECTOR_DVID;
    env["DRM_MODE_SUBCONNECTOR_DVIA"] = DRM_MODE_SUBCONNECTOR_DVIA;
    env["DRM_MODE_SUBCONNECTOR_Composite"] = DRM_MODE_SUBCONNECTOR_Composite;
    env["DRM_MODE_SUBCONNECTOR_SVIDEO"] = DRM_MODE_SUBCONNECTOR_SVIDEO;
    env["DRM_MODE_SUBCONNECTOR_Component"] = DRM_MODE_SUBCONNECTOR_Component;
    env["DRM_MODE_SUBCONNECTOR_SCART"] = DRM_MODE_SUBCONNECTOR_SCART;

    env["DRM_MODE_CONNECTOR_Unknown"] = DRM_MODE_CONNECTOR_Unknown;
    env["DRM_MODE_CONNECTOR_VGA"] = DRM_MODE_CONNECTOR_VGA;
    env["DRM_MODE_CONNECTOR_DVII"] = DRM_MODE_CONNECTOR_DVII;
    env["DRM_MODE_CONNECTOR_DVID"] = DRM_MODE_CONNECTOR_DVID;
    env["DRM_MODE_CONNECTOR_DVIA"] = DRM_MODE_CONNECTOR_DVIA;
    env["DRM_MODE_CONNECTOR_Composite"] = DRM_MODE_CONNECTOR_Composite;
    env["DRM_MODE_CONNECTOR_SVIDEO"] = DRM_MODE_CONNECTOR_SVIDEO;
    env["DRM_MODE_CONNECTOR_LVDS"] = DRM_MODE_CONNECTOR_LVDS;
    env["DRM_MODE_CONNECTOR_Component"] = DRM_MODE_CONNECTOR_Component;
    env["DRM_MODE_CONNECTOR_9PinDIN"] = DRM_MODE_CONNECTOR_9PinDIN;
    env["DRM_MODE_CONNECTOR_DisplayPort"] = DRM_MODE_CONNECTOR_DisplayPort;
    env["DRM_MODE_CONNECTOR_HDMIA"] = DRM_MODE_CONNECTOR_HDMIA;
    env["DRM_MODE_CONNECTOR_HDMIB"] = DRM_MODE_CONNECTOR_HDMIB;
    env["DRM_MODE_CONNECTOR_TV"] = DRM_MODE_CONNECTOR_TV;
    env["DRM_MODE_CONNECTOR_eDP"] = DRM_MODE_CONNECTOR_eDP;
    env["DRM_MODE_CONNECTOR_VIRTUAL"] = DRM_MODE_CONNECTOR_VIRTUAL;
    env["DRM_MODE_CONNECTOR_DSI"] = DRM_MODE_CONNECTOR_DSI;

    env["DRM_MODE_PROP_PENDING"] = DRM_MODE_PROP_PENDING;
    env["DRM_MODE_PROP_RANGE"] = DRM_MODE_PROP_RANGE;
    env["DRM_MODE_PROP_IMMUTABLE"] = DRM_MODE_PROP_IMMUTABLE;
    env["DRM_MODE_PROP_ENUM"] = DRM_MODE_PROP_ENUM;
    env["DRM_MODE_PROP_BLOB"] = DRM_MODE_PROP_BLOB;

    env["DRM_MODE_CURSOR_BO"] = DRM_MODE_CURSOR_BO;
    env["DRM_MODE_CURSOR_MOVE"] = DRM_MODE_CURSOR_MOVE;

    /*
     * Feature defines
     *
     * Just because these are defined doesn't mean that the kernel
     * can do that feature, its just for new code vs old libdrm.
     */
    env["DRM_MODE_FEATURE_KMS"] = DRM_MODE_FEATURE_KMS;
    env["DRM_MODE_FEATURE_DIRTYFB"] = DRM_MODE_FEATURE_DIRTYFB;

    // enum drmModeConnection
    env["DRM_MODE_CONNECTED"] = DRM_MODE_CONNECTED;
    env["DRM_MODE_DISCONNECTED"] = DRM_MODE_DISCONNECTED;
    env["DRM_MODE_UNKNOWNCONNECTION"] = DRM_MODE_UNKNOWNCONNECTION;

    // enum drmModeSubPixel
    env["DRM_MODE_SUBPIXEL_UNKNOWN"] = DRM_MODE_SUBPIXEL_UNKNOWN;
    env["DRM_MODE_SUBPIXEL_HORIZONTAL_RGB"] = DRM_MODE_SUBPIXEL_HORIZONTAL_RGB;
    env["DRM_MODE_SUBPIXEL_HORIZONTAL_BGR"] = DRM_MODE_SUBPIXEL_HORIZONTAL_BGR;
    env["DRM_MODE_SUBPIXEL_VERTICAL_RGB"] = DRM_MODE_SUBPIXEL_VERTICAL_RGB;
    env["DRM_MODE_SUBPIXEL_VERTICAL_BGR"] = DRM_MODE_SUBPIXEL_VERTICAL_BGR;
    env["DRM_MODE_SUBPIXEL_NONE"] = DRM_MODE_SUBPIXEL_NONE;

    return 0;
}

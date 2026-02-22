#include "../libinput.hpp"
#include "../thread.hpp"

// http://wayland.freedesktop.org/libinput/doc/latest/group__config.html

int lua::libinput_group__config(lua_State* const state)
{
    lua::thread env(state);

    // enum libinput_config_scroll_method
    env["LIBINPUT_CONFIG_SCROLL_NO_SCROLL"] = LIBINPUT_CONFIG_SCROLL_NO_SCROLL;
    env["LIBINPUT_CONFIG_SCROLL_2FG"] = LIBINPUT_CONFIG_SCROLL_2FG;
    env["LIBINPUT_CONFIG_SCROLL_EDGE"] = LIBINPUT_CONFIG_SCROLL_EDGE;
    env["LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN"] = LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN;

    // enum libinput_config_status
    env["LIBINPUT_CONFIG_STATUS_SUCCESS"] = LIBINPUT_CONFIG_STATUS_SUCCESS;
    env["LIBINPUT_CONFIG_STATUS_UNSUPPORTED"] = LIBINPUT_CONFIG_STATUS_UNSUPPORTED;
    env["LIBINPUT_CONFIG_STATUS_INVALID"] = LIBINPUT_CONFIG_STATUS_INVALID;

    // enum libinput_config_tap_state
    env["LIBINPUT_CONFIG_TAP_DISABLED"] = LIBINPUT_CONFIG_TAP_DISABLED;
    env["LIBINPUT_CONFIG_TAP_ENABLED"] = LIBINPUT_CONFIG_TAP_ENABLED;

    env["libinput_config_status_to_str"] = libinput_config_status_to_str;
    env["libinput_device_config_tap_get_finger_count"] = libinput_device_config_tap_get_finger_count;
    env["libinput_device_config_tap_set_enabled"] = libinput_device_config_tap_set_enabled;
    env["libinput_device_config_tap_get_enabled"] = libinput_device_config_tap_get_enabled;
    env["libinput_device_config_tap_get_default_enabled"] = libinput_device_config_tap_get_default_enabled;
    env["libinput_device_config_calibration_has_matrix"] = libinput_device_config_calibration_has_matrix;
    env["libinput_device_config_calibration_set_matrix"] = libinput_device_config_calibration_set_matrix;
    env["libinput_device_config_calibration_get_matrix"] = libinput_device_config_calibration_get_matrix;
    env["libinput_device_config_calibration_get_default_matrix"] = libinput_device_config_calibration_get_default_matrix;
    env["libinput_device_config_send_events_get_modes"] = libinput_device_config_send_events_get_modes;
    env["libinput_device_config_send_events_set_mode"] = libinput_device_config_send_events_set_mode;
    env["libinput_device_config_send_events_get_mode"] = libinput_device_config_send_events_get_mode;
    env["libinput_device_config_send_events_get_default_mode"] = libinput_device_config_send_events_get_default_mode;
    env["libinput_device_config_accel_is_available"] = libinput_device_config_accel_is_available;
    env["libinput_device_config_accel_set_speed"] = libinput_device_config_accel_set_speed;
    env["libinput_device_config_accel_get_speed"] = libinput_device_config_accel_get_speed;
    env["libinput_device_config_accel_get_default_speed"] = libinput_device_config_accel_get_default_speed;
    env["libinput_device_config_scroll_has_natural_scroll"] = libinput_device_config_scroll_has_natural_scroll;
    env["libinput_device_config_scroll_set_natural_scroll_enabled"] = libinput_device_config_scroll_set_natural_scroll_enabled;
    env["libinput_device_config_scroll_get_natural_scroll_enabled"] = libinput_device_config_scroll_get_natural_scroll_enabled;
    env["libinput_device_config_scroll_get_default_natural_scroll_enabled"] = libinput_device_config_scroll_get_default_natural_scroll_enabled;
    env["libinput_device_config_buttons_has_left_handed"] = libinput_device_config_buttons_has_left_handed;
    env["libinput_device_config_buttons_set_left_handed"] = libinput_device_config_buttons_set_left_handed;
    env["libinput_device_config_buttons_get_left_handed"] = libinput_device_config_buttons_get_left_handed;
    env["libinput_device_config_buttons_get_default_left_handed"] = libinput_device_config_buttons_get_default_left_handed;
    env["libinput_device_config_scroll_get_methods"] = libinput_device_config_scroll_get_methods;
    env["libinput_device_config_scroll_set_method"] = libinput_device_config_scroll_set_method;
    env["libinput_device_config_scroll_get_method"] = libinput_device_config_scroll_get_method;
    env["libinput_device_config_scroll_get_default_method"] = libinput_device_config_scroll_get_default_method;
    env["libinput_device_config_scroll_set_button"] = libinput_device_config_scroll_set_button;
    env["libinput_device_config_scroll_get_button"] = libinput_device_config_scroll_get_button;
    env["libinput_device_config_scroll_get_default_button"] = libinput_device_config_scroll_get_default_button;

    return 0;
}

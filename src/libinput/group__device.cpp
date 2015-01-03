#include "../libinput.hpp"
#include "../thread.hpp"

// http://wayland.freedesktop.org/libinput/doc/latest/group__device.html

int lua::libinput_group__device(lua_State* const state)
{
    lua::thread env(state);

    // enum libinput_button_state
    env["LIBINPUT_BUTTON_STATE_RELEASED"] = LIBINPUT_BUTTON_STATE_RELEASED;
    env["LIBINPUT_BUTTON_STATE_PRESSED"] = LIBINPUT_BUTTON_STATE_PRESSED;

    // enum libinput_device_capability
    env["LIBINPUT_DEVICE_CAP_KEYBOARD"] = LIBINPUT_DEVICE_CAP_KEYBOARD;
    env["LIBINPUT_DEVICE_CAP_POINTER"] = LIBINPUT_DEVICE_CAP_POINTER;
    env["LIBINPUT_DEVICE_CAP_TOUCH"] = LIBINPUT_DEVICE_CAP_TOUCH;

    // enum libinput_key_state
    env["LIBINPUT_KEY_STATE_RELEASED"] = LIBINPUT_KEY_STATE_RELEASED;
    env["LIBINPUT_KEY_STATE_PRESSED"] = LIBINPUT_KEY_STATE_PRESSED;

    // enum libinput_led
    env["LIBINPUT_LED_NUM_LOCK"] = LIBINPUT_LED_NUM_LOCK;
    env["LIBINPUT_LED_CAPS_LOCK"] = LIBINPUT_LED_CAPS_LOCK;
    env["LIBINPUT_LED_SCROLL_LOCK"] = LIBINPUT_LED_SCROLL_LOCK;

    // enum libinput_pointer_axis
    env["LIBINPUT_POINTER_AXIS_SCROLL_VERTICAL"] = LIBINPUT_POINTER_AXIS_SCROLL_VERTICAL;
    env["LIBINPUT_POINTER_AXIS_SCROLL_HORIZONTAL"] = LIBINPUT_POINTER_AXIS_SCROLL_HORIZONTAL;

    env["libinput_device_ref"] = libinput_device_ref;
    env["libinput_device_unref"] = libinput_device_unref;
    env["libinput_device_set_user_data"] = libinput_device_set_user_data;
    env["libinput_device_get_user_data"] = libinput_device_get_user_data;
    env["libinput_device_get_context"] = libinput_device_get_context;
    env["libinput_device_get_sysname"] = libinput_device_get_sysname;
    env["libinput_device_get_name"] = libinput_device_get_name;
    env["libinput_device_get_id_product"] = libinput_device_get_id_product;
    env["libinput_device_get_id_vendor"] = libinput_device_get_id_vendor;
    env["libinput_device_get_output_name"] = libinput_device_get_output_name;
    env["libinput_device_get_seat"] = libinput_device_get_seat;
    env["libinput_device_set_seat_logical_name"] = libinput_device_set_seat_logical_name;
    env["libinput_device_led_update"] = libinput_device_led_update;
    env["libinput_device_has_capability"] = libinput_device_has_capability;
    env["libinput_device_get_size"] = libinput_device_get_size;
    env["libinput_device_has_button"] = libinput_device_has_button;

    return 0;
}

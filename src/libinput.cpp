#include "libinput.hpp"

#include "luacxx/convert/callable.hpp"
#include "luacxx/thread.hpp"
#include "linux/input.hpp"

#include <libinput.h>

// http://wayland.freedesktop.org/libinput/doc/latest/group__event.html
// http://wayland.freedesktop.org/libinput/doc/latest/libinput_8h.html

int _libinput_device_get_size(lua_State* const state)
{
    double width, height;
    libinput_device_get_size(
        lua::get<libinput_device*>(state, 1),
        &width,
        &height
    );

    lua::push(state, width, height);
    return 2;
}

int _libinput_log_set_handler(lua_State* const state)
{
    // TODO libinput_log_set_handler
    return 0;
}

int luaopen_libinput(lua_State* const state)
{
    lua::thread env(state);

    // enum libinput_log_priority
    env["LIBINPUT_LOG_PRIORITY_ERROR "] = LIBINPUT_LOG_PRIORITY_ERROR;
    env["LIBINPUT_LOG_PRIORITY_INFO"] = LIBINPUT_LOG_PRIORITY_INFO;
    env["LIBINPUT_LOG_PRIORITY_DEBUG"] = LIBINPUT_LOG_PRIORITY_DEBUG;

    // enum libinput_device_capability
    env["LIBINPUT_DEVICE_CAP_TOUCH "] = LIBINPUT_DEVICE_CAP_TOUCH;
    env["LIBINPUT_DEVICE_CAP_POINTER"] = LIBINPUT_DEVICE_CAP_POINTER;
    env["LIBINPUT_DEVICE_CAP_KEYBOARD"] = LIBINPUT_DEVICE_CAP_KEYBOARD;

    // enum libinput_key_state
    env["LIBINPUT_KEY_STATE_PRESSED "] = LIBINPUT_KEY_STATE_PRESSED;
    env["LIBINPUT_KEY_STATE_RELEASED"] = LIBINPUT_KEY_STATE_RELEASED;

    // enum libinput_led
    env["LIBINPUT_LED_SCROLL_LOCK "] = LIBINPUT_LED_SCROLL_LOCK;
    env["LIBINPUT_LED_CAPS_LOCK"] = LIBINPUT_LED_CAPS_LOCK;
    env["LIBINPUT_LED_NUM_LOCK"] = LIBINPUT_LED_NUM_LOCK;

    // enum libinput_button_state
    env["LIBINPUT_BUTTON_STATE_PRESSED"] = LIBINPUT_BUTTON_STATE_PRESSED;
    env["LIBINPUT_BUTTON_STATE_RELEASED"] = LIBINPUT_BUTTON_STATE_RELEASED;

    // enum libinput_pointer_axis
    env["LIBINPUT_POINTER_AXIS_SCROLL_HORIZONTAL"] = LIBINPUT_POINTER_AXIS_SCROLL_HORIZONTAL;
    env["LIBINPUT_POINTER_AXIS_SCROLL_VERTICAL"] = LIBINPUT_POINTER_AXIS_SCROLL_VERTICAL;

    // enum libinput_event_type
    env["LIBINPUT_EVENT_TOUCH_FRAME"] = LIBINPUT_EVENT_TOUCH_FRAME;
    env["LIBINPUT_EVENT_TOUCH_CANCEL"] = LIBINPUT_EVENT_TOUCH_CANCEL;
    env["LIBINPUT_EVENT_TOUCH_MOTION"] = LIBINPUT_EVENT_TOUCH_MOTION;
    env["LIBINPUT_EVENT_TOUCH_UP"] = LIBINPUT_EVENT_TOUCH_UP;
    env["LIBINPUT_EVENT_TOUCH_DOWN"] = LIBINPUT_EVENT_TOUCH_DOWN;
    env["LIBINPUT_EVENT_POINTER_AXIS"] = LIBINPUT_EVENT_POINTER_AXIS;
    env["LIBINPUT_EVENT_POINTER_BUTTON"] = LIBINPUT_EVENT_POINTER_BUTTON;
    env["LIBINPUT_EVENT_POINTER_MOTION_ABSOLUTE"] = LIBINPUT_EVENT_POINTER_MOTION_ABSOLUTE;
    env["LIBINPUT_EVENT_POINTER_MOTION"] = LIBINPUT_EVENT_POINTER_MOTION;
    env["LIBINPUT_EVENT_KEYBOARD_KEY"] = LIBINPUT_EVENT_KEYBOARD_KEY;
    env["LIBINPUT_EVENT_DEVICE_REMOVED"] = LIBINPUT_EVENT_DEVICE_REMOVED;
    env["LIBINPUT_EVENT_DEVICE_ADDED"] = LIBINPUT_EVENT_DEVICE_ADDED;
    env["LIBINPUT_EVENT_NONE"] = LIBINPUT_EVENT_NONE;

    env["libinput_event_destroy"] = libinput_event_destroy;
    env["libinput_event_get_type"] = libinput_event_get_type;
    env["libinput_event_get_context"] = libinput_event_get_context;
    env["libinput_event_get_device"] = libinput_event_get_device;
    env["libinput_event_get_pointer_event"] = libinput_event_get_pointer_event;
    env["libinput_event_get_keyboard_event"] = libinput_event_get_keyboard_event;
    env["libinput_event_get_touch_event"] = libinput_event_get_touch_event;
    env["libinput_event_get_device_notify_event"] = libinput_event_get_device_notify_event;
    env["libinput_event_device_notify_get_base_event"] = libinput_event_device_notify_get_base_event;

    env["libinput_event_keyboard_get_time"] = libinput_event_keyboard_get_time;
    env["libinput_event_keyboard_get_key"] = libinput_event_keyboard_get_key;
    env["libinput_event_keyboard_get_key_state"] = libinput_event_keyboard_get_key_state;
    env["libinput_event_keyboard_get_base_event"] = libinput_event_keyboard_get_base_event;
    env["libinput_event_keyboard_get_seat_key_count"] = libinput_event_keyboard_get_seat_key_count;

    env["libinput_event_pointer_get_time"] = libinput_event_pointer_get_time;
    env["libinput_event_pointer_get_dx"] = libinput_event_pointer_get_dx;
    env["libinput_event_pointer_get_dy"] = libinput_event_pointer_get_dy;
    env["libinput_event_pointer_get_absolute_x"] = libinput_event_pointer_get_absolute_x;
    env["libinput_event_pointer_get_absolute_y"] = libinput_event_pointer_get_absolute_y;
    env["libinput_event_pointer_get_absolute_x_transformed"] = libinput_event_pointer_get_absolute_x_transformed;
    env["libinput_event_pointer_get_absolute_y_transformed"] = libinput_event_pointer_get_absolute_y_transformed;
    env["libinput_event_pointer_get_button"] = libinput_event_pointer_get_button;
    env["libinput_event_pointer_get_button_state"] = libinput_event_pointer_get_button_state;
    env["libinput_event_pointer_get_seat_button_count"] = libinput_event_pointer_get_seat_button_count;
    env["libinput_event_pointer_get_axis"] = libinput_event_pointer_get_axis;
    env["libinput_event_pointer_get_axis_value"] = libinput_event_pointer_get_axis_value;
    env["libinput_event_pointer_get_base_event"] = libinput_event_pointer_get_base_event;

    env["libinput_event_touch_get_time"] = libinput_event_touch_get_time;
    env["libinput_event_touch_get_slot"] = libinput_event_touch_get_slot;
    env["libinput_event_touch_get_seat_slot"] = libinput_event_touch_get_seat_slot;
    env["libinput_event_touch_get_x"] = libinput_event_touch_get_x;
    env["libinput_event_touch_get_y"] = libinput_event_touch_get_y;
    env["libinput_event_touch_get_x_transformed"] = libinput_event_touch_get_x_transformed;
    env["libinput_event_touch_get_y_transformed"] = libinput_event_touch_get_y_transformed;
    env["libinput_event_touch_get_base_event"] = libinput_event_touch_get_base_event;

    env["libinput_udev_create_context"] = libinput_udev_create_context;
    env["libinput_udev_create_assign_seat"] = libinput_udev_assign_seat;

    env["libinput_path_create_context"] = libinput_path_create_context;
    env["libinput_path_add_device"] = libinput_path_add_device;
    env["libinput_path_remove_device"] = libinput_path_remove_device;

    env["libinput_get_fd"] = libinput_get_fd;
    env["libinput_dispatch"] = libinput_dispatch;
    env["libinput_get_event"] = libinput_get_event;
    env["libinput_next_event_type"] = libinput_next_event_type;
    env["libinput_get_user_data"] = libinput_get_user_data;
    env["libinput_resume"] = libinput_resume;
    env["libinput_suspend"] = libinput_suspend;
    env["libinput_ref"] = libinput_ref;
    env["libinput_unref"] = libinput_unref;

    env["libinput_log_set_priority"] = libinput_log_set_priority;
    env["libinput_log_get_priority"] = libinput_log_get_priority;
    env["libinput_log_set_handler"] = _libinput_log_set_handler;

    env["libinput_seat_ref"] = libinput_seat_ref;
    env["libinput_seat_unref"] = libinput_seat_unref;
    env["libinput_seat_set_user_data"] = libinput_seat_set_user_data;
    env["libinput_seat_get_user_data"] = libinput_seat_get_user_data;
    env["libinput_seat_get_physical_name"] = libinput_seat_get_physical_name;
    env["libinput_seat_get_logical_name"] = libinput_seat_get_logical_name;

    env["libinput_device_ref"] = libinput_device_ref;
    env["libinput_device_unref"] = libinput_device_unref;
    env["libinput_device_set_user_data"] = libinput_device_set_user_data;
    env["libinput_device_get_user_data"] = libinput_device_get_user_data;
    env["libinput_device_get_sysname"] = libinput_device_get_sysname;
    env["libinput_device_get_output_name"] = libinput_device_get_output_name;
    env["libinput_device_get_seat"] = libinput_device_get_seat;
    env["libinput_device_led_update"] = libinput_device_led_update;
    env["libinput_device_get_keys"] = libinput_device_get_keys;
    env["libinput_device_calibrate"] = libinput_device_calibrate;
    env["libinput_device_has_capability"] = libinput_device_has_capability;
    env["libinput_device_get_size"] = _libinput_device_get_size;

    return 0;
}

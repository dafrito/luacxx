#include "../libinput.hpp"
#include "../thread.hpp"

// http://wayland.freedesktop.org/libinput/doc/latest/group__base.html

int lua::libinput_group__base(lua_State* const state)
{
    lua::thread env(state);

    // enum libinput_event_type
    env["LIBINPUT_EVENT_NONE"] = LIBINPUT_EVENT_NONE;
    env["LIBINPUT_EVENT_DEVICE_ADDED"] = LIBINPUT_EVENT_DEVICE_ADDED;
    env["LIBINPUT_EVENT_DEVICE_REMOVED"] = LIBINPUT_EVENT_DEVICE_REMOVED;
    env["LIBINPUT_EVENT_KEYBOARD_KEY"] = LIBINPUT_EVENT_KEYBOARD_KEY;
    env["LIBINPUT_EVENT_POINTER_MOTION"] = LIBINPUT_EVENT_POINTER_MOTION;
    env["LIBINPUT_EVENT_POINTER_MOTION_ABSOLUTE"] = LIBINPUT_EVENT_POINTER_MOTION_ABSOLUTE;
    env["LIBINPUT_EVENT_POINTER_BUTTON"] = LIBINPUT_EVENT_POINTER_BUTTON;
    env["LIBINPUT_EVENT_POINTER_AXIS"] = LIBINPUT_EVENT_POINTER_AXIS;
    env["LIBINPUT_EVENT_TOUCH_DOWN"] = LIBINPUT_EVENT_TOUCH_DOWN;
    env["LIBINPUT_EVENT_TOUCH_UP"] = LIBINPUT_EVENT_TOUCH_UP;
    env["LIBINPUT_EVENT_TOUCH_MOTION"] = LIBINPUT_EVENT_TOUCH_MOTION;
    env["LIBINPUT_EVENT_TOUCH_CANCEL"] = LIBINPUT_EVENT_TOUCH_CANCEL;
    env["LIBINPUT_EVENT_TOUCH_FRAME"] = LIBINPUT_EVENT_TOUCH_FRAME;

    // FIXME (missing udev binding)
    // env["libinput_udev_create_context"] = libinput_udev_create_context;
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

    return 0;
}

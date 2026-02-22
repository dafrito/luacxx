#include "../libinput.hpp"
#include "../thread.hpp"

// http://wayland.freedesktop.org/libinput/doc/latest/group__event.html

int lua::libinput_group__event(lua_State* const state)
{
    lua::thread env(state);

    env["libinput_event_destroy"] = libinput_event_destroy;
    env["libinput_event_get_type"] = libinput_event_get_type;
    env["libinput_event_get_context"] = libinput_event_get_context;
    env["libinput_event_get_device"] = libinput_event_get_device;
    env["libinput_event_get_pointer_event"] = libinput_event_get_pointer_event;
    env["libinput_event_get_keyboard_event"] = libinput_event_get_keyboard_event;
    env["libinput_event_get_touch_event"] = libinput_event_get_touch_event;
    env["libinput_event_get_device_notify_event"] = libinput_event_get_device_notify_event;
    env["libinput_event_device_notify_get_base_event"] = libinput_event_device_notify_get_base_event;

    return 0;
}

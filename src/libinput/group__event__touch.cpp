#include "../libinput.hpp"
#include "../thread.hpp"

// http://wayland.freedesktop.org/libinput/doc/latest/group__event__touch.html

int lua::libinput_group__event__touch(lua_State* const state)
{
    lua::thread env(state);

    env["libinput_event_touch_get_time"] = libinput_event_touch_get_time;
    env["libinput_event_touch_get_slot"] = libinput_event_touch_get_slot;
    env["libinput_event_touch_get_seat_slot"] = libinput_event_touch_get_seat_slot;
    env["libinput_event_touch_get_x"] = libinput_event_touch_get_x;
    env["libinput_event_touch_get_y"] = libinput_event_touch_get_y;
    env["libinput_event_touch_get_x_transformed"] = libinput_event_touch_get_x_transformed;
    env["libinput_event_touch_get_y_transformed"] = libinput_event_touch_get_y_transformed;
    env["libinput_event_touch_get_base_event"] = libinput_event_touch_get_base_event;

    return 0;
}

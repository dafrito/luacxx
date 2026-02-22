#include "../libinput.hpp"
#include "../thread.hpp"

// http://wayland.freedesktop.org/libinput/doc/latest/group__event__pointer.html

int lua::libinput_group__event__pointer(lua_State* const state)
{
    lua::thread env(state);

    env["libinput_event_pointer_get_time"] = libinput_event_pointer_get_time;
    env["libinput_event_pointer_get_dx"] = libinput_event_pointer_get_dx;
    env["libinput_event_pointer_get_dy"] = libinput_event_pointer_get_dy;
    env["libinput_event_pointer_get_dx_unaccelerated"] = libinput_event_pointer_get_dx_unaccelerated;
    env["libinput_event_pointer_get_dy_unaccelerated"] = libinput_event_pointer_get_dy_unaccelerated;
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

    return 0;
}

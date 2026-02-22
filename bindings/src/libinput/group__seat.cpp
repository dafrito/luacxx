#include "../libinput.hpp"
#include "../thread.hpp"

// http://wayland.freedesktop.org/libinput/doc/latest/group__seat.html

int lua::libinput_group__seat(lua_State* const state)
{
    lua::thread env(state);

    env["libinput_seat_ref"] = libinput_seat_ref;
    env["libinput_seat_unref"] = libinput_seat_unref;
    env["libinput_seat_set_user_data"] = libinput_seat_set_user_data;
    env["libinput_seat_get_user_data"] = libinput_seat_get_user_data;
    env["libinput_seat_get_context"] = libinput_seat_get_context;
    env["libinput_seat_get_physical_name"] = libinput_seat_get_physical_name;
    env["libinput_seat_get_logical_name"] = libinput_seat_get_logical_name;

    return 0;
}

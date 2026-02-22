#include "../libinput.hpp"
#include "../thread.hpp"

// http://wayland.freedesktop.org/libinput/doc/latest/group__event__keyboard.html

int lua::libinput_group__event__keyboard(lua_State* const state)
{
    lua::thread env(state);

    env["libinput_event_keyboard_get_time"] = libinput_event_keyboard_get_time;
    env["libinput_event_keyboard_get_key"] = libinput_event_keyboard_get_key;
    env["libinput_event_keyboard_get_key_state"] = libinput_event_keyboard_get_key_state;
    env["libinput_event_keyboard_get_base_event"] = libinput_event_keyboard_get_base_event;
    env["libinput_event_keyboard_get_seat_key_count"] = libinput_event_keyboard_get_seat_key_count;

    return 0;
}

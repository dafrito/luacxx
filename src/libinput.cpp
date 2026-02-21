#include "libinput.hpp"
#include "linux/input.hpp"

#include "luacxx/convert/callable.hpp"
#include "luacxx/thread.hpp"

int luaopen_libinput(lua_State* const state)
{
    lua::thread env(state);

    lua::libinput_group__base(state);
    lua::libinput_group__config(state);
    lua::libinput_group__device(state);
    lua::libinput_group__event(state);
    lua::libinput_group__event__keyboard(state);
    lua::libinput_group__event__pointer(state);
    lua::libinput_group__event__touch(state);
    lua::libinput_group__seat(state);

    return 0;
}

#include "libevdev.hpp"

#include "convert/callable.hpp"
#include "thread.hpp"
#include "linux/input.hpp"

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

int _libevdev_new_from_fd(lua_State* const state)
{
    libevdev* dev;
    lua::push(state, libevdev_new_from_fd(
        lua::get<int>(state, 1),
        &dev
    ));
    lua::push(state, dev);
    return 2;
}

void libevdev_log_handler(libevdev_log_priority priority, void *data, const char *file, int line, const char *func, const char *format, va_list args)
{
    lua_State* const state = static_cast<lua_State*>(data);
    lua_getfield(state, LUA_REGISTRYINDEX, "libevdev_log_function");
    if (lua_type(state, -1) != LUA_TFUNCTION) {
        return;
    }

    lua::call(lua::index(state, -1),
        priority,
        file,
        line,
        func,
        format,
        args
    );
}


int _libevdev_set_log_function(lua_State* const state)
{
    lua_setfield(state, LUA_REGISTRYINDEX, "libevdev_log_function");
    libevdev_set_log_function(libevdev_log_handler, state);
    return 0;
}

int _libevdev_get_repeat(lua_State* const state)
{
    int delay, period;
    lua::push(state, libevdev_get_repeat(
        lua::get<libevdev*>(state, 1),
        &delay,
        &period
    ));
    lua::push(state, delay, period);
    return 3;
}

int luaopen_libevdev(lua_State* const state)
{
    luaL_requiref(state, "linux.input", luaopen_linux_input, false);

    lua::thread env(state);

    env["LIBEVDEV_READ_FLAG_BLOCKING "] = LIBEVDEV_READ_FLAG_BLOCKING;
    env["LIBEVDEV_READ_FLAG_FORCE_SYNC"] = LIBEVDEV_READ_FLAG_FORCE_SYNC;
    env["LIBEVDEV_READ_FLAG_NORMAL"] = LIBEVDEV_READ_FLAG_NORMAL;
    env["LIBEVDEV_READ_FLAG_SYNC"] = LIBEVDEV_READ_FLAG_SYNC;

    env["LIBEVDEV_LOG_DEBUG "] = LIBEVDEV_LOG_DEBUG;
    env["LIBEVDEV_LOG_INFO"] = LIBEVDEV_LOG_INFO;
    env["LIBEVDEV_LOG_ERROR"] = LIBEVDEV_LOG_ERROR;

    env["LIBEVDEV_UNGRAB "] = LIBEVDEV_UNGRAB;
    env["LIBEVDEV_GRAB"] = LIBEVDEV_GRAB;

    env["LIBEVDEV_READ_STATUS_SYNC "] = LIBEVDEV_READ_STATUS_SYNC;
    env["LIBEVDEV_READ_STATUS_SUCCESS"] = LIBEVDEV_READ_STATUS_SUCCESS;

    env["LIBEVDEV_LED_OFF "] = LIBEVDEV_LED_OFF;
    env["LIBEVDEV_LED_ON"] = LIBEVDEV_LED_ON;

    env["libevdev_new"] = libevdev_new;
    env["libevdev_new_from_fd"] = _libevdev_new_from_fd;
    env["libevdev_free"] = libevdev_free;
    env["libevdev_set_log_function"] = _libevdev_set_log_function;
    env["libevdev_set_log_priority"] = libevdev_set_log_priority;
    env["libevdev_get_log_priority"] = libevdev_get_log_priority;
    env["libevdev_grab"] = libevdev_grab;
    env["libevdev_set_fd"] = libevdev_set_fd;
    env["libevdev_change_fd"] = libevdev_change_fd;
    env["libevdev_get_fd"] = libevdev_get_fd;
    env["libevdev_next_event"] = libevdev_next_event;
    env["libevdev_has_event_pending"] = libevdev_has_event_pending;
    env["libevdev_get_name"] = libevdev_get_name;
    env["libevdev_set_name"] = libevdev_set_name;
    env["libevdev_get_phys"] = libevdev_get_phys;
    env["libevdev_set_phys"] = libevdev_set_phys;
    env["libevdev_get_uniq"] = libevdev_get_uniq;
    env["libevdev_set_uniq"] = libevdev_set_uniq;
    env["libevdev_get_id_product"] = libevdev_get_id_product;
    env["libevdev_set_id_product"] = libevdev_set_id_product;
    env["libevdev_get_id_vendor"] = libevdev_get_id_vendor;
    env["libevdev_set_id_vendor"] = libevdev_set_id_vendor;
    env["libevdev_get_id_bustype"] = libevdev_get_id_bustype;
    env["libevdev_set_id_bustype"] = libevdev_set_id_bustype;
    env["libevdev_get_id_version"] = libevdev_get_id_version;
    env["libevdev_set_id_version"] = libevdev_set_id_version;
    env["libevdev_get_driver_version"] = libevdev_get_driver_version;
    env["libevdev_has_property"] = libevdev_has_property;
    env["libevdev_enable_property"] = libevdev_enable_property;
    env["libevdev_has_event_type"] = libevdev_has_event_type;
    env["libevdev_has_event_code"] = libevdev_has_event_code;
    env["libevdev_get_abs_minimum"] = libevdev_get_abs_minimum;
    env["libevdev_get_abs_maximum"] = libevdev_get_abs_maximum;
    env["libevdev_get_abs_fuzz"] = libevdev_get_abs_fuzz;
    env["libevdev_get_abs_flat"] = libevdev_get_abs_flat;
    env["libevdev_get_abs_resolution"] = libevdev_get_abs_resolution;
    env["libevdev_get_abs_info"] = libevdev_get_abs_info;
    env["libevdev_get_event_value"] = libevdev_get_event_value;
    env["libevdev_set_event_value"] = libevdev_set_event_value;
    env["libevdev_fetch_event_value"] = libevdev_fetch_event_value;
    env["libevdev_get_slot_value"] = libevdev_get_slot_value;
    env["libevdev_set_slot_value"] = libevdev_set_slot_value;
    env["libevdev_fetch_slot_value"] = libevdev_fetch_slot_value;
    env["libevdev_get_num_slots"] = libevdev_get_num_slots;
    env["libevdev_get_current_slot"] = libevdev_get_current_slot;
    env["libevdev_set_abs_minimum"] = libevdev_set_abs_minimum;
    env["libevdev_set_abs_maximum"] = libevdev_set_abs_maximum;
    env["libevdev_set_abs_fuzz"] = libevdev_set_abs_fuzz;
    env["libevdev_set_abs_flat"] = libevdev_set_abs_flat;
    env["libevdev_set_abs_resolution"] = libevdev_set_abs_resolution;
    env["libevdev_set_abs_info"] = libevdev_set_abs_info;
    env["libevdev_enable_event_type"] = libevdev_enable_event_type;
    env["libevdev_disable_event_type"] = libevdev_disable_event_type;
    env["libevdev_enable_event_code"] = libevdev_enable_event_code;
    env["libevdev_disable_event_code"] = libevdev_disable_event_code;
    env["libevdev_kernel_set_abs_info"] = libevdev_kernel_set_abs_info;
    env["libevdev_kernel_set_led_value"] = libevdev_kernel_set_led_value;
    env["libevdev_kernel_set_led_values"] = libevdev_kernel_set_led_values;
    env["libevdev_set_clock_id"] = libevdev_set_clock_id;
    env["libevdev_event_is_type"] = libevdev_event_is_type;
    env["libevdev_event_is_code"] = libevdev_event_is_code;
    env["libevdev_event_type_get_name"] = libevdev_event_type_get_name;
    env["libevdev_event_code_get_name"] = libevdev_event_code_get_name;
    env["libevdev_property_get_name"] = libevdev_property_get_name;
    env["libevdev_event_type_get_max"] = libevdev_event_type_get_max;
    env["libevdev_event_type_from_name"] = libevdev_event_type_from_name;
    env["libevdev_event_type_from_name_n"] = libevdev_event_type_from_name_n;
    env["libevdev_event_code_from_name"] = libevdev_event_code_from_name;
    env["libevdev_event_code_from_name_n"] = libevdev_event_code_from_name_n;
    env["libevdev_get_repeat"] = _libevdev_get_repeat;

    return 0;
}

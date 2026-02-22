#ifndef LUACXX_LIBEVDEV_INCLUDED
#define LUACXX_LIBEVDEV_INCLUDED

#include "stack.hpp"
#include "enum.hpp"

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

#include "convert/numeric.hpp"
#include "convert/const_char_p.hpp"

LUA_METATABLE_NAMED(libevdev);
LUA_METATABLE_ENUM(libevdev_log_priority);
LUA_METATABLE_ENUM(libevdev_read_flag);
LUA_METATABLE_ENUM(libevdev_read_status);
LUA_METATABLE_ENUM(libevdev_grab_mode);
LUA_METATABLE_ENUM(libevdev_led_value);
LUA_METATABLE_NAMED(input_absinfo);
LUA_METATABLE_NAMED(input_event);

/*

=head1 NAME

libevdev

=head1 SYNOPSIS

=head1 DESCRIPTION

=head1 INSTALLING

    yum install libevdev-devel

*/

extern "C" int luaopen_libevdev(lua_State* const);

#endif // LUACXX_LIBEVDEV_INCLUDED

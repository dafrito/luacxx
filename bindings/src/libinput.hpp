#ifndef LUACXX_LIBINPUT_INCLUDED
#define LUACXX_LIBINPUT_INCLUDED

#include "stack.hpp"
#include "enum.hpp"

#include "convert/numeric.hpp"
#include "convert/callable.hpp"
#include "convert/const_char_p.hpp"
#include "convert/string.hpp"

#include <libinput.h>

/*

=head1 NAME

libinput 0.3.0 - http://www.freedesktop.org/wiki/Software/libinput/

=head1 SYNOPSIS

    require "libinput";

=head1 DESCRIPTION

This binding allows direct use of libinput, as described in:

    http://wayland.freedesktop.org/libinput/doc/latest/libinput_8h.html

=head1 LICENSE

libinput itself is licensed under the following terms:

    Copyright © 2008-2012 Kristian Høgsberg
    Copyright © 2010-2012 Intel Corporation
    Copyright © 2010-2011 Benjamin Franzke
    Copyright © 2011-2012 Collabora, Ltd.
    Copyright © 2013-2014 Jonas Ådahl
    Copyright © 2013-2014 Red Hat, Inc.

    Permission to use, copy, modify, distribute, and sell this software and its
    documentation for any purpose is hereby granted without fee, provided that
    the above copyright notice appear in all copies and that both that copyright
    notice and this permission notice appear in supporting documentation, and
    that the name of the copyright holders not be used in advertising or
    publicity pertaining to distribution of the software without specific,
    written prior permission.  The copyright holders make no representations
    about the suitability of this software for any purpose.  It is provided "as
    is" without express or implied warranty.

    THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
    INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
    EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
    DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
    OF THIS SOFTWARE.

As much as is possible, this binding uses the same license as libinput itself.

*/

LUA_METATABLE_NAMED(libinput);
LUA_METATABLE_NAMED(libinput_interface);
LUA_METATABLE_NAMED(libinput_device);
LUA_METATABLE_NAMED(libinput_event);
LUA_METATABLE_NAMED(libinput_event_device_notify);
LUA_METATABLE_NAMED(libinput_event_keyboard);
LUA_METATABLE_NAMED(libinput_event_pointer);
LUA_METATABLE_NAMED(libinput_event_touch);
LUA_METATABLE_NAMED(libinput_seat);

LUA_METATABLE_ENUM(libinput_event_type);
LUA_METATABLE_ENUM(libinput_log_priority);
LUA_METATABLE_ENUM(libinput_config_scroll_method)
LUA_METATABLE_ENUM(libinput_config_status)
LUA_METATABLE_ENUM(libinput_config_tap_state)
LUA_METATABLE_ENUM(libinput_button_state)
LUA_METATABLE_ENUM(libinput_device_capability)
LUA_METATABLE_ENUM(libinput_key_state)
LUA_METATABLE_ENUM(libinput_led)
LUA_METATABLE_ENUM(libinput_pointer_axis)

namespace lua {
    int libinput_group__base(lua_State* const state);
    int libinput_group__config(lua_State* const state);
    int libinput_group__device(lua_State* const state);
    int libinput_group__event(lua_State* const state);
    int libinput_group__event__keyboard(lua_State* const state);
    int libinput_group__event__pointer(lua_State* const state);
    int libinput_group__event__touch(lua_State* const state);
    int libinput_group__seat(lua_State* const state);
} // namespace lua

extern "C" int luaopen_libinput(lua_State* const);

#endif // LUACXX_LIBINPUT_INCLUDED

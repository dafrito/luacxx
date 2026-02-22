#ifndef luacxx_gbm_INCLUDED
#define luacxx_gbm_INCLUDED

#include "stack.hpp"
#include "enum.hpp"
#include "algorithm.hpp"
#include "convert/numeric.hpp"
#include "convert/callable.hpp"
#include "convert/const_char_p.hpp"
#include "convert/string.hpp"

#include <gbm.h>

/*

=head1 NAME

Mesa gbm 10.1.5 - http://lists.freedesktop.org/archives/mesa-dev/2011-June/008726.html

=head1 SYNOPSIS

    require "gbm"

=head1 DESCRIPTION

This binding allows direct use of Mesa's gbm (graphics buffer manager), as
described in:

    http://cgit.freedesktop.org/mesa/mesa/tree/src/gbm/main/gbm.h

=head1 LICENSE

gbm.h contains the following license:

     * Copyright © 2011 Intel Corporation
     *
     * Permission is hereby granted, free of charge, to any person obtaining a
     * copy of this software and associated documentation files (the "Software"),
     * to deal in the Software without restriction, including without limitation
     * the rights to use, copy, modify, merge, publish, distribute, sublicense,
     * and/or sell copies of the Software, and to permit persons to whom the
     * Software is furnished to do so, subject to the following conditions:
     *
     * The above copyright notice and this permission notice (including the next
     * paragraph) shall be included in all copies or substantial portions of the
     * Software.
     *
     * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
     * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
     * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
     * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
     * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
     * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
     * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
     * DEALINGS IN THE SOFTWARE.
     *
     * Authors:
     *    Benjamin Franzke <benjaminfranzke@googlemail.com>

As much as is possible, this file uses the same license as gbm itself.

*/

LUA_METATABLE_ENUM(gbm_bo_format);
LUA_METATABLE_ENUM(gbm_bo_flags);
LUA_METATABLE_NAMED(gbm_device);
LUA_METATABLE_NAMED(gbm_bo);
LUA_METATABLE_NAMED(gbm_bo_handle);

extern "C" int luaopen_gbm(lua_State* const);

#endif // luacxx_gbm_INCLUDED

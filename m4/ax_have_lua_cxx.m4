# ===========================================================================
#    http://www.gnu.org/software/autoconf-archive/ax_have_luacxx.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_HAVE_LUA_CXX
#
# DESCRIPTION
#
#   Test for Lua-cxx C++/Lua bindings.
#
#   This macro calls:
#
#     AC_SUBST(LUA_CXX_INCLUDE)
#     AC_SUBST(LUA_CXX_LIBS)
#
#   And sets:
#
#     HAVE_LUA_CXX
#
# LICENSE
#
#   Copyright (c) 2012 Aaron Faanes <dafrito@gmail.com>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

AC_DEFUN([AX_HAVE_LUA_CXX],
[
	AC_ARG_WITH([lua-cxx],
    AS_HELP_STRING([--with-lua-cxx], [use Lua-CXX Lua/C++ bindings]),
    [
      if test x"$withval" = "xno"; then
        want_luacxx="no";
      else
        want_luacxx="yes";
      fi
    ],
    [want_luacxx="yes"]
  )

  if test x"$want_luacxx" = "xyes"; then
    AC_MSG_CHECKING([for Lua-cxx])

    # Ensure we have a suitable C++ compiler
    AC_REQUIRE([AC_PROG_CC])
    AC_REQUIRE([AX_CXX_COMPILE_STDCXX_11])

    # Ensure we have Lua
    AC_REQUIRE([AX_LUA_LIBS])
    AC_REQUIRE([AX_LUA_HEADERS])

    # Ensure we have Qt
    AC_REQUIRE([AX_HAVE_QT])

    ax_luacxx_saved_CPPFLAGS="$CPPFLAGS"
    ax_luacxx_INCLUDE="$LUA_INCLUDE $QT_CXXFLAGS"
    CPPFLAGS="$CPPFLAGS $ax_luacxx_INCLUDE"
    export CPPFLAGS

    ax_luacxx_saved_LIBS="$LIBS"
    ax_luacxx_LIBS="$LUA_LIB $QT_LIBS"
    LIBS="$LIBS $ax_luacxx_LIBS"
    export LIBS

    AC_LANG_PUSH([C++])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM(
        [[@%:@include <lua-cxx/Lua.hpp>]],
        [[
          Lua lua;
          return 0;
        ]]
      )],
      ax_have_luacxx=yes,
      ax_have_luacxx=no
    )
    AC_LANG_POP([C++])

    AC_MSG_RESULT([$ax_have_luacxx])
    if test x"$ax_have_luacxx" = "xyes"; then
      AC_DEFINE(HAVE_LUA_CXX,,[define if Lua-cxx is available])
      LUA_CXX_INCLUDE="$ax_luacxx_INCLUDE"
      dnl This doesn't yet test the location of luacxx
      LUA_CXX_LIBS="$ax_luacxx_LIBS -lluacxx"
    else
      AC_MSG_ERROR([Could not find Lua-cxx])
      LUA_CXX_INCLUDE=""
      LUA_CXX_LIBS=""
    fi
    AC_SUBST(LUA_CXX_INCLUDE)
    AC_SUBST(LUA_CXX_LIBS)

    CPPFLAGS="$ax_luacxx_saved_CPPFLAGS"
    LIBS="$ax_luacxx_saved_LIBS"
  fi;
])

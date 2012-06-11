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
#   Test for Lua-CXX C++/Lua bindings.
#
#   This macro calls:
#
#     AC_SUBST(BOOST_FILESYSTEM_LIB)
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
    AC_MSG_CHECKING([for Lua-Cxx])

    # Ensure we have a suitable C++ compiler
    AC_REQUIRE([AC_PROG_CC])
    AC_REQUIRE([AX_CXX_COMPILE_STDCXX_11])

    # Ensure we have Lua
    AC_REQUIRE([AX_LUA_LIBS])
    AC_REQUIRE([AX_LUA_HEADERS])

    # Ensure we have Qt
    AC_REQUIRE([AX_HAVE_QT])

    ax_luacxx_CPPFLAGS="$CPPFLAGS"
    CPPFLAGS="$CPPFLAGS $LUA_INCLUDE $QT_CXXFLAGS"
    export CPPFLAGS

    ax_luacxx_LIBS="$LIBS"
    LIBS="$LIBS $LUA_LIB $QT_LIBS"
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

    if test x"$ax_have_luacxx" = "xyes"; then
      AC_DEFINE(HAVE_LUA_CXX,,[define if Lua-Cxx is available])
      AC_DEFINE(LUA_CXX_CPPFLAGS,,[define if Lua-Cxx is available])
    else
      AC_MSG_ERROR([Could not find Lua-Cxx])
    fi

    CPPFLAGS="$ax_luacxx_CPPFLAGS"
    LIBS="$ax_luacxx_LIBS"
  fi;
])

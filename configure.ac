# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([luacxx], [3.1], [dafrito@gmail.com], [luacxx], [http://www.dafrito.com])
AC_SUBST([PACKAGE_RELEASE], [1])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_SRCDIR([src/stack.hpp])
AC_CONFIG_HEADERS([src/config.hpp])
AC_CONFIG_MACRO_DIR([m4])

# Check for build programs
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

# Initialize libtool
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_PREREQ([2.2])
LT_INIT
AC_PROG_LIBTOOL

# Check for compiler characteristics.
AC_LANG([C++])
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T
AX_CXX_COMPILE_STDCXX_11([noext],[AM_CXXFLAGS])
AC_SUBST([AM_CXXFLAGS])

# Check for Lua itself
AC_SUBST(LUA_INCLUDE)
AC_SUBST(LUA_LIB)
if pkg-config --print-errors --exists 'lua >= 5.0'; then
    LUA_INCLUDE=`pkg-config --cflags lua`
    LUA_LIB=`pkg-config --libs lua`
else
    AC_MSG_ERROR([Lua is required to build luacxx])
fi

# Check for Boost
AX_BOOST_BASE([], [:], [:])
AX_BOOST_UNIT_TEST_FRAMEWORK

# Check for Qt
AX_HAVE_QT_CORE
AX_HAVE_QT_MOC
QT_CXXFLAGS="$QT_CXXFLAGS -fPIC"
AM_CONDITIONAL([BUILD_QT], [test x$HAVE_QT_CORE = xyes])

# Check for Gtk
AC_SUBST(GIO_CXXFLAGS)
AC_SUBST(GIO_LIB)
if pkg-config --print-errors --exists 'gobject-introspection-no-export-1.0'; then
    GIO_CXXFLAGS=`pkg-config --cflags gobject-introspection-no-export-1.0`
    GIO_LIB=`pkg-config --libs gobject-introspection-no-export-1.0`
    GIO_CXXFLAGS="$GIO_CXXFLAGS -DHAVE_GTK"
    AM_CONDITIONAL([BUILD_GTK], [true])
else
    AM_CONDITIONAL([BUILD_GTK], [false])
fi

AC_CONFIG_FILES([luacxx.m4 luacxx.pc Makefile src/Makefile src/tests/Makefile rpm.spec])
AC_OUTPUT

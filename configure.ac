# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([lua-cxx], [3.1], [dafrito@gmail.com], [lua-cxx], [http://www.dafrito.com])
AC_SUBST([PACKAGE_RELEASE], [1])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_SRCDIR([src/state.hpp])
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
    AC_MSG_ERROR([Lua is required to build lua-cxx])
fi

# Check for Boost
AX_BOOST_BASE([], [:], [:])
AX_BOOST_UNIT_TEST_FRAMEWORK

# Check for Qt
AX_HAVE_QT_CORE
AX_HAVE_QT_MOC
QT_CXXFLAGS="$QT_CXXFLAGS -fPIC"
AM_CONDITIONAL([BUILD_QT], [test x$HAVE_QT_CORE = xyes])

AC_CONFIG_FILES([lua-cxx.m4 lua-cxx.pc Makefile src/Makefile src/tests/Makefile rpm.spec])
AC_OUTPUT

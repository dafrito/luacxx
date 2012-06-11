#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([lua-cxx], [1.0], [dafrito@gmail.com])
AM_INIT_AUTOMAKE([-Wall foreign])
LT_INIT
AC_CONFIG_SRCDIR([lib/LuaStack.hpp])
AC_CONFIG_HEADERS([lib/config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_LIBTOOL

AX_HAVE_QT

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile lib/Makefile])
AC_OUTPUT
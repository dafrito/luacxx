# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([lua-cxx], [1.0], [dafrito@gmail.com], [lua-cxx], [http://www.dafrito.com])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIR([m4])

# Check for build programs
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

# Initialize libtool
AM_PROG_AR
LT_PREREQ([2.2])
LT_INIT
AC_PROG_LIBTOOL

# Check for compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Check for Boost
AX_BOOST_BASE
AX_BOOST_UNIT_TEST_FRAMEWORK

# Check for Qt
AX_HAVE_QT_CORE
AX_HAVE_QT_GUI
AX_HAVE_QT_MOC

if test x"$have_qt_core" = xno || test x"$have_qt_gui" = xno || test x"$have_qt_moc" = xno; then
    AC_MSG_ERROR([Qt is required to build lua-cxx])
fi;

AC_LANG([C++])

AC_CONFIG_FILES([lua-cxx.m4 Makefile src/Makefile tests/Makefile rpm.spec])
AC_OUTPUT

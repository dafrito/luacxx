# =head1 NAME
#
# configure.ac - Autoconf build configuration for Rainback
#
# =head1 SYNOPSIS
#
# Compile this file with autoreconf, producing a ./configure script
#
#     autoreconf -i;
#
# If this command fails, you've likely found a bug in the project.  Please look
# at the REPORTING BUGS section to report what you've found.
#
# Create a build directory (optional, but assumed here)
#
#     mkdir build;
#     cd build;
#
# Run the output of this file, creating this project's Makefiles.
#
#     ../configure --prefix=$HOME;
#
# If this command fails, you have a missing dependency.  Look at this file
# for a detailed listing of the prerequisites.
#
# =head1 BUILD CONFIGURATION FILES
#
# =head2 configure.ac
#
# This is the Autoconf file for Rainback and its underlying projects. It
# provides the configuration for how to compile Rainback itself. The language
# this file is written is likely unfamiliar unless you've worked with the
# Autotools, but the syntax is simple: it's little more than a macro language
# to write shell scripts.
#
# =head2 Makefile.am
#
# This file contains the commands to implement Makefile targets like "check"
# and "run". It also included the src/Makefile.am.
#
# This file can be updated to add new build targets (e.g. for new executables or
# for other build processes).
#
# =head2 src/Makefile.am
#
# This file contains the listing of source files for each library and executable
# produced by this project including the unit tests.
#
# This file must be updated whenever source files are added or removed from the
# project.
#
# =head1 TROUBLESHOOTING
#
# Getting configure to work is essential in building Rainback, but most
# problems stem from missing dependencies or porting issues. If this file is
# changed, you must rebuild the configure script

AC_PREREQ([2.68])
AC_INIT([rainback], [1.0], [dafrito@gmail.com], [rainback], [http://www.rainback.com])
AC_SUBST([PACKAGE_RELEASE], [1])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_SRCDIR([src/lua-cxx/stack.hpp])
AC_CONFIG_HEADERS([src/config.hpp])
AC_CONFIG_MACRO_DIR([m4])

# Check for build programs
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_PREREQ([2.2])
LT_INIT
AC_PROG_LIBTOOL

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
    AC_MSG_ERROR([Lua is required to build rainback])
fi

AC_SUBST(NCURSES_INCLUDE)
AC_SUBST(NCURSES_LIB)
if pkg-config --print-errors --exists 'ncursesw'; then
    NCURSES_INCLUDE=`pkg-config --cflags ncursesw`
    NCURSES_LIB=`pkg-config --libs ncursesw`
    AM_CONDITIONAL([BUILD_NCURSES], [true])
else
    AM_CONDITIONAL([BUILD_NCURSES], [false])
fi

AC_SUBST(NANOMSG_INCLUDE)
AC_SUBST(NANOMSG_LIB)
if pkg-config --print-errors --exists libnanomsg; then
    NANOMSG_INCLUDE=`pkg-config --cflags libnanomsg`
    NANOMSG_LIB=`pkg-config --libs libnanomsg`
    AM_CONDITIONAL([BUILD_NANOMSG], [true])
else
    AM_CONDITIONAL([BUILD_NANOMSG], [false])
fi

# Check for Boost. It's used for unit tets
AX_BOOST_BASE([], [:], [:])
AX_BOOST_UNIT_TEST_FRAMEWORK

# Check for Qt
AX_HAVE_QT_CORE
AX_HAVE_QT_MOC
AX_HAVE_QT_GUI
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

AC_CONFIG_FILES([lua-cxx.m4 rainback.pc Makefile src/Makefile src/tests/Makefile rpm.spec])
AC_OUTPUT

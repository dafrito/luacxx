AC_PREREQ([2.68])

AC_INIT([luacxx], [0.1], [dafrito@gmail.com], [luacxx], [http://www.github.com/dafrito/luacxx])
AC_SUBST([PACKAGE_RELEASE], [1])
AC_SUBST([PACKAGE_DESCRIPTION], ["C++11 bindings and modules for Lua"])

AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_SRCDIR([src/luacxx/stack.hpp])
AC_CONFIG_HEADERS([src/config.hpp])
AC_CONFIG_MACRO_DIR([m4])

m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_PREREQ([2.2])
LT_INIT
AC_PROG_LIBTOOL

# Check for build programs
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

AC_LANG([C++])
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T
AX_CXX_COMPILE_STDCXX_11([noext],[stdcxx11_CFLAGS])
AC_SUBST([stdcxx11_CFLAGS])

# Check for Boost. It's used for unit tets
AX_BOOST_BASE([], [:], [:])
AX_BOOST_UNIT_TEST_FRAMEWORK

AX_HAVE_QT_MOC

PKG_CHECK_MODULES(lua, [lua >= 5.0],
    [],
    [AC_MSG_ERROR([Lua is required to build Luacxx])]
)

luacxx_with_default=yes

AC_ARG_WITH([linux],
    [AS_HELP_STRING([--with-linux], [build linux module])],
    [],
    [with_linux=$luacxx_with_default]
)
if test x$with_linux = xyes; then
    AC_CHECK_HEADER(["linux/input.h"],
        [with_Qt5Core=yes],
        [with_Qt5Core=no]
    )
    AC_DEFINE([HAVE_linux], [1], [Defined if linux is available])
fi;
AM_CONDITIONAL([BUILD_linux], [test x$with_linux = xyes])

AC_ARG_WITH([Qt5Core],
    [AS_HELP_STRING([--with-Qt5Core], [build Qt5Core module])],
    [],
    [with_Qt5Core=$luacxx_with_default]
)
if test x$with_Qt5Core = xyes; then
    PKG_CHECK_MODULES(Qt5Core, [Qt5Core],
        [with_Qt5Core=yes],
        [with_Qt5Core=no]
    )
    AC_DEFINE([HAVE_Qt5Core], [1], [Defined if Qt5Core is available])
fi;
AM_CONDITIONAL([BUILD_Qt5Core], [test x$with_Qt5Core = xyes])

AC_ARG_WITH([Qt5Gui],
    [AS_HELP_STRING([--with-Qt5Gui], [build Qt5Gui module])],
    [],
    [with_Qt5Gui=$luacxx_with_default]
)
if test x$with_Qt5Gui = xyes; then
    PKG_CHECK_MODULES(Qt5Gui, [Qt5Gui],
        [with_Qt5Gui=yes],
        [with_Qt5Gui=no]
    )
    AC_DEFINE([HAVE_Qt5Gui], [1], [Defined if Qt5Gui is available])
fi;
AM_CONDITIONAL([BUILD_Qt5Gui], [test x$with_Qt5Gui = xyes])

AC_ARG_WITH([ncurses],
    [AS_HELP_STRING([--with-ncurses], [build ncurses module])],
    [],
    [with_ncurses=$luacxx_with_default]
)
if test x$with_ncurses = xyes; then
    PKG_CHECK_MODULES(ncurses, [ncursesw],
        [with_ncurses=yes],
        [with_ncurses=no]
    )
    AC_DEFINE([HAVE_ncurses], [1], [Defined if ncurses is available])
fi;
AM_CONDITIONAL([BUILD_ncurses], [test x$with_ncurses = xyes])

AC_ARG_WITH([libevdev],
    [AS_HELP_STRING([--with-libevdev], [build libevdev module])],
    [],
    [with_libevdev=$luacxx_with_default]
)
if test x$with_libevdev = xyes; then
    PKG_CHECK_MODULES(libevdev, [libevdev],
        [with_libevdev=yes],
        [with_libevdev=no]
    )
    AC_DEFINE([HAVE_libevdev], [1], [Defined if libevdev is available])
fi;
AM_CONDITIONAL([BUILD_libevdev], [test x$with_libevdev = xyes])

AC_ARG_WITH([libinput],
    [AS_HELP_STRING([--with-libinput], [build libinput module])],
    [],
    [with_libinput=$luacxx_with_default]
)
if test x$with_libinput = xyes; then
    PKG_CHECK_MODULES(libinput, [libinput],
        [with_libinput=yes],
        [with_libinput=no]
    )
    AC_DEFINE([HAVE_libinput], [1], [Defined if libinput is available])
fi;
AM_CONDITIONAL([BUILD_libinput], [test x$with_libinput = xyes])

AC_ARG_WITH([nanomsg],
    [AS_HELP_STRING([--with-nanomsg], [build nanomsg module])],
    [],
    [with_nanomsg=$luacxx_with_default]
)
if test x$with_nanomsg = xyes; then
    PKG_CHECK_MODULES(nanomsg, [libnanomsg],
        [with_nanomsg=yes],
        [with_nanomsg=no]
    )
    AC_DEFINE([HAVE_nanomsg], [1], [Defined if nanomsg is available])
fi;
AM_CONDITIONAL([BUILD_nanomsg], [test x$with_nanomsg = xyes])

AC_ARG_WITH([gobject-introspection],
    [AS_HELP_STRING([--with-gobject-introspection], [build gobject-introspection module])],
    [],
    [with_gobject_introspection=$luacxx_with_default]
)
if test x$with_gobject_introspection = xyes; then
    PKG_CHECK_MODULES(gobject_introspection, [gobject-introspection-no-export-1.0],
        [with_gobject_introspection=yes],
        [with_gobject_introspection=no]
    )
    AC_DEFINE([HAVE_gobject_introspection], [1], [Defined if gobject-introspection is available])
fi;
AM_CONDITIONAL([BUILD_gobject_introspection], [test x$with_gobject_introspection = xyes])

AC_CONFIG_FILES([luacxx.pc Makefile src/Makefile luacxx.spec])
AC_OUTPUT

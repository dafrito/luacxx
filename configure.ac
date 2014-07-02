AC_PREREQ([2.68])

AC_INIT([luacxx], [0.1], [dafrito@gmail.com], [luacxx], [http://www.github.com/dafrito/luacxx])
AC_SUBST([PACKAGE_RELEASE], [1])
AC_SUBST([PACKAGE_DESCRIPTION], ["Lua-based programming tool"])

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

AC_CHECK_HEADER(["linux/input.h"],
    [AM_CONDITIONAL([BUILD_linux], [true])],
    [AM_CONDITIONAL([BUILD_linux], [false])]
)

PKG_CHECK_MODULES(Qt5Core, [Qt5Core],
    [AM_CONDITIONAL([BUILD_Qt5Core], [true])],
    [AM_CONDITIONAL([BUILD_Qt5Core], [false])]
)

PKG_CHECK_MODULES(Qt5Gui, [Qt5Gui],
    [AM_CONDITIONAL([BUILD_Qt5Gui], [true])],
    [AM_CONDITIONAL([BUILD_Qt5Gui], [false])]
)

PKG_CHECK_MODULES(ncurses, [ncursesw],
    [AM_CONDITIONAL([BUILD_ncurses], [true])],
    [AM_CONDITIONAL([BUILD_ncurses], [false])]
)

PKG_CHECK_MODULES(libevdev, [libevdev],
    [AM_CONDITIONAL([BUILD_libevdev], [true])],
    [AM_CONDITIONAL([BUILD_libevdev], [false])]
)

PKG_CHECK_MODULES(libinput, [libinput],
    [AM_CONDITIONAL([BUILD_libinput], [true])],
    [AM_CONDITIONAL([BUILD_libinput], [false])]
)

PKG_CHECK_MODULES(nanomsg, [libnanomsg],
    [AM_CONDITIONAL([BUILD_nanomsg], [true])],
    [AM_CONDITIONAL([BUILD_nanomsg], [false])]
)

PKG_CHECK_MODULES(gobject_introspection, [gobject-introspection-no-export-1.0],
    [AM_CONDITIONAL([BUILD_gobject_introspection], [true])],
    [AM_CONDITIONAL([BUILD_gobject_introspection], [false])]
)

AC_CONFIG_FILES([luacxx.pc Makefile src/Makefile luacxx.spec])
AC_OUTPUT

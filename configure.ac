AC_PREREQ([2.72])

AC_INIT([luacxx],[3.0],[dafrito@gmail.com],[luacxx],[http://www.github.com/dafrito/luacxx])
AC_SUBST([PACKAGE_RELEASE], [1])
AC_SUBST([PACKAGE_DESCRIPTION], ["C++11 bindings and modules for Lua"])

AM_INIT_AUTOMAKE([-Wall foreign serial-tests subdir-objects])
AC_CONFIG_SRCDIR([src/stack.hpp])
AC_CONFIG_MACRO_DIR([m4])

m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_PREREQ([2.2])
LT_INIT
LT_INIT

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

# Check for Boost. It's used for unit tests
AX_BOOST_BASE([], [:], [:])
AX_BOOST_UNIT_TEST_FRAMEWORK

AX_HAVE_QT_MOC

PKG_CHECK_MODULES(lua, [lua >= 5.0],
    [],
    [AC_MSG_ERROR([Lua is required to build Luacxx])]
)

luacxx_with_default=no

AC_ARG_WITH([linux],
    [AS_HELP_STRING([--with-linux], [build linux module])],
    [],
    [with_linux=$luacxx_with_default]
)
if test x$with_linux = xyes; then
    AC_CHECK_HEADER(["linux/input.h"],
        [with_linux=yes],
        [with_linux=no]
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

AC_ARG_WITH([Qt5Network],
    [AS_HELP_STRING([--with-Qt5Network], [build Qt5Network module])],
    [],
    [with_Qt5Network=$luacxx_with_default]
)
if test x$with_Qt5Network = xyes; then
    PKG_CHECK_MODULES(Qt5Network, [Qt5Network],
        [with_Qt5Network=yes],
        [with_Qt5Network=no]
    )
    AC_DEFINE([HAVE_Qt5Network], [1], [Defined if Qt5Network is available])
fi;
AM_CONDITIONAL([BUILD_Qt5Network], [test x$with_Qt5Network = xyes])

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

AC_ARG_WITH([Qt5Sql],
    [AS_HELP_STRING([--with-Qt5Sql], [build Qt5Sql module])],
    [],
    [with_Qt5Sql=$luacxx_with_default]
)
if test x$with_Qt5Sql = xyes; then
    PKG_CHECK_MODULES(Qt5Sql, [Qt5Sql],
        [with_Qt5Sql=yes],
        [with_Qt5Sql=no]
    )
    AC_DEFINE([HAVE_Qt5Sql], [1], [Defined if Qt5Sql is available])
fi;
AM_CONDITIONAL([BUILD_Qt5Sql], [test x$with_Qt5Sql = xyes])

AC_ARG_WITH([Qt5Widgets],
    [AS_HELP_STRING([--with-Qt5Widgets], [build Qt5Widgets module])],
    [],
    [with_Qt5Widgets=$luacxx_with_default]
)
if test x$with_Qt5Widgets = xyes; then
    PKG_CHECK_MODULES(Qt5Widgets, [Qt5Widgets],
        [with_Qt5Widgets=yes],
        [with_Qt5Widgets=no]
    )
    AC_DEFINE([HAVE_Qt5Widgets], [1], [Defined if Qt5Widgets is available])
fi;
AM_CONDITIONAL([BUILD_Qt5Widgets], [test x$with_Qt5Widgets = xyes])

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

AC_ARG_WITH([egl],
    [AS_HELP_STRING([--with-egl], [build egl module])],
    [],
    [with_egl=$luacxx_with_default]
)
if test x$with_egl = xyes; then
    PKG_CHECK_MODULES(egl, [egl],
        [with_egl=yes],
        [with_egl=no]
    )
    AC_DEFINE([HAVE_egl], [1], [Defined if egl is available])
fi;
AM_CONDITIONAL([BUILD_egl], [test x$with_egl = xyes])

AC_ARG_WITH([gbm],
    [AS_HELP_STRING([--with-gbm], [build gbm module])],
    [],
    [with_gbm=$luacxx_with_default]
)
if test x$with_gbm = xyes; then
    PKG_CHECK_MODULES(gbm, [gbm],
        [with_gbm=yes],
        [with_gbm=no]
    )
    AC_DEFINE([HAVE_gbm], [1], [Defined if gbm is available])
fi;
AM_CONDITIONAL([BUILD_gbm], [test x$with_gbm = xyes])

AC_ARG_WITH([drm],
    [AS_HELP_STRING([--with-drm], [build drm module])],
    [],
    [with_drm=$luacxx_with_default]
)
if test x$with_drm = xyes; then
    PKG_CHECK_MODULES(drm, [libdrm],
        [with_drm=yes],
        [with_drm=no]
    )
    AC_DEFINE([HAVE_drm], [1], [Defined if drm is available])
fi;
AM_CONDITIONAL([BUILD_drm], [test x$with_drm = xyes])

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

AC_ARG_WITH([llvm],
    [AS_HELP_STRING([--with-llvm], [build modules for LLVM])],
    [],
    [with_llvm=$luacxx_with_default]
)
AC_SUBST(llvm_CFLAGS)
AC_SUBST(llvm_LIBS)
if test x$with_llvm = xyes; then
    AC_CHECK_PROG([with_llvm], [llvm-config], [yes], [no])

    llvm_CFLAGS=`llvm-config --cxxflags`
    llvm_LIBS=`llvm-config --ldflags`

    AC_DEFINE([HAVE_llvm], [1], [Defined if LLVM is available])
else
    with_llvm=no
fi;
AM_CONDITIONAL([BUILD_llvm], [test x$with_llvm = xyes])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    luacxx.spec
    src/pkg-config/luacxx.pc.head
    src/pkg-config/llvm.pc.head
    src/pkg-config/Qt5Core.pc.head
    src/pkg-config/Qt5Network.pc.head
    src/pkg-config/Qt5Gui.pc.head
    src/pkg-config/Qt5Sql.pc.head
    src/pkg-config/Qt5Widgets.pc.head
    src/pkg-config/gobject-introspection.pc.head
    src/pkg-config/ncurses.pc.head
    src/pkg-config/nanomsg.pc.head
    src/pkg-config/libevdev.pc.head
    src/pkg-config/libinput.pc.head
    src/pkg-config/egl.pc.head
    src/pkg-config/drm.pc.head
    src/pkg-config/gbm.pc.head
    src/pkg-config/linux.pc.head
])
AC_OUTPUT

AC_MSG_RESULT([
    Qt5Core                 ${with_Qt5Core}
    Qt5Network              ${with_Qt5Network}
    Qt5Sql                  ${with_Qt5Sql}
    Qt5Gui                  ${with_Qt5Gui}
    Qt5Widgets              ${with_Qt5Widgets}
    ncurses                 ${with_ncurses}
    libinput                ${with_libinput}
    libevdev                ${with_libevdev}
    nanomsg                 ${with_nanomsg}
    llvm                    ${with_llvm}
    gobject-introspection   ${with_gobject_introspection}
    egl                     ${with_egl}
    gbm                     ${with_gbm}
    drm                     ${with_drm}
])

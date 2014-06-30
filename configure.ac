changecom('DOC', 'COD')
DOC
"

=head1 NAME

configure.ac - Autoconf build configuration for Rainback

=head1 SYNOPSIS

   git clone https://github.com/dafrito/rainback.git
   cd rainback

    autoreconf -i

    mkdir build
    cd build

    ../configure --prefix=$HOME

    make -j 4

=head1 DEPENDENCIES

=head3 C++11 compiler

Rainback depends heavily on C++11 features for its operation. It would be a
large undertaking to remove the use of these new features, and not without a
significant loss in the expressiveness of the code.

Rainback has been built successfully using the following compilers:

    gcc version 4.8.3 20140624 (Red Hat 4.8.3-1) (GCC)
    clang version 3.4 (tags/RELEASE_34/final)

=head3 Lua 5.2

Rainback uses Lua as its underlying foundation. It would not be possible to
remove it without rewriting the project, though older version support could be
added.

Rainback has been built successfully using the following versions:

    Lua 5.2.2  Copyright (C) 1994-2013 Lua.org, PUC-Rio

=head1 OPTIONAL SOFTWARE

    yum install gobject-introspection-devel

=head3 libinput

    yum install mtdev-devel systemd-devel

Compile this file with autoreconf, producing a ./configure script

    autoreconf -i;

If this command fails, you've likely found a bug in the project. Please report
it, even if it's just dropping by via IRC.

Create a build directory (optional, but assumed here)

    mkdir build;
    cd build;

Run the output of this file, creating this project's Makefiles.

   ../configure --prefix=$HOME;

If this command fails, you have a missing dependency.  Look at this file
for a detailed listing of the prerequisites.

=head1 BUILD CONFIGURATION FILES

=head2 configure.ac

This is the Autoconf file for Rainback and its underlying projects. It
provides the configuration for how to compile Rainback itself. The language
this file is written is likely unfamiliar unless you have worked with the
Autotools, but the syntax is simple: it's little more than a macro language
to write shell scripts.

=head2 Makefile.am

This file contains the commands to implement Makefile targets like check
and run. It also included the src/Makefile.am.

This file can be updated to add new build targets (e.g. for new executables or
for other build processes).

=head2 src/Makefile.am

This file contains the listing of source files for each library and executable
produced by this project including the unit tests.

This file must be updated whenever source files are added or removed from the
project.

=head2 MAKE TARGETS

=head4 make run

Runs the Rainback application.

=head4 make debug

Runs the Rainback application under gdb. When you are ready to run the application,
you will need to pass the location of the demo source code, like so:

    (gdb) r ../src/demo.lua

=head4 make check

Runs Rainback's test suite.

=head4 make valgrind

Runs the Rainback application under valgrind. This is useful for debugging memory
leaks and segfaults.

=head4 make checkvalgrind

Runs Rainback's test suite under valgrind.

=head4 make lua

Runs a Lua interpreter with package.path and package.cpath set up to use this
repository's bindings and sources files.

=head4 make install

Installs Rainback executables and libraries to configure's --prefix.

For an install limited to your own home directory, ./configure --prefix=$HOME
would be sufficient. Note that pkg-config must be configured to include other
home-installed packages: on Fedora, appending the following to ~/.bashrc would
work:

    export PKG_CONFIG_PATH=$HOME/lib/pkgconfig

Followed by the build process

    ./configure --prefix=$HOME
    make -j 4
    make install

For a system-wide install on Fedora, ./configure --prefix=/usr would be
sufficient:

    ./configure --prefix=/usr
    make -j 4
    make install

If you wish to examine the files that will be installed, DESTDIR is a better
option than --prefix. DESTDIR will relocate files under a subtree without
affecting the paths used by Makefile variables. This target produces an
identical tree as what would be done without DESTDIR, but DESTDIR ensures that
the creation can take place at a safe location:

    # Same as a system-wide install
    ./configure --prefix=/usr
    make -j 4

    # ...but install to a temporary directory
    mkdir -p ~/tmp/rainback
    make install DESTDIR=$HOME/tmp/rainback

=head1 OPERATING SYSTEM SUPPORT

Rainback is designed with modern Linux in mind, in terms of the available
feature set and performance characteristics, so the best experience will be
found there. BSDs and UNIX-like operating systems should work, though I've
not yet done so. Windows is not currently supported, though I've built ancient
versions of Rainback using MinGW and Qt.

=head2 OSes that can build Rainback without needing manually installed dependencies

Rainback has been built using the following operating systems:

    Fedora 20 (Linux 3.14.8-200.fc20.x86_64 #1 SMP Mon Jun 16 21:57:53 UTC 2014 x86_64 x86_64 x86_64 GNU/Linux)

=head2 OSes that can build Rainback with manually installed dependencies

None yet known.

=head2 OSes that can build Rainback only with emulation

=head3 Microsoft Windows

I built older versions of Rainback using MinGW and Qt on Windows 7, but I
wasn't able to consistently reproduce successful builds. Even if this was
done, there's definite limitations to working in windows.

Please contact the developers on #rainback or via the mailing list if you're
looking to build on Windows. This document will be updated as the situation
stabilizes.

=cut

"
COD
changecom()

AC_PREREQ([2.68])

AC_INIT([rainback], [0.1], [dafrito@gmail.com], [rainback], [http://www.rainback.com])
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
    [AC_MSG_ERROR([Lua is required to build rainback])]
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

AC_CONFIG_FILES([src/rainback.pc Makefile src/Makefile src/rainback.spec])
AC_OUTPUT

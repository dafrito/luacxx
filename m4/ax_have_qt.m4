# ===========================================================================
#        http://www.gnu.org/software/autoconf-archive/ax_have_qt.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_HAVE_QT [--with-Qt-dir=DIR]
#
#   AX_HAVE_QT_CORE
#   AX_HAVE_QT_GUI
#   AX_HAVE_QT_NETWORK
#   AX_HAVE_QT_OPENGL
#   AX_HAVE_QT_SQL
#   AX_HAVE_QT_TEST
#   AX_HAVE_QT_XML
#   AX_HAVE_QT_MOC
#
#   The following macros are not yet implemented:
#   AX_HAVE_QT_UIC
#   AX_HAVE_QT_LRELEASE
#   AX_HAVE_QT_LUPDATE
#
# DESCRIPTION
#
#   The following shell variable (which are not output variables) are also
#   set to either "yes" or "no" (depending on which libraries were found) to
#   help you determine exactly what was found.
#
#   have_qt_core
#   have_qt_gui
#   have_qt_network
#   have_qt_opengl
#   have_qt_sql
#   have_qt_test
#   have_qt_xml
#
#   have_qt_moc
#   have_qt_uic
#   have_qt_lrelease
#   have_qt_lupdate
#
#   The following variables contain the compiler and linker flags necessary
#   to use the requested Qt modules.
#
#     AC_SUBST(QT_CXXFLAGS)
#     AC_SUBST(QT_LIBS)
#
#   The following variables contain an absolute path to the various Qt
#   executables:
#     AC_SUBST(QT_MOC)
#     AC_SUBST(QT_UIC)
#     AC_SUBST(QT_LRELEASE)
#     AC_SUBST(QT_LUPDATE)
#
#  Additionally, the following variable will contain the path to a specified
#  Qt SDK location, if one was given:
#
#     AC_SUBST(QT_DIR)
#
#   Example lines for Makefile.in:
#
#     CXXFLAGS = @QT_CXXFLAGS@
#     LIBS     = @QT_LIBS@
#     MOC      = @QT_MOC@
#
#   No common variables such as $LIBS or $CFLAGS are polluted.
#
#   Options:
#
#   --with-Qt-dir=DIR: DIR is equal to $QT_DIR if you have followed the
#   installation instructions from the SDK. Header files are in DIR/include,
#   binary utilities are in DIR/bin and the library is in DIR/lib. If =no is
#   given, then QT_DIR is not set.
#
# LICENSE
#
#   Copyright (c) 2012 Aaron Faanes   <dafrito@gmail.com>
#   Copyright (c) 2008 Bastiaan Veelo <Bastiaan@Veelo.net>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved. This file is offered as-is, without any
#   warranty.

#serial 11

AC_DEFUN([_AX_QT_BASE],
[
  AC_REQUIRE([AC_PROG_CXX])

  AC_ARG_WITH([Qt-dir],
              AS_HELP_STRING([--with-Qt-dir=DIR],
                             [DIR is equal to $QT_DIR if you have followed the
                              installation instructions of Trolltech. Header
                              files are in DIR/include, binary utilities are
                              in DIR/bin. The library is in DIR/lib, unless
                              --with-Qt-lib-dir is also set.]))
  if test x"$with_Qt_dir" = x"no"; then
    have_qt="User disabled Qt."
  else
    # "yes" is a bogus option
    if test x"$with_Qt_dir" = xyes; then
      with_Qt_dir=
    fi
    # No Qt unless we discover otherwise
    have_qt=no
  fi;

  if test -d "$with_Qt_dir"; then
    _AX_HAVE_QT_CHECK_FOR_QT_DIR([$with_Qt_dir], [QT_DIR="$with_Qt_dir"], [QT_DIR=])
  fi;

  AC_SUBST(QT_DIR)
  AC_SUBST(QT_CXXFLAGS)
  AC_SUBST(QT_LIBS)
])dnl AX_QT_BASE

AC_DEFUN([AX_HAVE_QT_CORE], [
  AC_REQUIRE([_AX_QT_BASE])
  AC_MSG_CHECKING([QtCore])
  _AX_HAVE_QT_ADD_MODULE(
    [QtCore],
    [QCoreApplication],
    [[
      int    argc;
      char **argv;
      QCoreApplication app(argc, argv);
    ]],
    , dnl CXXFLAGS
    , dnl LIBS
    [
      AC_MSG_RESULT([yes])
      AC_DEFINE([HAVE_QT_CORE],,[define if the QtCore module is available])
      have_qt_core=yes
    ], [
    AC_MSG_RESULT([no])
    have_qt_core=no
  ])
])

AC_DEFUN([AX_HAVE_QT_GUI], [
  AC_MSG_CHECKING([QtGui])
  AC_REQUIRE([AC_PATH_X])
  AC_REQUIRE([AC_PATH_XTRA])
  AC_REQUIRE([AX_HAVE_QT_CORE])
  _AX_HAVE_QT_ADD_MODULE(
    [QtGui],
    [QApplication],
    [[
      int    argc;
      char **argv;
      QApplication app(argc, argv);
    ]],
    [$X_CFLAGS],
    [$X_PRE_LIBS $X_LIBS $X_EXTRA_LIBS],
    [
      AC_MSG_RESULT([yes])
      AC_DEFINE([HAVE_QT_GUI],,[define if the QtGui module is available])
      have_qt_gui=yes
    ], [
    AC_MSG_RESULT([no])
    have_qt_gui=no
  ])
])

AC_DEFUN([AX_HAVE_QT_TEST], [
  AC_MSG_CHECKING([QtTest])
  AC_REQUIRE([AX_HAVE_QT_CORE])
  AC_REQUIRE([AX_HAVE_QT_MOC])
  _AX_HAVE_QT_ADD_MODULE(
    [QtTest],
    [QCoreApplication QTest],
    [[
      int    argc;
      char **argv;
      QCoreApplication app(argc, argv);
      QTest::qSleep(10)
    ]],
    , dnl CXXFLAGS
    , dnl LIBS
    [
      AC_MSG_RESULT([yes])
      AC_DEFINE([HAVE_QT_TEST],,[define if the QtTest module is available])
      have_qt_test=yes
    ], [
    AC_MSG_RESULT([no])
    have_qt_test=no
  ])
])

AC_DEFUN([AX_HAVE_QT_SQL], [
  AC_MSG_CHECKING([QtSql])
  AC_REQUIRE([AX_HAVE_QT_CORE])
  _AX_HAVE_QT_ADD_MODULE(
    [QtSql],
    [QCoreApplication QSqlDatabase],
    _AX_HAVE_QT_CORE_PROGRAM([QSqlDatabase]),
    , dnl CXXFLAGS
    , dnl LIBS
    [
      AC_MSG_RESULT([yes])
      AC_DEFINE([HAVE_QT_SQL],,[define if the QtSql module is available])
      have_qt_sql=yes
    ], [
    AC_MSG_RESULT([no])
    have_qt_sql=no
  ])
])

AC_DEFUN([AX_HAVE_QT_NETWORK], [
  AC_MSG_CHECKING([QtNetwork])
  AC_REQUIRE([AX_HAVE_QT_CORE])
  _AX_HAVE_QT_ADD_MODULE(
    [QtNetwork],
    [QCoreApplication QLocalSocket],
    _AX_HAVE_QT_CORE_PROGRAM([QLocalSocket]),
    , dnl CXXFLAGS
    , dnl LIBS
    [
      AC_MSG_RESULT([yes])
      AC_DEFINE([HAVE_QT_NETWORK],,[define if the QtNetwork module is available])
      have_qt_network=yes
    ], [
    AC_MSG_RESULT([no])
    have_qt_network=no
  ])
])

AC_DEFUN([AX_HAVE_QT_XML], [
  AC_MSG_CHECKING([QtXml])
  AC_REQUIRE([AX_HAVE_QT_CORE])
  _AX_HAVE_QT_ADD_MODULE(
    [QtXml],
    [QCoreApplication QXmlSimpleReader],
    _AX_HAVE_QT_CORE_PROGRAM([QXmlSimpleReader]),
    , dnl CXXFLAGS
    , dnl LIBS
    [
      AC_MSG_RESULT([yes])
      AC_DEFINE([HAVE_QT_XML],,[define if the QtXml module is available])
      have_qt_xml=yes
    ], [
    AC_MSG_RESULT([no])
      have_qt_xml=no
  ])
])

AC_DEFUN([AX_HAVE_QT_OPENGL], [
  AC_MSG_CHECKING([QtOpenGL])
  AC_REQUIRE([AC_PATH_X])
  AC_REQUIRE([AC_PATH_XTRA])
  AC_REQUIRE([AX_HAVE_OPENGL])
  AC_REQUIRE([AX_HAVE_QT_GUI])
  _AX_HAVE_QT_ADD_MODULE(
    [QtOpenGL],
    [QApplication QGLWidget],
    _AX_HAVE_QT_GUI_PROGRAM([QGLWidget]),
    [$X_CFLAGS $GL_CFLAGS],
    [$X_PRE_LIBS $X_LIBS $X_EXTRA_LIBS $GL_LIBS],
    [
      AC_DEFINE([HAVE_QT_OPENGL],,[define if the QtOpenGL module is available])
      AC_MSG_RESULT([yes])
      have_qt_opengl=yes
    ], [
    AC_MSG_RESULT([no])
    have_qt_opengl=no
  ])
])

AC_DEFUN([AX_HAVE_QT_MOC], [
  AC_REQUIRE([AX_HAVE_QT_CORE])
  QT_MOC=
  AC_PATH_PROGS([QT_MOC], [moc moc-qt4], [], [$QT_DIR/bin:$PATH])
])

AC_DEFUN([_AX_HAVE_QT_CHECK_MOC], [
  ax_qt_moc=$1

  cat >ax_test_moc.h <<EOF
#include <QObject>

class Test : public QObject
{
  Q_OBJECT

public:
  Test() {}
  ~Test() {}

public slots:
  void receive() {}

signals:
  void send();
};
EOF

  cat >ax_test_moc.cpp <<EOF
#include "ax_test_moc.h"
#include <QApplication>

int main (int argc, char **argv)
{
  QApplication app(argc, argv);
  Test t;
  QObject::connect( &t, SIGNAL(send()), &t, SLOT(receive()) );
}
EOF

  ax_try="$ax_qt_moc ax_test_moc.h -o moc_ax_test_moc.cpp >/dev/null 2>/dev/null"
  AC_TRY_EVAL(ax_try)
  rm -f ax_test_moc.h moc_ax_test_moc.cpp ax_test_moc.cpp
  if test x"$ac_status" = x0; then
    $2
    :
  else
    $3
    :
  fi;
])

AC_DEFUN([_AX_HAVE_QT_ADD_MODULE], [
           ax_qt_module=$1
   ax_qt_module_headers="$2"
  # Program body         3
  ax_qt_module_CXXFLAGS="$4"
      ax_qt_module_LIBS="$5"
  # Action if successful 6
  # Action if failed     7

  # Search for specified headers in relevant directories
  for ax_qt_header_name in $ax_qt_module_headers; do
    ax_qt_module_include_dir=
    _AX_HAVE_QT_FOR_EACH_DIR([ax_dir_root], [
      for ax_dir in $ax_dir_root $ax_dir_root/include; do
        if test -r "$ax_dir/$ax_qt_header_name"; then
          ax_qt_module_include_dir="$ax_dir"
          break;
        elif test -r "$ax_dir/$ax_qt_module/$ax_qt_header_name"; then
          _AX_HAVE_QT_INSERT([ax_qt_module_CXXFLAGS], [-I"$ax_dir"])
          ax_qt_module_include_dir="$ax_dir/$ax_qt_module"
          break;
        fi;
      done;
      if test x"$ax_qt_module_include_dir" != x; then
        _AX_HAVE_QT_INSERT([ax_qt_module_CXXFLAGS], [-I"$ax_qt_module_include_dir"])
        break;
      fi
    ])
  done;

  # Construct a prologue from the specified headers
  ax_qt_module_prologue=
  for ax_included in $ax_qt_module_headers; do
    ax_qt_module_prologue="$ax_qt_module_prologue
      #include <$ax_included>"
  done

  # Attempt to compile and link a test program using this module.

  # (1/3) Try building without any extra options
  _AX_HAVE_QT_COMPILE(
    [$ax_qt_module_prologue],
    [$3],
    ["$ax_qt_module_CXXFLAGS"],
    ["$ax_qt_module_LIBS"], [
      $6
      :
  ],[
    # (2/3) Try building with the library specified (-lmodule)
    _AX_HAVE_QT_COMPILE(
    [$ax_qt_module_prologue],
    [$3],
    [$ax_qt_module_CXXFLAGS],
    ["$ax_qt_module_LIBS -l$ax_qt_module"], [
      $6
      :
  ],[
    # (3/3) Try building using an explicit library path (-Lpath -lmodule)
    ax_found_a_good_dir=no
    _AX_HAVE_QT_FOR_EACH_DIR([ax_dir_root],[
      for ax_dir in $ax_dir_root $ax_dir_root/lib $ax_dir_root/lib64; do
        for lib_candidate in `ls $ax_dir/lib$ax_qt_module* 2>/dev/null`; do
          lib_candidate=`echo $lib_candidate | sed -re "s|^.*/lib($ax_qt_module.*)\\..*|\\1|"`
          _AX_HAVE_QT_COMPILE(
            [$ax_qt_module_prologue],
            [$3],
            [$ax_qt_module_CXXFLAGS],
            ["$ax_qt_module_LIBS -L$ax_dir -l$lib_candidate"], [
              ax_found_a_good_dir=yes
              $6
              break;
            ]
          )
        done;
        if test x"$ax_found_a_good_dir" = xyes; then
          break;
        fi
      done;
      if test x"$ax_found_a_good_dir" = xyes; then
        break;
      fi
    ])
    if test x"$ax_found_a_good_dir" != xyes; then
      # No luck adding this module
      $7
      :
    fi
    dnl End of (3/3)
  ]) dnl End of (2/3)
  ]) dnl End of (1/3)
]) dnl _AX_HAVE_QT_ADD_MODULE

AC_DEFUN([_AX_HAVE_QT_COMPILE], [
  ax_qt_compile_prologue=$1
  # program body          2
  ax_qt_compile_CXXFLAGS=$3
      ax_qt_compile_LIBS=$4
  # Action if successful  5
  # Action if failed      6

  AC_LANG_PUSH([C++])

  ax_save_CXXFLAGS="$CXXFLAGS"
      ax_save_LIBS="$LIBS"

  CXXFLAGS="$QT_CXXFLAGS $ax_qt_compile_CXXFLAGS"
      LIBS="$QT_LIBS     $ax_qt_compile_LIBS"

  AC_TRY_LINK(
    [$ax_qt_module_prologue],
    $2,
  [
    CXXFLAGS="$ax_save_CXXFLAGS"
        LIBS="$ax_save_LIBS"

    # Successfully linked our test code, so insert it into our
    # global arguments and call the client-provided code

    _AX_HAVE_QT_INSERT([QT_CXXFLAGS], [$ax_qt_compile_CXXFLAGS])
    _AX_HAVE_QT_INSERT([QT_LIBS],     [$ax_qt_compile_LIBS])

    $5
  ], [
    # Failed to link the test program, so do nothing except call
    # the client-provided code

    CXXFLAGS="$ax_save_CXXFLAGS"
        LIBS="$ax_save_LIBS"

    $6
  ])

  AC_LANG_POP([C++])
])

dnl Check if the specified directory is a traditional Qt directory, as provided
dnl by Trolltech.
dnl
dnl The first argument must be the path of the canonical Qt installation.
dnl
dnl The second and third arguments optionally specify any shell script that will be
dnl run on the success or failure, respectively, of this test.
AC_DEFUN([_AX_HAVE_QT_CHECK_FOR_QT_DIR], [
  ax_qt_dir_candidate=$1
  if (test -x $ax_qt_dir_candidate/bin/moc*) &&
     ((ls $ax_qt_dir_candidate/lib/libqt* > /dev/null 2>/dev/null) ||
      (ls $ax_qt_dir_candidate/lib64/libqt* > /dev/null 2>/dev/null) ||
      (ls $ax_qt_dir_candidate/lib/libQt* > /dev/null 2>/dev/null) ||
      (ls $ax_qt_dir_candidate/lib64/libQt* > /dev/null 2>/dev/null)); then
    :
    $2
  else
    :
    $3
  fi;
])

dnl Force Autoconf to use the specified directory as the canonical Qt installation.
dnl Where applicable, these contents will be preferred over external ones.
AC_DEFUN([_AX_HAVE_QT_USE_QT_DIR], [
  ax_qt_dir="$1"
  _AX_HAVE_QT_CHECK_FOR_QT_DIR($ax_qt_dir,,[
    AC_MSG_WARN([Specified Qt directory is not actually a Qt directory])
  ])
  have_qt=yes
  ax_qt_include_dir="$ax_qt_dir/include"
  ax_qt_bin_dir="$ax_qt_dir/bin"
  ax_qt_lib_dir="$ax_qt_dir/lib"
  if (test -d $ax_qt_dir/lib64); then
    ax_qt_lib_dir="$ax_qt_dir/lib64"
  else
    ax_qt_lib_dir="$ax_qt_dir/lib"
  fi
  # Only search for the lib if the user did not define one already
  if test x"$ax_qt_lib" = x; then
    ax_qt_lib="`ls $ax_qt_lib_dir/libqt* | sed -n 1p |
                 sed s@$ax_qt_lib_dir/lib@@ | [sed s@[.].*@@]`"
  fi
  QT_LIBS="-L$ax_qt_lib_dir -l$ax_qt_lib $X_PRE_LIBS $X_LIBS $X_EXTRA_LIBS"
])

dnl Find the legacy include directory for Qt. While this is still used for modern
dnl versions of Qt, it is preferable to include the module header directories
dnl themselves.
dnl
dnl This macro sets the following variables:
dnl   ax_qt_include_dir - the path believed to contain Qt's header files
dnl
AC_DEFUN([_AX_HAVE_QT_FIND_INCLUDE], [
  # The following header file is expected to define QT_VERSION.
  qt_direct_test_header=qglobal.h
  # Look for the header file in a standard set of common directories.
  ax_prev_ver=0
  _AX_HAVE_QT_FOR_EACH_DIR([ax_dir_root], [
    for ax_dir in $ax_dir_root $ax_dir_root/include; do
      if test -r "$ax_dir/$qt_direct_test_header"; then
        # Check if this directory contains a newer library than our
        # previous candidate.
        ax_this_ver=`sed -nre 's/^[ ]*#define[ ]+QT_VERSION[ ]+//p' \
          $ax_dir/$qt_direct_test_header`
        if expr $ax_this_ver '>' $ax_prev_ver > /dev/null; then
          ax_qt_include_dir=$ax_dir
          ax_prev_ver=$ax_this_ver
        fi
      fi
    done
  ])
])dnl _AX_HAVE_QT_FIND_INCLUDE

dnl Iterate over a set of common directories, executing specified shell script for each entry.
dnl
dnl The first argument specifies the variable name of a given directory. This name should be used
dnl in the specified shell script.
dnl
dnl The second argument consists of shell script that will be executed for each entry. If the shell
dnl script calls "break", then iteration will immediately stop.
dnl
dnl The third argument consists of any extra directories that will be iterated.
AC_DEFUN([_AX_HAVE_QT_FOR_EACH_DIR],[
  for ax_for_each_dir_root in $3 \
    "${QT_DIR}" \
    /lib64 \
    /lib \
    /usr \
    /usr/include \
    /usr/lib64 \
    /usr/lib \
    /usr/local \
    /opt \
    /mingw \
    /Developer;
  do
    for $1 in \
      "$ax_for_each_dir_root" \
      `ls -dr $ax_dir_root/qt* 2>/dev/null` \
      `ls -dr $ax_dir_root/Qt* 2>/dev/null`;
    do
      ax_continue_flag=
      $2
      # Detect if we broke out of the for-loop using this flag
      ax_continue_flag=yes
    done
    if test x"$ax_continue_flag" != xyes; then
      break;
    fi;
  done
])

dnl Add a parameter to the specified variable.
dnl
dnl The first parameter is the name of the variable that will be modified.
dnl The second parameter is the parameter that will be added. Multiple parameters
dnl are allowed.
dnl
dnl The third parameter will, if "yes", force the variable to be added to the front, rather
dnl than the back of the specified variable.
AC_DEFUN([_AX_HAVE_QT_INSERT], [
  ax_target_variable=$1
  # To be added       2
  ax_insert_to_front=$3

  # Values to insert
  ax_inserted_variable_list=

  # Ensure each value is not already present in the list
  for ax_one_inserted_value in $2; do
    ax_do_insertion=yes
    for ax_this_value in $$1; do
      if test x"$ax_this_value" = x"$ax_one_inserted_value"; then
        # Value is already present, so no need to insert it again
        ax_do_insertion=
        break
      fi
    done
    if test x"$ax_do_insertion" = xyes; then
      ax_inserted_variable_list="$ax_inserted_variable_list $ax_one_inserted_value"
    fi
  done

  # Finally, insert values into the list
  if test x"$ax_insert_to_front" = xyes; then
    eval "$ax_target_variable=\"$ax_inserted_variable_list "'$'"$ax_target_variable\""
  else
    eval "$ax_target_variable=\""'$'"$ax_target_variable $ax_inserted_variable_list\""
  fi;
])dnl _AX_HAVE_QT_INSERT

dnl Simple macro to output a non-GUI test program
AC_DEFUN([_AX_HAVE_QT_CORE_PROGRAM], [
  int argc;
  char **argv;
  QCoreApplication app(argc,argv);
  $1 instance;
])dnl _AX_HAVE_QT_CORE_PROGRAM

dnl Simple macro to output a GUI-based test program
AC_DEFUN([_AX_HAVE_QT_GUI_PROGRAM], [
  int argc;
  char ** argv;
  QApplication app(argc,argv);
  $1 instance;
])dnl _AX_HAVE_QT_GUI_PROGRAM

lib_LTLIBRARIES = libluacxx.la

libluacxx_la_CPPFLAGS = \
	-Wall \
	@stdcxx11_CFLAGS@ \
	-I$(top_srcdir) \
	@Qt5Core_CFLAGS@ -fPIC \
	@Qt5Gui_CFLAGS@ \
	@gobject_introspection_CFLAGS@ \
	@lua_CFLAGS@ \
	@ncurses_CFLAGS@ \
	@libevdev_CFLAGS@ \
	@nanomsg_CFLAGS@

libluacxx_la_LIBADD = \
	@Qt5Core_LIBS@ \
	@Qt5Gui_LIBS@ \
	@gobject_introspection_LIBS@ \
	@lua_LIBS@ \
	@ncurses_LIBS@ \
	@libevdev_LIBS@ \
	@nanomsg_LIBS@

libluacxx_la_LDFLAGS = -version-info 0:0:0 --build-id

nobase_pkginclude_HEADERS = \
	config.hpp \
	luacxx/algorithm.hpp \
	luacxx/stack.hpp \
	luacxx/error.hpp \
	luacxx/global.hpp \
	luacxx/load.hpp \
	luacxx/range.hpp \
	luacxx/reference.hpp \
	luacxx/thread.hpp \
	luacxx/type.hpp \
	luacxx/type/function.hpp \
	luacxx/type/numeric.hpp \
	luacxx/type/standard.hpp \
	luacxx/module/ModuleLoader.hpp

libluacxx_la_SOURCES = \
	luacxx/algorithm.cpp \
	luacxx/load.cpp \
	luacxx/stack.cpp \
	luacxx/thread.cpp \
	luacxx/type/standard.cpp

bin_PROGRAMS = luacxx
luacxx_CPPFLAGS = $(libluacxx_la_CPPFLAGS)
luacxx_LDADD = libluacxx.la

luacxx_SOURCES = \
	acme/luacxx.cpp

check_PROGRAMS = runtest
TESTS = $(check_PROGRAMS)

runtest_CXXFLAGS = \
	$(libluacxx_la_CPPFLAGS) \
	@BOOST_CPPFLAGS@ \
	-DBOOST_TEST_DYN_LINK \
	-DTEST_DIR=\"$(top_srcdir)/src/tests/\"

runtest_LDADD = \
	libluacxx.la \
	@BOOST_LDFLAGS@ \
	@BOOST_UNIT_TEST_FRAMEWORK_LIB@

runtest_SOURCES = \
	tests.cpp

EXTRA_DIST = \
	tests/bin/a.lua \
	tests/bin/b.lua \
	tests/anim.lua \
	tests/simple.lua \
	tests/testlib/Library.lua

if BUILD_Qt5Core

runtest_MOC_SOURCES = \
	moc_tests.cpp
nodist_runtest_SOURCES = $(runtest_MOC_SOURCES)

moc_tests.cpp: tests.hpp
	$(QT_MOC) -o $@ $<

libluacxx_la_SOURCES += \
	luacxx/module/DirectoryModuleLoader.cpp \
	Qt/QObject.cpp \
	Qt/QVariant.cpp \
	Qt/QPoint.cpp \
	Qt/QPointF.cpp \
	Qt/QSize.cpp \
	Qt/QSizeF.cpp \
	Qt/QRect.cpp \
	Qt/QRectF.cpp \
	Qt/QQuaternion.cpp \
	Qt/Qt_1.cpp \
	Qt/Qt_2.cpp \
	Qt/Qt_3.cpp \
	Qt/Qt_4.cpp \
	Qt/QCoreApplication.cpp \
	Qt/QStringList.cpp \
	Qt/QMimeData.cpp \
	Qt/QElapsedTimer.cpp \
	Qt/QEvent.cpp \
	Qt/QEventLoop.cpp \
	Qt/QEventFilter.cpp \
	Qt/QObjectSlot.cpp

nobase_pkginclude_HEADERS += \
	luacxx/module/DirectoryModuleLoader.hpp \
	Qt/QObject.hpp \
	Qt/QObjectSlot.hpp \
	Qt/QRect.hpp \
	Qt/QRectF.hpp \
	Qt/QChar.hpp \
	Qt/QString.hpp \
	Qt/QPoint.hpp \
	Qt/QPointF.hpp \
	Qt/QElapsedTimer.hpp \
	Qt/QVariant.hpp \
	Qt/QCoreApplication.hpp \
	Qt/QEvent.hpp \
	Qt/QEventLoop.hpp \
	Qt/QStringList.hpp \
	Qt/QMimeData.hpp \
	Qt/QEventFilter.hpp \
	Qt/Qt.hpp \
	Qt/QSize.hpp \
	Qt/QObservable.hpp

endif

if BUILD_Qt5Gui

libluacxx_la_SOURCES += \
	Qt/QWindow.cpp \
	Qt/QGuiApplication.cpp \
	Qt/QOpenGLContext.cpp \
	Qt/QOpenGLContextGroup.cpp \
	Qt/QOpenGLFunctions.cpp \
	Qt/QSurfaceFormat.cpp \
	Qt/QMatrix.cpp \
	Qt/QCursor.cpp \
	Qt/QClipboard.cpp \
	Qt/QDrag.cpp \
	Qt/QIcon.cpp \
	Qt/QInputMethod.cpp \
	Qt/QPalette.cpp \
	Qt/QScreen.cpp \
	Qt/QImage.cpp \
	Qt/QFont.cpp \
	Qt/QPainterPath.cpp \
	Qt/QBrush.cpp \
	Qt/QSurface.cpp \
	Qt/QGradient.cpp \
	Qt/QLinearGradient.cpp \
	Qt/QPen.cpp \
	Qt/QTransform.cpp \
	Qt/QColor.cpp \
	Qt/QPixmap.cpp \
	Qt/QBitmap.cpp \
	Qt/QPainter.cpp \
	Qt/QPaintDevice.cpp \
	Qt/QRegion.cpp \
	Qt/QVector2D.cpp \
	Qt/QVector3D.cpp \
	Qt/QVector4D.cpp \
	Qt/QBackingStore.cpp

nobase_pkginclude_HEADERS += \
	Qt/QPen.hpp \
	Qt/QBrush.hpp \
	Qt/QTransform.hpp \
	Qt/QGradient.hpp \
	Qt/QLinearGradient.hpp \
	Qt/QColor.hpp \
	Qt/QPainter.hpp \
	Qt/QImage.hpp \
	Qt/QFont.hpp \
	Qt/QPainterPath.hpp \
	Qt/QPaintDevice.hpp \
	Qt/QWindow.hpp \
	Qt/QGuiApplication.hpp \
	Qt/QBackingStore.hpp \
	Qt/QPixmap.hpp \
	Qt/QBitmap.hpp \
	Qt/QSurfaceFormat.hpp \
	Qt/QMatrix.hpp \
	Qt/QCursor.hpp \
	Qt/QClipboard.hpp \
	Qt/QDrag.hpp \
	Qt/QIcon.hpp \
	Qt/QInputMethod.hpp \
	Qt/QPalette.hpp \
	Qt/QVector2D.hpp \
	Qt/QVector3D.hpp \
	Qt/QVector4D.hpp \
	Qt/QQuaternion.hpp \
	Qt/QOpenGLContext.hpp \
	Qt/QOpenGLContextGroup.hpp \
	Qt/QOpenGLFunctions.hpp \
	Qt/QScreen.hpp \
	Qt/Qt.hpp \
	Qt/QRegion.hpp

endif

if BUILD_gobject_introspection

libluacxx_la_SOURCES += \
	Gtk/GIBaseInfo.cpp \
	Gtk/GObject.cpp \
	Gtk/GIRepository.cpp \
	gobject-introspection.cpp

nobase_pkginclude_HEADERS += \
	Gtk/GIBaseInfo.hpp \
	Gtk/GObject.hpp \
	Gtk/GIRepository.hpp \
	gobject-introspection.hpp

endif

if BUILD_ncurses

libluacxx_la_SOURCES += \
	ncurses.cpp \
	ncurses/curs_add_wch.cpp \
	ncurses/curs_add_wchstr.cpp \
	ncurses/curs_addch.cpp \
	ncurses/curs_addchstr.cpp \
	ncurses/curs_addstr.cpp \
	ncurses/curs_addwstr.cpp \
	ncurses/curs_attr.cpp \
	ncurses/curs_beep.cpp \
	ncurses/curs_bkgd.cpp \
	ncurses/curs_bkgrnd.cpp \
	ncurses/curs_border.cpp \
	ncurses/curs_border_set.cpp \
	ncurses/curs_clear.cpp \
	ncurses/curs_color.cpp \
	ncurses/curs_delch.cpp \
	ncurses/curs_deleteln.cpp \
	ncurses/curs_extend.cpp \
	ncurses/curs_get_wch.cpp \
	ncurses/curs_get_wstr.cpp \
	ncurses/curs_getcchar.cpp \
	ncurses/curs_getch.cpp \
	ncurses/curs_getstr.cpp \
	ncurses/curs_getyx.cpp \
	ncurses/curs_in_wch.cpp \
	ncurses/curs_in_wchstr.cpp \
	ncurses/curs_inch.cpp \
	ncurses/curs_inchstr.cpp \
	ncurses/curs_initscr.cpp \
	ncurses/curs_inopts.cpp \
	ncurses/curs_ins_wch.cpp \
	ncurses/curs_ins_wstr.cpp \
	ncurses/curs_insch.cpp \
	ncurses/curs_insstr.cpp \
	ncurses/curs_instr.cpp \
	ncurses/curs_inwstr.cpp \
	ncurses/curs_kernel.cpp \
	ncurses/curs_legacy.cpp \
	ncurses/curs_mouse.cpp \
	ncurses/curs_move.cpp \
	ncurses/curs_outopts.cpp \
	ncurses/curs_overlay.cpp \
	ncurses/curs_pad.cpp \
	ncurses/curs_print.cpp \
	ncurses/curs_printw.cpp \
	ncurses/curs_refresh.cpp \
	ncurses/curs_scanw.cpp \
	ncurses/curs_scr_dump.cpp \
	ncurses/curs_scroll.cpp \
	ncurses/curs_slk.cpp \
	ncurses/curs_termattrs.cpp \
	ncurses/curs_touch.cpp \
	ncurses/curs_util.cpp \
	ncurses/curs_variables.cpp \
	ncurses/curs_window.cpp \
	ncurses/default_colors.cpp \
	ncurses/define_key.cpp \
	ncurses/key_defined.cpp \
	ncurses/keybound.cpp \
	ncurses/keyok.cpp \
	ncurses/legacy_coding.cpp \
	ncurses/resizeterm.cpp \
	ncurses/wresize.cpp

nobase_pkginclude_HEADERS += \
	ncurses.hpp

endif

if BUILD_nanomsg

libluacxx_la_SOURCES += \
	nanomsg.cpp

nobase_pkginclude_HEADERS += \
	nanomsg.hpp

endif

if BUILD_libevdev

libluacxx_la_SOURCES += \
	libevdev.cpp

nobase_pkginclude_HEADERS += \
	libevdev.hpp

endif

if BUILD_libinput

libluacxx_la_SOURCES += \
	libinput.cpp

nobase_pkginclude_HEADERS += \
	libinput.hpp

endif

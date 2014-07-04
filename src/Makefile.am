pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ../luacxx.pc

lib_LTLIBRARIES = libluacxx.la

libluacxx_la_CPPFLAGS = \
	-Wall \
	@stdcxx11_CFLAGS@ \
	@gobject_introspection_CFLAGS@ \
	@Qt5Core_CFLAGS@ -fPIC\
	@lua_CFLAGS@

libluacxx_la_LIBADD = \
	@gobject_introspection_LIBS@ \
	@Qt5Core_LIBS@ \
	@lua_LIBS@

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
	luacxx/convert/numeric.cpp
	luacxx/convert/builtin.hpp
	luacxx/convert/callable.hpp
	luacxx/convert/char.hpp
	luacxx/convert/char_pointer.hpp
	luacxx/convert/numeric.hpp
	luacxx/convert/shared_ptr.hpp
	luacxx/convert/string.hpp
	luacxx/convert/void.hpp
	luacxx/module/ModuleLoader.hpp

libluacxx_la_SOURCES = \
	luacxx/algorithm.cpp \
	luacxx/load.cpp \
	luacxx/stack.cpp \
	luacxx/thread.cpp \
	luacxx/convert/numeric.cpp

bin_PROGRAMS = luacxx
luacxx_CPPFLAGS = $(libluacxx_la_CPPFLAGS)
luacxx_LDADD = libluacxx.la

luacxx_SOURCES = \
	luacxx/luacxx.cpp

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
	tests/main.cpp \
	tests/luacxx_convert_vector.cpp \
	tests/luacxx_without_conversions.cpp

if BUILD_llvm

lib_LTLIBRARIES += libluacxx-llvm.la

libluacxx_llvm_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS)

libluacxx_llvm_la_LIBADD = \
	libluacxx.la \
	@llvm_LIBS@

libluacxx_llvm_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_llvm_la_SOURCES = \
	llvm/IR/IRBuilder.cpp

nobase_pkginclude_HEADERS += \
	llvm/IR/IRBuilder.hpp

endif

if BUILD_Qt5Core

runtest_LDADD += libluacxx-Qt5Core.la

runtest_SOURCES += tests/Qt5Core.cpp

runtest_MOC_SOURCES = \
	moc_Qt5Core.cpp

nodist_runtest_SOURCES = $(runtest_MOC_SOURCES)

moc_Qt5Core.cpp: tests/Qt5Core.hpp
	$(QT_MOC) -o $@ $<

lib_LTLIBRARIES += libluacxx-Qt5Core.la

libluacxx_Qt5Core_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS)

libluacxx_Qt5Core_la_LIBADD = \
	@Qt5Core_LIBS@ \
	libluacxx.la

libluacxx_Qt5Core_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_Qt5Core_la_SOURCES = \
	luacxx/module/DirectoryModuleLoader.cpp \
	Qt5Core/QObject.cpp \
	Qt5Core/QVariant.cpp \
	Qt5Core/QStringList.cpp \
	Qt5Core/QCoreApplication.cpp \
	Qt5Core/QPoint.cpp \
	Qt5Core/QPointF.cpp \
	Qt5Core/QSize.cpp \
	Qt5Core/QSizeF.cpp \
	Qt5Core/QRect.cpp \
	Qt5Core/QRectF.cpp \
	Qt5Core/Qt_1.cpp \
	Qt5Core/Qt_2.cpp \
	Qt5Core/Qt_3.cpp \
	Qt5Core/Qt_4.cpp \
	Qt5Core/QUrl.cpp \
	Qt5Core/QMimeData.cpp \
	Qt5Core/QElapsedTimer.cpp \
	Qt5Core/QEvent.cpp \
	Qt5Core/QEventLoop.cpp \
	Qt5Core/QEventFilter.cpp \
	Qt5Core/QObjectSlot.cpp

nobase_pkginclude_HEADERS += \
	luacxx/module/DirectoryModuleLoader.hpp \
	Qt5Core/QObject.hpp \
	Qt5Core/QObjectSlot.hpp \
	Qt5Core/QRect.hpp \
	Qt5Core/QRectF.hpp \
	Qt5Core/QChar.hpp \
	Qt5Core/QString.hpp \
	Qt5Core/QPoint.hpp \
	Qt5Core/QPointF.hpp \
	Qt5Core/QUrl.hpp \
	Qt5Core/QElapsedTimer.hpp \
	Qt5Core/QVariant.hpp \
	Qt5Core/QCoreApplication.hpp \
	Qt5Core/QEvent.hpp \
	Qt5Core/QEventLoop.hpp \
	Qt5Core/QStringList.hpp \
	Qt5Core/QMimeData.hpp \
	Qt5Core/QEventFilter.hpp \
	Qt5Core/Qt.hpp \
	Qt5Core/QSize.hpp \
	Qt5Core/QObservable.hpp

endif

if BUILD_Qt5Gui

lib_LTLIBRARIES += libluacxx-Qt5Gui.la

libluacxx_Qt5Gui_la_CPPFLAGS = \
	$(libluacxx_Qt5Core_la_CPPFLAGS) \
	@Qt5Gui_CFLAGS@ -fPIC

libluacxx_Qt5Gui_la_LIBADD = \
	@Qt5Gui_LIBS@ \
	libluacxx-Qt5Core.la

libluacxx_Qt5Gui_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_Qt5Gui_la_SOURCES = \
	Qt5Gui/QQuaternion.cpp \
	Qt5Gui/QRegion.cpp \
	Qt5Gui/QVector2D.cpp \
	Qt5Gui/QVector3D.cpp \
	Qt5Gui/QVector4D.cpp \
	Qt5Gui/QWindow.cpp \
	Qt5Gui/QPen.cpp \
	Qt5Gui/QBrush.cpp \
	Qt5Gui/QResizeEvent.cpp \
	Qt5Gui/QExposeEvent.cpp \
	Qt5Gui/QGuiApplication.cpp \
	Qt5Gui/QOpenGLContext.cpp \
	Qt5Gui/QOpenGLContextGroup.cpp \
	Qt5Gui/QOpenGLFunctions.cpp \
	Qt5Gui/QSurfaceFormat.cpp \
	Qt5Gui/QMatrix.cpp \
	Qt5Gui/QCursor.cpp \
	Qt5Gui/QClipboard.cpp \
	Qt5Gui/QDrag.cpp \
	Qt5Gui/QIcon.cpp \
	Qt5Gui/QInputMethod.cpp \
	Qt5Gui/QPalette.cpp \
	Qt5Gui/QScreen.cpp \
	Qt5Gui/QImage.cpp \
	Qt5Gui/QFont.cpp \
	Qt5Gui/QPainterPath.cpp \
	Qt5Gui/QSurface.cpp \
	Qt5Gui/QGradient.cpp \
	Qt5Gui/QLinearGradient.cpp \
	Qt5Gui/QTransform.cpp \
	Qt5Gui/QColor.cpp \
	Qt5Gui/QPixmap.cpp \
	Qt5Gui/QBitmap.cpp \
	Qt5Gui/QPainter.cpp \
	Qt5Gui/QPaintDevice.cpp \
	Qt5Gui/QBackingStore.cpp

nobase_pkginclude_HEADERS += \
	Qt5Gui/QPen.hpp \
	Qt5Gui/QBrush.hpp \
	Qt5Gui/QTransform.hpp \
	Qt5Gui/QGradient.hpp \
	Qt5Gui/QLinearGradient.hpp \
	Qt5Gui/QColor.hpp \
	Qt5Gui/QPainter.hpp \
	Qt5Gui/QImage.hpp \
	Qt5Gui/QFont.hpp \
	Qt5Gui/QPainterPath.hpp \
	Qt5Gui/QPaintDevice.hpp \
	Qt5Gui/QWindow.hpp \
	Qt5Gui/QGuiApplication.hpp \
	Qt5Gui/QBackingStore.hpp \
	Qt5Gui/QPixmap.hpp \
	Qt5Gui/QBitmap.hpp \
	Qt5Gui/QSurfaceFormat.hpp \
	Qt5Gui/QMatrix.hpp \
	Qt5Gui/QCursor.hpp \
	Qt5Gui/QClipboard.hpp \
	Qt5Gui/QDrag.hpp \
	Qt5Gui/QIcon.hpp \
	Qt5Gui/QInputMethod.hpp \
	Qt5Gui/QPalette.hpp \
	Qt5Gui/QVector2D.hpp \
	Qt5Gui/QVector3D.hpp \
	Qt5Gui/QVector4D.hpp \
	Qt5Gui/QQuaternion.hpp \
	Qt5Gui/QOpenGLContext.hpp \
	Qt5Gui/QOpenGLContextGroup.hpp \
	Qt5Gui/QOpenGLFunctions.hpp \
	Qt5Gui/QScreen.hpp \
	Qt5Gui/QRegion.hpp

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

lib_LTLIBRARIES += libluacxx-ncurses.la

libluacxx_ncurses_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS) \
	@ncurses_CFLAGS@

libluacxx_ncurses_la_LIBADD = \
	@ncurses_LIBS@ \
	libluacxx.la

libluacxx_ncurses_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_ncurses_la_SOURCES = \
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

lib_LTLIBRARIES += libluacxx-nanomsg.la

libluacxx_nanomsg_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS) \
	@nanomsg_CFLAGS@

libluacxx_nanomsg_la_LIBADD = \
	@nanomsg_LIBS@ \
	libluacxx.la

libluacxx_nanomsg_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_nanomsg_la_SOURCES = \
	nanomsg.cpp

nobase_pkginclude_HEADERS += \
	nanomsg.hpp

endif

if BUILD_libevdev

lib_LTLIBRARIES += libluacxx-libevdev.la

libluacxx_libevdev_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS) \
	@libevdev_CFLAGS@

libluacxx_libevdev_la_LIBADD = \
	@libevdev_LIBS@ \
	libluacxx.la

libluacxx_libevdev_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_libevdev_la_SOURCES = \
	libevdev.cpp

nobase_pkginclude_HEADERS += \
	libevdev.hpp

endif

if BUILD_libinput

lib_LTLIBRARIES += libluacxx-libinput.la

libluacxx_libinput_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS) \
	@libinput_CFLAGS@

libluacxx_libinput_la_LIBADD = \
	@libinput_LIBS@ \
	libluacxx.la

libluacxx_libinput_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_libinput_la_SOURCES = \
	libinput.cpp

nobase_pkginclude_HEADERS += \
	libinput.hpp

endif

if BUILD_egl

lib_LTLIBRARIES += libluacxx-egl.la

libluacxx_egl_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS) \
	@egl_CFLAGS@

libluacxx_egl_la_LIBADD = \
	@egl_LIBS@ \
	libluacxx.la

libluacxx_egl_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_egl_la_SOURCES = \
	egl.cpp

nobase_pkginclude_HEADERS += \
	egl.hpp

endif

if BUILD_linux

lib_LTLIBRARIES += libluacxx-linux.la

libluacxx_linux_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS)

libluacxx_linux_la_LIBADD = \
	libluacxx.la

libluacxx_linux_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_linux_la_SOURCES = \
	linux/input.cpp

nobase_pkginclude_HEADERS += \
	linux/input.hpp

endif

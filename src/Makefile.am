lib_LTLIBRARIES = libluacxx.la

libluacxx_la_CPPFLAGS = $(QT_CXXFLAGS) $(GIO_CXXFLAGS) @LUA_INCLUDE@ @NCURSES_INCLUDE@ @NANOMSG_INCLUDE@ -I$(top_srcdir)/src
libluacxx_la_LIBADD = $(QT_LIBS) $(GIO_LIB) @LUA_LIB@ @NCURSES_LIB@ @NANOMSG_LIB@
libluacxx_la_LDFLAGS = -version-info 0:0:0 --build-id

nobase_pkginclude_HEADERS = \
	config.hpp \
	algorithm.hpp \
	stack.hpp \
	error.hpp \
	global.hpp \
	load.hpp \
	range.hpp \
	reference.hpp \
	thread.hpp \
	type.hpp \
	type/function.hpp \
	type/numeric.hpp \
	type/standard.hpp \
	module/DirectoryModuleLoader.hpp \
	module/ModuleLoader.hpp \
	ncurses.hpp \
	Qt/QObject.hpp \
	Qt/QObjectSlot.hpp \
	Qt/QRect.hpp \
	Qt/QRectF.hpp \
	Qt/QChar.hpp \
	Qt/QString.hpp \
	Qt/QPen.hpp \
	Qt/QBrush.hpp \
	Qt/QPoint.hpp \
	Qt/QPointF.hpp \
	Qt/QTransform.hpp \
	Qt/QGradient.hpp \
	Qt/QLinearGradient.hpp \
	Qt/QColor.hpp \
	Qt/QPainter.hpp \
	Qt/QImage.hpp \
	Qt/QFont.hpp \
	Qt/QPainterPath.hpp \
	Qt/QPaintDevice.hpp \
	Qt/QElapsedTimer.hpp \
	Qt/QVariant.hpp \
	Qt/QWindow.hpp \
	Qt/QCoreApplication.hpp \
	Qt/QGuiApplication.hpp \
	Qt/QBackingStore.hpp \
	Qt/QEvent.hpp \
	Qt/QEventLoop.hpp \
	Qt/QPixmap.hpp \
	Qt/QBitmap.hpp \
	Qt/QSurfaceFormat.hpp \
	Qt/QMatrix.hpp \
	Qt/QCursor.hpp \
	Qt/QStringList.hpp \
	Qt/QClipboard.hpp \
	Qt/QMimeData.hpp \
	Qt/QDrag.hpp \
	Qt/QIcon.hpp \
	Qt/QInputMethod.hpp \
	Qt/QPalette.hpp \
	Qt/QEventFilter.hpp \
	Qt/QVector2D.hpp \
	Qt/QVector3D.hpp \
	Qt/QVector4D.hpp \
	Qt/QQuaternion.hpp \
	Qt/QOpenGLContext.hpp \
	Qt/QOpenGLContextGroup.hpp \
	Qt/QOpenGLFunctions.hpp \
	Qt/QScreen.hpp \
	Qt/Qt.hpp \
	Qt/QRegion.hpp \
	Qt/QSize.hpp \
	Qt/QObservable.hpp \
	Gtk/GObject.hpp \
	Gtk/require.hpp \
	Gtk/GIBaseInfo.hpp \
	Gtk/GIRepository.hpp \
	nanomsg.hpp

libluacxx_la_SOURCES = \
	algorithm.cpp \
	load.cpp \
	stack.cpp \
	thread.cpp \
	type/standard.cpp

bin_PROGRAMS = luacxx
luacxx_CPPFLAGS = $(libluacxx_la_CPPFLAGS)
luacxx_LDADD = libluacxx.la

luacxx_SOURCES = \
	luacxx.cpp

if BUILD_QT

libluacxx_la_SOURCES += \
	module/DirectoryModuleLoader.cpp \
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
	Qt/QWindow.cpp \
	Qt/QCoreApplication.cpp \
	Qt/QGuiApplication.cpp \
	Qt/QOpenGLContext.cpp \
	Qt/QOpenGLContextGroup.cpp \
	Qt/QOpenGLFunctions.cpp \
	Qt/QSurfaceFormat.cpp \
	Qt/QMatrix.cpp \
	Qt/QCursor.cpp \
	Qt/QStringList.cpp \
	Qt/QClipboard.cpp \
	Qt/QMimeData.cpp \
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
	Qt/QElapsedTimer.cpp \
	Qt/QVector2D.cpp \
	Qt/QVector3D.cpp \
	Qt/QVector4D.cpp \
	Qt/QEvent.cpp \
	Qt/QEventLoop.cpp \
	Qt/QEventFilter.cpp \
	Qt/QBackingStore.cpp \
	Qt/QObjectSlot.cpp

endif

if BUILD_GTK

libluacxx_la_SOURCES += \
	Gtk/GIBaseInfo.cpp \
	Gtk/GObject.cpp \
	Gtk/GIRepository.cpp \
	Gtk/require.cpp

endif

if BUILD_NCURSES

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

endif

if BUILD_NANOMSG

libluacxx_la_SOURCES += \
	nanomsg.cpp

endif

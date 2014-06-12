lib_LTLIBRARIES = libluacxx.la

libluacxx_la_CPPFLAGS = $(QT_CXXFLAGS) $(GIO_CXXFLAGS) @LUA_INCLUDE@ -I$(top_srcdir)/src
libluacxx_la_LIBADD = $(QT_LIBS) $(GIO_LIB) @LUA_LIB@
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
	Gtk/GIRepository.hpp

libluacxx_la_SOURCES = \
	algorithm.cpp \
	load.cpp \
	stack.cpp \
	thread.cpp

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
	Qt/Qt.cpp \
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
	Qt/QVector3D.cpp \
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

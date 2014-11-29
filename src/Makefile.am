pkgconfigdir = $(libdir)/pkgconfig

lib_LTLIBRARIES = libluacxx.la

libluacxx_la_CPPFLAGS = \
	@stdcxx11_CFLAGS@ \
	@gobject_introspection_CFLAGS@ \
	@lua_CFLAGS@

libluacxx_la_LIBADD = \
	@gobject_introspection_LIBS@ \
	@lua_LIBS@

libluacxx_la_LDFLAGS = -version-info 0:0:0 --build-id

nobase_pkginclude_HEADERS = \
	config.hpp \
	algorithm.hpp \
	log.hpp \
	stack.hpp \
	enum.hpp \
	link.hpp \
	index.hpp \
	error.hpp \
	global.hpp \
	load.hpp \
	range.hpp \
	reference.hpp \
	thread.hpp \
	type.hpp \
	value.hpp \
	convert/callable.hpp \
	convert/char.hpp \
	convert/char_p.hpp \
	convert/const_char_p.hpp \
	convert/numeric.hpp \
	convert/shared_ptr.hpp \
	convert/string.hpp \
	convert/vector.hpp \
	convert/void.hpp \
	std/vector.hpp

libluacxx_la_SOURCES = \
	algorithm.cpp \
	log.cpp \
	error.cpp \
	reference.cpp \
	load.cpp \
	stack.cpp \
	thread.cpp \
	convert/callable.cpp \
	convert/const_char_p.cpp \
	convert/char.cpp \
	convert/numeric.cpp

pkgconfig_DATA = pkg-config/luacxx.pc

pkg-config/luacxx.pc: pkg-config/luacxx.pc.head
	cat $< >$@
	echo "Libs: -L$(libdir) -lluacxx $(libluacxx_la_LIBADD)" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_la_CPPFLAGS)" >>$@

check_PROGRAMS = \
	test_luacxx_without_conversions

test_luacxx_without_conversions_CXXFLAGS = \
	$(libluacxx_la_CPPFLAGS) \
	@BOOST_CPPFLAGS@ \
	-DBOOST_TEST_DYN_LINK \
	-DTEST_DIR=\"$(top_srcdir)/src/tests/\"

test_luacxx_without_conversions_LDADD = \
	libluacxx.la \
	@BOOST_LDFLAGS@ \
	@BOOST_UNIT_TEST_FRAMEWORK_LIB@

test_luacxx_without_conversions_SOURCES = \
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

pkgconfig_DATA += pkg-config/luacxx-llvm.pc

pkg-config/luacxx-llvm.pc: pkg-config/llvm.pc.head
	cat $< >$@
	echo "Requires: luacxx" >>$@
	echo "Libs: -L$(libdir) -lluacxx-llvm @llvm_LIBS@" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_llvm_la_CPPFLAGS)" >>$@

endif

if BUILD_Qt5Core

moc_Qt5Core.cpp: tests/Qt5Core.hpp
	$(QT_MOC) -o $@ $<

lib_LTLIBRARIES += libluacxx-Qt5Core.la

libluacxx_Qt5Core_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS) \

libluacxx_Qt5Core_la_LIBADD = \
	@Qt5Core_LIBS@ \
	libluacxx.la

# It's necessary to include these since Qt likes to have global static objects
# that are destroyed on exit. If Qt's libraries are loaded from Lua, then Lua
# will unload Qt's source code without removing the registered exit handler.
luacxx_CPPFLAGS = @Qt5Core_CFLAGS@ @Qt5Gui_CFLAGS@
luacxx_LDADD = $(libluacxx_Qt5Core_la_LIBADD)

libluacxx_Qt5Core_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_Qt5Core_la_SOURCES = \
	Qt5Core/QPoint.cpp \
	Qt5Core/QPointF.cpp \
	Qt5Core/QSize.cpp \
	Qt5Core/QSizeF.cpp \
	Qt5Core/QFlags.cpp \
	Qt5Core/QString.cpp \
	Qt5Core/QRect.cpp \
	Qt5Core/QRectF.cpp \
	Qt5Core/QLine.cpp \
	Qt5Core/QLineF.cpp \
	Qt5Core/QObject.cpp \
	Qt5Core/QMetaObject.cpp \
	Qt5Core/QMetaMethod.cpp \
	Qt5Core/QMetaEnum.cpp \
	Qt5Core/QMetaClassInfo.cpp \
	Qt5Core/QMetaProperty.cpp \
	Qt5Core/QBitArray.cpp \
	Qt5Core/QDataStream.cpp \
	Qt5Core/QVariant.cpp \
	Qt5Core/QStringList.cpp \
	Qt5Core/QByteArray.cpp \
	Qt5Core/QPair.cpp \
	Qt5Core/QLocale.cpp \
	Qt5Core/QMargins.cpp \
	Qt5Core/QMarginsF.cpp \
	Qt5Core/QEasingCurve.cpp \
	Qt5Core/QRegExp.cpp \
	Qt5Core/QModelIndex.cpp \
	Qt5Core/QPersistentModelIndex.cpp \
	Qt5Core/QModelIndexList.cpp \
	Qt5Core/QThread.cpp \
	Qt5Core/Qt_1.cpp \
	Qt5Core/Qt_2.cpp \
	Qt5Core/Qt_3.cpp \
	Qt5Core/Qt_4.cpp \
	Qt5Core/QSocketNotifier.cpp \
	Qt5Core/QAbstractEventDispatcher.cpp \
	Qt5Core/QAbstractNativeEventFilter.cpp \
	Qt5Core/QAbstractItemModel.cpp \
	Qt5Core/QAbstractTableModel.cpp \
	Qt5Core/QItemSelection.cpp \
	Qt5Core/QItemSelectionModel.cpp \
	Qt5Core/QItemSelectionRange.cpp \
	Qt5Core/QFileSystemWatcher.cpp \
	Qt5Core/QUrl.cpp \
	Qt5Core/QIODevice.cpp \
	Qt5Core/QFileDevice.cpp \
	Qt5Core/QFile.cpp \
	Qt5Core/QMimeData.cpp \
	Qt5Core/QTranslator.cpp \
	Qt5Core/QElapsedTimer.cpp \
	Qt5Core/QEvent.cpp \
	Qt5Core/QEventLoop.cpp \
	Qt5Core/QEventFilter.cpp \
	Qt5Core/QObjectSlot.cpp \
	Qt5Core/QDateTime.cpp \
	Qt5Core/QDate.cpp \
	Qt5Core/QTime.cpp \
	Qt5Core/QTimeZone.cpp \
	Qt5Core/QCoreApplication.cpp

nobase_pkginclude_HEADERS += \
	Qt5Core/Qt5Core.hpp \
	Qt5Core/QString.hpp \
	Qt5Core/QChar.hpp \
	Qt5Core/QList.hpp \
	Qt5Core/QVector.hpp \
	Qt5Core/QMap.hpp \
	Qt5Core/QEasingCurve.hpp \
	Qt5Core/QRegExp.hpp \
	Qt5Core/QMultiMap.hpp \
	Qt5Core/QObject.hpp \
	Qt5Core/QObjectSlot.hpp \
	Qt5Core/QMetaObject.hpp \
	Qt5Core/QMetaMethod.hpp \
	Qt5Core/QMetaEnum.hpp \
	Qt5Core/QMetaClassInfo.hpp \
	Qt5Core/QMetaProperty.hpp \
	Qt5Core/QBitArray.hpp \
	Qt5Core/QRect.hpp \
	Qt5Core/QRectF.hpp \
	Qt5Core/QPoint.hpp \
	Qt5Core/QPointF.hpp \
	Qt5Core/QDataStream.hpp \
	Qt5Core/QLine.hpp \
	Qt5Core/QFlags.hpp \
	Qt5Core/QLineF.hpp \
	Qt5Core/QLocale.hpp \
	Qt5Core/QPair.hpp \
	Qt5Core/QThread.hpp \
	Qt5Core/QMargins.hpp \
	Qt5Core/QMarginsF.hpp \
	Qt5Core/QModelIndex.hpp \
	Qt5Core/QPersistentModelIndex.hpp \
	Qt5Core/QModelIndexList.hpp \
	Qt5Core/QUrl.hpp \
	Qt5Core/QIODevice.hpp \
	Qt5Core/QFileDevice.hpp \
	Qt5Core/QFile.hpp \
	Qt5Core/QElapsedTimer.hpp \
	Qt5Core/QSocketNotifier.hpp \
	Qt5Core/QAbstractNativeEventFilter.hpp \
	Qt5Core/QAbstractEventDispatcher.hpp \
	Qt5Core/QTranslator.hpp \
	Qt5Core/QVariant.hpp \
	Qt5Core/QByteArray.hpp \
	Qt5Core/QCoreApplication.hpp \
	Qt5Core/QEvent.hpp \
	Qt5Core/QFileSystemWatcher.hpp \
	Qt5Core/QEventLoop.hpp \
	Qt5Core/QStringList.hpp \
	Qt5Core/QMimeData.hpp \
	Qt5Core/QEventFilter.hpp \
	Qt5Core/Qt.hpp \
	Qt5Core/QAbstractItemModel.hpp \
	Qt5Core/QAbstractTableModel.hpp \
	Qt5Core/QItemSelection.hpp \
	Qt5Core/QItemSelectionModel.hpp \
	Qt5Core/QItemSelectionRange.hpp \
	Qt5Core/QSize.hpp \
	Qt5Core/QObservable.hpp \
	Qt5Core/QDateTime.hpp \
	Qt5Core/QDate.hpp \
	Qt5Core/QTime.hpp \
	Qt5Core/QTimeZone.hpp

check_PROGRAMS += test_Qt5Core

test_Qt5Core_CXXFLAGS = \
	$(test_luacxx_CXXFLAGS) \
	$(libluacxx_Qt5Core_la_CPPFLAGS)

test_Qt5Core_LDADD = \
	$(test_luacxx_LDADD) \
	libluacxx-Qt5Core.la \
	libluacxx-Qt5Gui.la

test_Qt5Core_SOURCES = \
	tests/Qt5Core.cpp

test_Qt5Core_MOC_SOURCES = \
	moc_Qt5Core.cpp

nodist_test_Qt5Core_SOURCES = $(test_Qt5Core_MOC_SOURCES)

pkgconfig_DATA += pkg-config/luacxx-Qt5Core.pc

pkg-config/luacxx-Qt5Core.pc: pkg-config/Qt5Core.pc.head
	cat $< >$@
	echo "Requires: luacxx Qt5Core" >>$@
	echo "Libs: -L$(libdir) -lluacxx-Qt5Core" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_Qt5Core_la_CPPFLAGS)" >>$@
else
luacxx_CPPFLAGS =
luacxx_LDADD =
endif

if BUILD_Qt5Network

moc_Qt5Network.cpp: tests/Qt5Network.hpp
	$(QT_MOC) -o $@ $<

lib_LTLIBRARIES += libluacxx-Qt5Network.la

libluacxx_Qt5Network_la_CPPFLAGS = \
	$(libluacxx_Qt5Core_la_CPPFLAGS) \
	@Qt5Network_CFLAGS@

libluacxx_Qt5Network_la_LIBADD = \
	@Qt5Network_LIBS@ \
	$(libluacxx_Qt5Core_la_LIBADD)

libluacxx_Qt5Network_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_Qt5Network_la_SOURCES = \
	Qt5Network/QAbstractSocket.cpp \
	Qt5Network/QLocalSocket.cpp \
	Qt5Network/QTcpSocket.cpp \
	Qt5Network/QUdpSocket.cpp \
	Qt5Network/QHostAddress.cpp \
	Qt5Network/QNetworkAddressEntry.cpp \
	Qt5Network/QNetworkInterface.cpp \
	Qt5Network/QNetworkProxy.cpp \
	Qt5Network/QNetworkRequest.cpp \
	Qt5Network/QSslSocket.cpp \
	Qt5Network/QSslCertificate.cpp \
	Qt5Network/QSslError.cpp \
	Qt5Network/QSslKey.cpp \
	Qt5Network/QSslCipher.cpp \
	Qt5Network/QSslConfiguration.cpp \
	Qt5Network/QSslCertificateExtension.cpp

nobase_pkginclude_HEADERS += \
	Qt5Network/Qt5Network.hpp \
	Qt5Network/QAbstractSocket.hpp \
	Qt5Network/QLocalSocket.hpp \
	Qt5Network/QTcpSocket.hpp \
	Qt5Network/QUdpSocket.hpp \
	Qt5Network/QHostAddress.hpp \
	Qt5Network/QNetworkProxy.hpp \
	Qt5Network/QNetworkRequest.hpp \
	Qt5Network/QNetworkAddressEntry.hpp \
	Qt5Network/QNetworkInterface.hpp \
	Qt5Network/QSslSocket.hpp \
	Qt5Network/QSslCertificate.hpp \
	Qt5Network/QSslError.hpp \
	Qt5Network/QSslKey.hpp \
	Qt5Network/QSslCipher.hpp \
	Qt5Network/QSslConfiguration.hpp \
	Qt5Network/QSslCertificateExtension.hpp

pkgconfig_DATA += pkg-config/luacxx-Qt5Network.pc

pkg-config/luacxx-Qt5Network.pc: pkg-config/Qt5Network.pc.head
	cat $< >$@
	echo "Requires: luacxx Qt5Network" >>$@
	echo "Libs: -L$(libdir) -lluacxx-Qt5Network" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_Qt5Network_la_CPPFLAGS)" >>$@

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
	Qt5Gui/QPolygon.cpp \
	Qt5Gui/QPolygonF.cpp \
	Qt5Gui/QWindow.cpp \
	Qt5Gui/QColor.cpp \
	Qt5Gui/QPen.cpp \
	Qt5Gui/QBrush.cpp \
	Qt5Gui/QGuiApplication.cpp \
	Qt5Gui/QOpenGLContext.cpp \
	Qt5Gui/QOpenGLContextGroup.cpp \
	Qt5Gui/QOpenGLFunctions.cpp \
	Qt5Gui/QSurfaceFormat.cpp \
	Qt5Gui/QKeySequence.cpp \
	Qt5Gui/QPaintEngine.cpp \
	Qt5Gui/QPaintEngineState.cpp \
	Qt5Gui/QAbstractTextDocumentLayout.cpp \
	Qt5Gui/QTextItem.cpp \
	Qt5Gui/QTextBlock.cpp \
	Qt5Gui/QTextBlockFormat.cpp \
	Qt5Gui/QTextBlockGroup.cpp \
	Qt5Gui/QTextBlockUserData.cpp \
	Qt5Gui/QTextCharFormat.cpp \
	Qt5Gui/QTextCursor.cpp \
	Qt5Gui/QTextFormat.cpp \
	Qt5Gui/QTextFrame.cpp \
	Qt5Gui/QTextFrameFormat.cpp \
	Qt5Gui/QTextImageFormat.cpp \
	Qt5Gui/QTextLayout.cpp \
	Qt5Gui/QTextLength.cpp \
	Qt5Gui/QTextLine.cpp \
	Qt5Gui/QTextList.cpp \
	Qt5Gui/QTextListFormat.cpp \
	Qt5Gui/QTextObject.cpp \
	Qt5Gui/QTextObjectInterface.cpp \
	Qt5Gui/QTextDocument.cpp \
	Qt5Gui/QTextDocumentFragment.cpp \
	Qt5Gui/QTextTable.cpp \
	Qt5Gui/QTextTableCell.cpp \
	Qt5Gui/QTextTableCellFormat.cpp \
	Qt5Gui/QTextTableFormat.cpp \
	Qt5Gui/QMatrix.cpp \
	Qt5Gui/QResizeEvent.cpp \
	Qt5Gui/QExposeEvent.cpp \
	Qt5Gui/QCursor.cpp \
	Qt5Gui/QClipboard.cpp \
	Qt5Gui/QDrag.cpp \
	Qt5Gui/QIconEngine.cpp \
	Qt5Gui/QIcon.cpp \
	Qt5Gui/QInputMethod.cpp \
	Qt5Gui/QPalette.cpp \
	Qt5Gui/QScreen.cpp \
	Qt5Gui/QHelpEvent.cpp \
	Qt5Gui/QImage.cpp \
	Qt5Gui/QMovie.cpp \
	Qt5Gui/QPicture.cpp \
	Qt5Gui/QFont.cpp \
	Qt5Gui/QFontInfo.cpp \
	Qt5Gui/QSyntaxHighlighter.cpp \
	Qt5Gui/QPageSize.cpp \
	Qt5Gui/QPageLayout.cpp \
	Qt5Gui/QPagedPaintDevice.cpp \
	Qt5Gui/QImageIOHandler.cpp \
	Qt5Gui/QPdfWriter.cpp \
	Qt5Gui/QImageReader.cpp \
	Qt5Gui/QImageWriter.cpp \
	Qt5Gui/QFontMetrics.cpp \
	Qt5Gui/QPainterPath.cpp \
	Qt5Gui/QSurface.cpp \
	Qt5Gui/QGradient.cpp \
	Qt5Gui/QLinearGradient.cpp \
	Qt5Gui/QTransform.cpp \
	Qt5Gui/QPixmap.cpp \
	Qt5Gui/QBitmap.cpp \
	Qt5Gui/QPainter.cpp \
	Qt5Gui/QAccessible.cpp \
	Qt5Gui/QDesktopServices.cpp \
	Qt5Gui/QFontDatabase.cpp \
	Qt5Gui/QPaintDevice.cpp \
	Qt5Gui/QBackingStore.cpp \
	Qt5Gui/QTextOption.cpp

nobase_pkginclude_HEADERS += \
	Qt5Gui/Qt5Gui.hpp \
	Qt5Gui/QPen.hpp \
	Qt5Gui/QBrush.hpp \
	Qt5Gui/QTransform.hpp \
	Qt5Gui/QGradient.hpp \
	Qt5Gui/QLinearGradient.hpp \
	Qt5Gui/QColor.hpp \
	Qt5Gui/QPainter.hpp \
	Qt5Gui/QImage.hpp \
	Qt5Gui/QMovie.hpp \
	Qt5Gui/QFont.hpp \
	Qt5Gui/QFontInfo.hpp \
	Qt5Gui/QSyntaxHighlighter.hpp \
	Qt5Gui/QPageSize.hpp \
	Qt5Gui/QPageLayout.hpp \
	Qt5Gui/QPagedPaintDevice.hpp \
	Qt5Gui/QPdfWriter.hpp \
	Qt5Gui/QImageIOHandler.hpp \
	Qt5Gui/QImageReader.hpp \
	Qt5Gui/QImageWriter.hpp \
	Qt5Gui/QFontMetrics.hpp \
	Qt5Gui/QPainterPath.hpp \
	Qt5Gui/QPaintDevice.hpp \
	Qt5Gui/QWindow.hpp \
	Qt5Gui/QGuiApplication.hpp \
	Qt5Gui/QBackingStore.hpp \
	Qt5Gui/QPixmap.hpp \
	Qt5Gui/QBitmap.hpp \
	Qt5Gui/QSurfaceFormat.hpp \
	Qt5Gui/QKeySequence.hpp \
	Qt5Gui/QMatrix.hpp \
	Qt5Gui/QCursor.hpp \
	Qt5Gui/QClipboard.hpp \
	Qt5Gui/QAccessible.hpp \
	Qt5Gui/QDesktopServices.hpp \
	Qt5Gui/QFontDatabase.hpp \
	Qt5Gui/QHelpEvent.hpp \
	Qt5Gui/QPaintEngine.hpp \
	Qt5Gui/QPaintEngineState.hpp \
	Qt5Gui/QAbstractTextDocumentLayout.hpp \
	Qt5Gui/QTextItem.hpp \
	Qt5Gui/QTextBlock.hpp \
	Qt5Gui/QTextBlockFormat.hpp \
	Qt5Gui/QTextBlockGroup.hpp \
	Qt5Gui/QTextBlockUserData.hpp \
	Qt5Gui/QTextCharFormat.hpp \
	Qt5Gui/QTextCursor.hpp \
	Qt5Gui/QTextFormat.hpp \
	Qt5Gui/QTextFrame.hpp \
	Qt5Gui/QTextFrameFormat.hpp \
	Qt5Gui/QTextImageFormat.hpp \
	Qt5Gui/QTextLayout.hpp \
	Qt5Gui/QTextLength.hpp \
	Qt5Gui/QTextLine.hpp \
	Qt5Gui/QTextList.hpp \
	Qt5Gui/QTextListFormat.hpp \
	Qt5Gui/QTextObject.hpp \
	Qt5Gui/QTextObjectInterface.hpp \
	Qt5Gui/QTextDocument.hpp \
	Qt5Gui/QTextDocumentFragment.hpp \
	Qt5Gui/QTextTable.hpp \
	Qt5Gui/QTextTableCell.hpp \
	Qt5Gui/QTextTableCellFormat.hpp \
	Qt5Gui/QTextTableFormat.hpp \
	Qt5Gui/QResizeEvent.hpp \
	Qt5Gui/QExposeEvent.hpp \
	Qt5Gui/QDrag.hpp \
	Qt5Gui/QIconEngine.hpp \
	Qt5Gui/QIcon.hpp \
	Qt5Gui/QInputMethod.hpp \
	Qt5Gui/QPalette.hpp \
	Qt5Gui/QVector2D.hpp \
	Qt5Gui/QVector3D.hpp \
	Qt5Gui/QVector4D.hpp \
	Qt5Gui/QPolygon.hpp \
	Qt5Gui/QPolygonF.hpp \
	Qt5Gui/QQuaternion.hpp \
	Qt5Gui/QOpenGLContext.hpp \
	Qt5Gui/QOpenGLContextGroup.hpp \
	Qt5Gui/QOpenGLFunctions.hpp \
	Qt5Gui/QScreen.hpp \
	Qt5Gui/QRegion.hpp \
	Qt5Gui/QTextOption.hpp

test_Qt5Gui_CXXFLAGS = \
	$(test_luacxx_CXXFLAGS) \
	$(libluacxx_Qt5Gui_la_CPPFLAGS)

test_Qt5Gui_LDADD = \
	$(test_luacxx_LDADD) \
	libluacxx-Qt5Gui.la

test_Qt5Gui_SOURCES = \
	tests/Qt5Gui.cpp

test_Qt5Gui_MOC_SOURCES = \
	moc_Qt5Gui.cpp

moc_Qt5Gui.cpp: tests/Qt5Gui.hpp
	$(QT_MOC) -o $@ $<

nodist_test_Qt5Gui_SOURCES = $(test_Qt5Gui_MOC_SOURCES)

check_PROGRAMS += test_Qt5Gui

pkgconfig_DATA += pkg-config/luacxx-Qt5Gui.pc

pkg-config/luacxx-Qt5Gui.pc: pkg-config/Qt5Gui.pc.head
	cat $< >$@
	echo "Requires: luacxx Qt5Gui" >>$@
	echo "Libs: -L$(libdir) -lluacxx-Qt5Gui" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_Qt5Gui_la_CPPFLAGS)" >>$@

endif

if BUILD_Qt5Widgets

lib_LTLIBRARIES += libluacxx-Qt5Widgets.la

libluacxx_Qt5Widgets_la_CPPFLAGS = \
	$(libluacxx_Qt5Gui_la_CPPFLAGS) \
	-DQT_WIDGETS_LIB \
	@Qt5Widgets_CFLAGS@

libluacxx_Qt5Widgets_la_LIBADD = \
	@Qt5Widgets_LIBS@ \
	libluacxx-Qt5Gui.la

libluacxx_Qt5Widgets_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_Qt5Widgets_la_SOURCES = \
	Qt5Widgets/QAbstractScrollArea.cpp \
	Qt5Widgets/QAbstractItemView.cpp \
	Qt5Widgets/QAbstractItemDelegate.cpp \
	Qt5Widgets/QAction.cpp \
	Qt5Widgets/QAbstractSlider.cpp \
	Qt5Widgets/QActionGroup.cpp \
	Qt5Widgets/QCompleter.cpp \
	Qt5Widgets/QDockWidget.cpp \
	Qt5Widgets/QFrame.cpp \
	Qt5Widgets/QGraphicsEffect.cpp \
	Qt5Widgets/QGraphicsItem.cpp \
	Qt5Widgets/QGraphicsLayout.cpp \
	Qt5Widgets/QGraphicsLayoutItem.cpp \
	Qt5Widgets/QGraphicsObject.cpp \
	Qt5Widgets/QGraphicsProxyWidget.cpp \
	Qt5Widgets/QGraphicsScene.cpp \
	Qt5Widgets/QGraphicsView.cpp \
	Qt5Widgets/QGraphicsWidget.cpp \
	Qt5Widgets/QGraphicsItemGroup.cpp \
	Qt5Widgets/QGraphicsTransform.cpp \
	Qt5Widgets/QStyleOption.cpp \
	Qt5Widgets/QStyleOptionGraphicsItem.cpp \
	Qt5Widgets/QStyleOptionViewItem.cpp \
	Qt5Widgets/QItemEditorFactory.cpp \
	Qt5Widgets/QItemEditorCreatorBase.cpp \
	Qt5Widgets/QScrollBar.cpp \
	Qt5Widgets/QItemDelegate.cpp \
	Qt5Widgets/QLabel.cpp \
	Qt5Widgets/QLayout.cpp \
	Qt5Widgets/QLayoutItem.cpp \
	Qt5Widgets/QValidator.cpp \
	Qt5Widgets/QSpacerItem.cpp \
	Qt5Widgets/QLineEdit.cpp \
	Qt5Widgets/QMainWindow.cpp \
	Qt5Widgets/QMenu.cpp \
	Qt5Widgets/QMenuBar.cpp \
	Qt5Widgets/QSizePolicy.cpp \
	Qt5Widgets/QStatusBar.cpp \
	Qt5Widgets/QStyle.cpp \
	Qt5Widgets/QTabBar.cpp \
	Qt5Widgets/QTabWidget.cpp \
	Qt5Widgets/QAbstractButton.cpp \
	Qt5Widgets/QPushButton.cpp \
	Qt5Widgets/QTextEdit.cpp \
	Qt5Widgets/QApplication.cpp \
	Qt5Widgets/QWidget.cpp

nobase_pkginclude_HEADERS += \
	Qt5Widgets/Qt5Widgets.hpp \
	Qt5Widgets/QAbstractSlider.hpp \
	Qt5Widgets/QAbstractScrollArea.hpp \
	Qt5Widgets/QAbstractItemView.hpp \
	Qt5Widgets/QAbstractItemDelegate.hpp \
	Qt5Widgets/QAction.hpp \
	Qt5Widgets/QActionGroup.hpp \
	Qt5Widgets/QApplication.hpp \
	Qt5Widgets/QCompleter.hpp \
	Qt5Widgets/QDockWidget.hpp \
	Qt5Widgets/QFrame.hpp \
	Qt5Widgets/QItemDelegate.hpp \
	Qt5Widgets/QGraphicsEffect.hpp \
	Qt5Widgets/QGraphicsItem.hpp \
	Qt5Widgets/QGraphicsLayout.hpp \
	Qt5Widgets/QGraphicsLayoutItem.hpp \
	Qt5Widgets/QGraphicsObject.hpp \
	Qt5Widgets/QGraphicsProxyWidget.hpp \
	Qt5Widgets/QGraphicsScene.hpp \
	Qt5Widgets/QGraphicsView.hpp \
	Qt5Widgets/QGraphicsWidget.hpp \
	Qt5Widgets/QGraphicsItemGroup.hpp \
	Qt5Widgets/QGraphicsTransform.hpp \
	Qt5Widgets/QStyleOption.hpp \
	Qt5Widgets/QStyleOptionGraphicsItem.hpp \
	Qt5Widgets/QStyleOptionViewItem.hpp \
	Qt5Widgets/QItemEditorFactory.hpp \
	Qt5Widgets/QItemEditorCreatorBase.hpp \
	Qt5Widgets/QScrollBar.hpp \
	Qt5Widgets/QLabel.hpp \
	Qt5Widgets/QLayout.hpp \
	Qt5Widgets/QLayoutItem.hpp \
	Qt5Widgets/QSpacerItem.hpp \
	Qt5Widgets/QLineEdit.hpp \
	Qt5Widgets/QMainWindow.hpp \
	Qt5Widgets/QMenu.hpp \
	Qt5Widgets/QMenuBar.hpp \
	Qt5Widgets/QValidator.hpp \
	Qt5Widgets/QSizePolicy.hpp \
	Qt5Widgets/QStatusBar.hpp \
	Qt5Widgets/QStyle.hpp \
	Qt5Widgets/QTabBar.hpp \
	Qt5Widgets/QTabWidget.hpp \
	Qt5Widgets/QTextEdit.hpp \
	Qt5Widgets/QAbstractButton.hpp \
	Qt5Widgets/QPushButton.hpp \
	Qt5Widgets/QWidget.hpp

test_Qt5Widgets_CXXFLAGS = \
	$(test_luacxx_CXXFLAGS) \
	$(libluacxx_Qt5Widgets_la_CPPFLAGS)

test_Qt5Widgets_LDADD = \
	$(test_luacxx_LDADD) \
	libluacxx-Qt5Gui.la \
	libluacxx-Qt5Widgets.la

test_Qt5Widgets_SOURCES = \
	tests/Qt5Widgets.cpp

test_Qt5Widgets_MOC_SOURCES = \
	moc_Qt5Widgets.cpp

moc_Qt5Widgets.cpp: tests/Qt5Widgets.hpp
	$(QT_MOC) -o $@ $<

nodist_test_Qt5Widgets_SOURCES = $(test_Qt5Widgets_MOC_SOURCES)

check_PROGRAMS += test_Qt5Widgets

pkgconfig_DATA += pkg-config/luacxx-Qt5Widgets.pc

pkg-config/luacxx-Qt5Widgets.pc: pkg-config/Qt5Widgets.pc.head
	cat $< >$@
	echo "Requires: luacxx Qt5Widgets" >>$@
	echo "Libs: -L$(libdir) -lluacxx-Qt5Widgets" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_Qt5Widgets_la_CPPFLAGS)" >>$@

endif

if BUILD_Qt5Sql

lib_LTLIBRARIES += libluacxx-Qt5Sql.la

libluacxx_Qt5Sql_la_CPPFLAGS = \
	$(libluacxx_Qt5Widgets_la_CPPFLAGS) \
	@Qt5Sql_CFLAGS@

libluacxx_Qt5Sql_la_LIBADD = \
	@Qt5Sql_LIBS@ \
	$(libluacxx_Qt5Widgets_la_LIBADD) \
	libluacxx-Qt5Widgets.la

libluacxx_Qt5Sql_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_Qt5Sql_la_SOURCES = \
	Qt5Sql/QSql.cpp \
	Qt5Sql/QSqlDatabase.cpp \
	Qt5Sql/QSqlDriver.cpp \
	Qt5Sql/QSqlDriverCreator.cpp \
	Qt5Sql/QSqlDriverCreatorBase.cpp \
	Qt5Sql/QSqlDriverPlugin.cpp \
	Qt5Sql/QSqlError.cpp \
	Qt5Sql/QSqlField.cpp \
	Qt5Sql/QSqlIndex.cpp \
	Qt5Sql/QSqlQuery.cpp \
	Qt5Sql/QSqlQueryModel.cpp \
	Qt5Sql/QSqlRecord.cpp \
	Qt5Sql/QSqlRelation.cpp \
	Qt5Sql/QSqlRelationalDelegate.cpp \
	Qt5Sql/QSqlRelationalTableModel.cpp \
	Qt5Sql/QSqlResult.cpp \
	Qt5Sql/QSqlTableModel.cpp

nobase_pkginclude_HEADERS += \
	Qt5Sql/QSql.hpp \
	Qt5Sql/QSqlDatabase.hpp \
	Qt5Sql/QSqlDriver.hpp \
	Qt5Sql/QSqlDriverCreator.hpp \
	Qt5Sql/QSqlDriverCreatorBase.hpp \
	Qt5Sql/QSqlDriverPlugin.hpp \
	Qt5Sql/QSqlError.hpp \
	Qt5Sql/QSqlField.hpp \
	Qt5Sql/QSqlIndex.hpp \
	Qt5Sql/QSqlQuery.hpp \
	Qt5Sql/QSqlQueryModel.hpp \
	Qt5Sql/QSqlRecord.hpp \
	Qt5Sql/QSqlRelation.hpp \
	Qt5Sql/QSqlRelationalDelegate.hpp \
	Qt5Sql/QSqlRelationalTableModel.hpp \
	Qt5Sql/QSqlResult.hpp \
	Qt5Sql/QSqlTableModel.hpp

pkgconfig_DATA += pkg-config/luacxx-Qt5Sql.pc

pkg-config/luacxx-Qt5Sql.pc: pkg-config/Qt5Sql.pc.head
	cat $< >$@
	echo "Requires: luacxx Qt5Sql" >>$@
	echo "Libs: -L$(libdir) -lluacxx-Qt5Sql" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_Qt5Sql_la_CPPFLAGS)" >>$@

endif

if BUILD_gobject_introspection

libluacxx_la_SOURCES += \
	Gtk/GIBaseInfo.cpp \
	Gtk/GObject.cpp \
	search/GIRepository.cpp

nobase_pkginclude_HEADERS += \
	Gtk/GIBaseInfo.hpp \
	Gtk/GObject.hpp \
	search/GIRepository.hpp

pkgconfig_DATA += pkg-config/luacxx-gobject-introspection.pc

pkg-config/luacxx-gobject-introspection.pc: pkg-config/gobject-introspection.pc.head
	cat $< >$@

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

pkgconfig_DATA += pkg-config/luacxx-ncurses.pc

pkg-config/luacxx-ncurses.pc: pkg-config/ncurses.pc.head
	cat $< >$@
	echo "Requires: luacxx ncursesw" >>$@
	echo "Libs: -L$(libdir) -lluacxx-ncurses" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_ncurses_la_CPPFLAGS)" >>$@

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

pkgconfig_DATA += pkg-config/luacxx-nanomsg.pc

pkg-config/luacxx-nanomsg.pc: pkg-config/nanomsg.pc.head
	cat $< >$@
	echo "Libs: $(libluacxx_nanomsg_la_LIBADD)" >>$@
	echo "Cflags: $(libluacxx_nanomsg_la_CPPFLAGS)" >>$@

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

pkgconfig_DATA += pkg-config/luacxx-libevdev.pc

pkg-config/luacxx-libevdev.pc: pkg-config/libevdev.pc.head
	cat $< >$@
	echo "Requires: luacxx libevdev" >>$@
	echo "Libs: -L$(libdir) -lluacxx-libevdev" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_libevdev_la_CPPFLAGS)" >>$@

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

pkgconfig_DATA += pkg-config/luacxx-libinput.pc

pkg-config/luacxx-libinput.pc: pkg-config/libinput.pc.head
	cat $< >$@
	echo "Requires: luacxx libinput" >>$@
	echo "Libs: -L$(libdir) -lluacxx-libinput" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_libinput_la_CPPFLAGS)" >>$@

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

pkgconfig_DATA += pkg-config/luacxx-egl.pc

pkg-config/luacxx-egl.pc: pkg-config/egl.pc.head
	cat $< >$@
	echo "Requires: luacxx egl" >>$@
	echo "Libs: -L$(libdir) -lluacxx-egl" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_egl_la_CPPFLAGS)" >>$@

endif

if BUILD_drm

lib_LTLIBRARIES += libluacxx-drm.la

libluacxx_drm_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS) \
	$(drm_CFLAGS)

libluacxx_drm_la_LIBADD = \
	$(drm_LIBS) \
	libluacxx.la

libluacxx_drm_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_drm_la_SOURCES = \
	xf86drmMode.cpp

nobase_pkginclude_HEADERS += \
	xf86drmMode.hpp

pkgconfig_DATA += pkg-config/luacxx-drm.pc

pkg-config/luacxx-drm.pc: pkg-config/drm.pc.head
	cat $< >$@
	echo "Requires: luacxx libdrm" >>$@
	echo "Libs: -L$(libdir) -lluacxx-drm" >> $@
	echo "Cflags: -I$(includedir) $(libluacxx_drm_la_CPPFLAGS)" >>$@

endif

if BUILD_gbm

lib_LTLIBRARIES += libluacxx-gbm.la

libluacxx_gbm_la_CPPFLAGS = \
	$(libluacxx_la_CPPFLAGS) \
	$(gbm_CFLAGS)

libluacxx_gbm_la_LIBADD = \
	$(gbm_LIBS) \
	libluacxx.la

libluacxx_gbm_la_LDFLAGS = -version-info 0:0:0 --build-id

libluacxx_gbm_la_SOURCES = \
	gbm.cpp

nobase_pkginclude_HEADERS += \
	gbm.hpp

pkgconfig_DATA += pkg-config/luacxx-gbm.pc

pkg-config/luacxx-gbm.pc: pkg-config/gbm.pc.head
	cat $< >$@
	echo "Requires: luacxx gbm" >>$@
	echo "Libs: -L$(libdir) -lluacxx-gbm" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_gbm_la_CPPFLAGS)" >>$@

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

pkgconfig_DATA += pkg-config/luacxx-linux.pc

pkg-config/luacxx-linux.pc: pkg-config/linux.pc.head
	cat $< >$@
	echo "Requires: luacxx" >>$@
	echo "Cflags: -I$(includedir) $(libluacxx_linux_la_CPPFLAGS)" >>$@

endif

bin_PROGRAMS = luacxx
luacxx_CPPFLAGS += $(libluacxx_la_CPPFLAGS)
luacxx_LDADD += libluacxx.la

luacxx_SOURCES = \
	luacxx.cpp

check_PROGRAMS += \
	test_luacxx

test_luacxx_CXXFLAGS = \
	$(libluacxx_la_CPPFLAGS) \
	@BOOST_CPPFLAGS@ \
	-DBOOST_TEST_DYN_LINK \
	-DTEST_DIR=\"$(top_srcdir)/src/tests/\"

test_luacxx_LDADD = \
	libluacxx.la \
	@BOOST_LDFLAGS@ \
	@BOOST_UNIT_TEST_FRAMEWORK_LIB@

test_luacxx_SOURCES = \
	tests/main.cpp

TESTS = $(check_PROGRAMS)

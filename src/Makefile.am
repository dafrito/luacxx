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
	Qt/QChar.hpp \
	Qt/QString.hpp \
	Qt/QVariant.hpp \
	Gtk/GObject.hpp \
	Gtk/require.hpp \
	Gtk/GIBaseInfo.hpp \
	Gtk/GIRepository.hpp

libluacxx_la_SOURCES = \
	algorithm.cpp \
	load.cpp \
	stack.cpp \
	thread.cpp

if BUILD_QT

libluacxx_la_SOURCES += \
	module/DirectoryModuleLoader.cpp \
	Qt/QVariant.cpp \
	Qt/QObject.cpp \
	Qt/QObjectSlot.cpp

endif

if BUILD_GTK

libluacxx_la_SOURCES += \
	Gtk/GIBaseInfo.cpp \
	Gtk/GObject.cpp \
	Gtk/GIRepository.cpp \
	Gtk/require.cpp

endif

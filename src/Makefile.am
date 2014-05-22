lib_LTLIBRARIES = libluacxx.la

libluacxx_la_CPPFLAGS = $(QT_CXXFLAGS) $(GIO_CXXFLAGS) @LUA_INCLUDE@ -I$(top_srcdir)/src
libluacxx_la_LIBADD = $(QT_LIBS) $(GIO_LIB) @LUA_LIB@
libluacxx_la_LDFLAGS = -version-info 0:0:0 --build-id

nobase_pkginclude_HEADERS = \
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
	qt/QObject.hpp \
	qt/QObjectSlot.hpp \
	qt/QChar.hpp \
	qt/QString.hpp \
	qt/QVariant.hpp \
	gtk/GObject.hpp \
	gtk/require.hpp \
	gtk/GIBaseInfo.hpp \
	gtk/GIRepository.hpp

libluacxx_la_SOURCES = \
	algorithm.cpp \
	load.cpp \
	stack.cpp \
	thread.cpp

if BUILD_QT

libluacxx_la_SOURCES += \
	module/DirectoryModuleLoader.cpp \
	qt/QVariant.cpp \
	qt/QObject.cpp \
	qt/QObjectSlot.cpp

# moc-generated source files
#libluacxx_la_MOC_SOURCES = \
#	qt/moc_QObjectObserver.cpp

nodist_libluacxx_la_SOURCES = $(libluacxx_la_MOC_SOURCES)

qt/moc_%.cpp: $(top_srcdir)/src/%.hpp
	@QT_MOC@ -o $@ $<

mostlyclean-local:
	rm -f $(libluacxx_la_MOC_SOURCES)
.PHONY: mostlyclean-local

endif

if BUILD_GTK

libluacxx_la_SOURCES += \
	gtk/GIBaseInfo.cpp \
	gtk/GObject.cpp \
	gtk/GIRepository.cpp \
	gtk/require.cpp

endif

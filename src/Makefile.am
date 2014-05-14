lib_LTLIBRARIES = liblua-cxx.la

liblua_cxx_la_CPPFLAGS = $(QT_CXXFLAGS) @LUA_INCLUDE@ -I$(top_srcdir)/src
liblua_cxx_la_LIBADD = $(QT_LIBS) @LUA_LIB@
liblua_cxx_la_LDFLAGS = -version-info 0:0:0 --build-id

nobase_pkginclude_HEADERS = \
	algorithm.hpp \
	assert.hpp \
	error.hpp \
	global.hpp \
	index.hpp \
	link.hpp \
	load.hpp \
	push.hpp \
	range.hpp \
	reference.hpp \
	state.hpp \
	store.hpp \
	thread.hpp \
	type.hpp \
	userdata.hpp \
	type/function.hpp \
	type/numeric.hpp \
	type/standard.hpp \
	module/DirectoryModuleLoader.hpp \
	module/ModuleLoader.hpp \
	qt/QObject.hpp \
	qt/QObjectSlot.hpp \
	qt/type/QChar.hpp \
	qt/type/QString.hpp \
	qt/type/QVariant.hpp

liblua_cxx_la_SOURCES = \
	algorithm.cpp \
	load.cpp \
	push.cpp \
	store.cpp \
	thread.cpp

if BUILD_QT

liblua_cxx_la_SOURCES += \
	module/DirectoryModuleLoader.cpp \
	qt/type/QVariant.cpp \
	qt/QObject.cpp \
	qt/QObjectSlot.cpp

# moc-generated source files
#liblua_cxx_la_MOC_SOURCES = \
#	qt/moc_QObjectObserver.cpp

nodist_liblua_cxx_la_SOURCES = $(liblua_cxx_la_MOC_SOURCES)

qt/moc_%.cpp: $(top_srcdir)/src/%.hpp
	@QT_MOC@ -o $@ $<

mostlyclean-local:
	rm -f $(liblua_cxx_la_MOC_SOURCES)
.PHONY: mostlyclean-local

endif

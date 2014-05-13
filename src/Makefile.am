lib_LTLIBRARIES = liblua-cxx.la
liblua_cxx_la_CPPFLAGS = @QT_CXXFLAGS@ @LUA_INCLUDE@ -I$(top_srcdir)/src
liblua_cxx_la_LIBADD = @QT_LIBS@ @LUA_LIB@
liblua_cxx_la_LDFLAGS = -version-info 0:0:0 --build-id

# moc-generated source files
#liblua_cxx_la_MOC_SOURCES = \
#	qt/moc_QObjectObserver.cpp

nodist_liblua_cxx_la_SOURCES = $(liblua_cxx_la_MOC_SOURCES)

liblua_cxx_la_SOURCES = \
	load.cpp \
	push.cpp \
	store.cpp \
	algorithm.cpp \
	thread.cpp \
	assert.cpp \
	qt/type/QVariant.cpp \
	module/DirectoryModuleLoader.cpp

pkginclude_HEADERS = \
	error.hpp \
	assert.hpp \
	push.hpp \
	store.hpp \
	state.hpp \
	iteration.hpp \
	load.hpp \
	algorithm.hpp \
	link.hpp \
	module/DirectoryModuleLoader.hpp \
	module/ModuleLoader.hpp \
	qt/type/QString.hpp \
	qt/type/QVariant.hpp \
	qt/type/QChar.hpp

mostlyclean-local:
	rm -f $(liblua_cxx_la_MOC_SOURCES)
.PHONY: mostlyclean-local

qt/moc_%.cpp: $(top_srcdir)/src/%.hpp
	@QT_MOC@ -o $@ $<

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
	stack.cpp \
	algorithm.cpp \
	module/DirectoryModuleLoader.cpp

pkginclude_HEADERS = \
	state.hpp \
	exception.hpp \
	load.hpp \
	algorithm.hpp \
	link.hpp \
	module/DirectoryModuleLoader.hpp \
	module/ModuleLoader.hpp \
	stack.hpp

mostlyclean-local:
	rm -f $(liblua_cxx_la_MOC_SOURCES)
.PHONY: mostlyclean-local

qt/moc_%.cpp: $(top_srcdir)/src/%.hpp
	@QT_MOC@ -o $@ $<

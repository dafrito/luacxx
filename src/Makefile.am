lib_LTLIBRARIES = liblua-cxx.la
liblua_cxx_la_CPPFLAGS = @QT_CXXFLAGS@ -I$(top_srcdir)/include
liblua_cxx_la_LIBADD = @QT_LIBS@
liblua_cxx_la_LDFLAGS = -version-info 0:0:0

# moc-generated source files
liblua_cxx_la_MOC_SOURCES =

nodist_liblua_cxx_la_SOURCES = $(liblua_cxx_la_MOC_SOURCES)

liblua_cxx_la_SOURCES = \
	Bootstrapper.cpp \
	util.cpp

pkginclude_HEADERS = \
	../include/Bootstrapper.hpp \
	../include/util.hpp

bin_PROGRAMS = lua-cxx
lua_cxx_CPPFLAGS = $(liblua_cxx_la_CPPFLAGS)
lua_cxx_LDADD = liblua_cxx.la $(liblua_cxx_la_LIBADD)

lua_cxx_SOURCES = \
	main.cpp

nodist_lua_cxx_SOURCES = $(lua_cxx_MOC_SOURCES)

mostlyclean-local:
	rm -f $(liblua_cxx_la_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: $(top_srcdir)/src/%.hpp
	@QT_MOC@ -o $@ $<

moc_%.cpp: $(top_srcdir)/include/%.hpp
	@QT_MOC@ -o $@ $<

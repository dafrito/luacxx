lib_LTLIBRARIES = liblua-cxx.la
liblua_cxx_la_CPPFLAGS = @QT_CXXFLAGS@ @LUA_INCLUDE@ -I$(top_srcdir)/include
liblua_cxx_la_LIBADD = @QT_LIBS@ @LUA_LIB@
liblua_cxx_la_LDFLAGS = -version-info 0:0:0

pkginclude_HEADERS = \
	../include/Lua.hpp \
	../include/loaders.hpp \
	../include/Lua.hpp \
	../include/LuaStack.hpp \
	../include/LuaValue.hpp \
	../include/LuaGlobal.hpp \
	../include/LuaAccessible.hpp \
	../include/LuaGlobalAccessible.hpp \
	../include/LuaReference.hpp \
	../include/LuaReferenceAccessible.hpp \
	../include/types.hpp \
	../include/LuaException.hpp

# moc-generated source files
liblua_cxx_la_MOC_SOURCES = \
	moc_Lua.cpp

nodist_liblua_cxx_la_SOURCES = $(liblua_cxx_la_MOC_SOURCES)

liblua_cxx_la_SOURCES = \
	loaders.cpp \
	Lua.cpp \
	LuaStack.cpp \
	types.cpp

mostlyclean-local:
	rm -f $(liblua_cxx_la_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: $(top_srcdir)/src/%.hpp
	@QT_MOC@ -o $@ $<

moc_%.cpp: $(top_srcdir)/include/%.hpp
	@QT_MOC@ -o $@ $<

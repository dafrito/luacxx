lib_LTLIBRARIES = liblua-cxx.la
liblua_cxx_la_CPPFLAGS = @QT_CXXFLAGS@ @LUA_INCLUDE@ -I$(top_srcdir)/include
liblua_cxx_la_LIBADD = @QT_LIBS@ @LUA_LIB@
liblua_cxx_la_LDFLAGS = -version-info 0:0:0

pkginclude_HEADERS = \
	../include/LuaEnvironment.hpp \
	../include/loaders.hpp \
	../include/LuaStack.hpp \
	../include/stack/accessible.cpp \
	../include/stack/invocation.cpp \
	../include/stack/reference.cpp \
	../include/stack/userdata.cpp \
	../include/insertion.cpp \
	../include/LuaValue.hpp \
	../include/LuaGlobalAccessible.hpp \
	../include/LuaStackAccessible.hpp \
	../include/LuaTableAccessible.hpp \
	../include/ModuleLoader.hpp \
	../include/DirectoryModuleLoader.hpp \
	../include/types.hpp \
	../include/table.hpp \
	../include/LuaUserdata.hpp \
	../include/userdata.hpp \
	../include/LuaIndex.hpp \
	../include/LuaException.hpp

# moc-generated source files
liblua_cxx_la_MOC_SOURCES =

nodist_liblua_cxx_la_SOURCES = $(liblua_cxx_la_MOC_SOURCES)

liblua_cxx_la_SOURCES = \
	loaders.cpp \
	LuaEnvironment.cpp \
	LuaStack.cpp \
	LuaIndex.cpp \
	DirectoryModuleLoader.cpp \
	userdata/qobject.cpp \
	LuaAccessible.cpp \
	LuaReferenceAccessible.cpp \
	LuaGlobalAccessible.cpp \
	types.cpp

mostlyclean-local:
	rm -f $(liblua_cxx_la_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: $(top_srcdir)/src/%.hpp
	@QT_MOC@ -o $@ $<

moc_%.cpp: $(top_srcdir)/include/%.hpp
	@QT_MOC@ -o $@ $<

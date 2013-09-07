lib_LTLIBRARIES = liblua-cxx.la
liblua_cxx_la_CPPFLAGS = @QT_CXXFLAGS@ @LUA_INCLUDE@ -I$(top_srcdir)/include
liblua_cxx_la_LIBADD = @QT_LIBS@ @LUA_LIB@
liblua_cxx_la_LDFLAGS = -version-info 0:0:0

# moc-generated source files
liblua_cxx_la_MOC_SOURCES = \
	moc_QObjectObserver.cpp

nodist_liblua_cxx_la_SOURCES = $(liblua_cxx_la_MOC_SOURCES)

liblua_cxx_la_SOURCES = \
	loaders.cpp \
	LuaEnvironment.cpp \
	LuaStack.cpp \
	LuaIndex.cpp \
	DirectoryModuleLoader.cpp \
	qobject.cpp \
	LuaReferenceAccessible.cpp \
	LuaGlobalAccessible.cpp \
	LuaUserdata.cpp \
	QObjectObserver.cpp \
	QObjectSlot.cpp \
	types.cpp \
	type/QVariant.cpp

mostlyclean-local:
	rm -f $(liblua_cxx_la_MOC_SOURCES)
.PHONY: mostlyclean-local

moc_%.cpp: $(top_srcdir)/src/%.hpp
	@QT_MOC@ -o $@ $<

moc_%.cpp: $(top_srcdir)/include/%.hpp
	@QT_MOC@ -o $@ $<

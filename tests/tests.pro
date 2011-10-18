include (../lib/lib.pro)

TEMPLATE = app
TARGET = run-tests

CONFIG += qt qtestlib

INCLUDEPATH += ../lib
DEPENDPATH += ../lib

HEADERS += \
	loaders.hpp \
	BasicTests.hpp \
	TableTests.hpp \
	mocks.hpp

SOURCES += \
	tests.cpp \

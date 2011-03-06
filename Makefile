CXXFLAGS=-Wall -Werror -g -std=c++0x
BUILDDIR=build
SRCDIR=src
TESTDIR=$(SRCDIR)/tests

libs=
cpp_headers=$(wildcard $(SRCDIR)/*.h $(SRCDIR)/*.hpp)
test_headers=$(wildcard $(TESTDIR)/*.h $(TESTDIR)/*.hpp)
source_files=$(cpp_headers) $(test_headers)
APP=tentacles

all: $(BUILDDIR)/$(APP)
.PHONY: all

test: $(BUILDDIR)/testrunner
	$(BUILDDIR)/testrunner
.PHONY: test

clean:
	rm -rf $(BUILDDIR)
.PHONY: clean

$(BUILDDIR)/$(APP): $(source_files) | $(BUILDDIR)
	g++ $(CXXFLAGS) -o $@ `pkg-config --libs ncurses` $<

$(BUILDDIR)/testrunner: $(test_headers) | $(BUILDDIR)
	cxxtestgen --error-printer $< | g++ $(CXXFLAGS) -x c++ -o $@ -

$(BUILDDIR):
	mkdir $(BUILDDIR)

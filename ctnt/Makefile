BUILDDIR = build
OUTDIR ?= $(BUILDDIR)
TESTDIR=tests

NAME=ctnt
LIB=$(OUTDIR)/lib$(NAME).so
APP=$(OUTDIR)/$(NAME)

CXXFLAGS=-Wall -Werror -g -std=c++0x 
CXXFLAGS+= -L$(OUTDIR) -Wl,-R$(OUTDIR) 
CXXFLAGS+= `pkg-config --libs ncurses lua`

all: lib app
.PHONY: all

lib: $(LIB)

app: $(APP)
.PHONY: app lib

objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
$(LIB): $(addprefix $(BUILDDIR)/, $(objects)) | $(BUILDDIR)
	g++ $(CXXFLAGS) -shared -fPIC -o $@ $<

$(APP): $(addprefix $(BUILDDIR)/, $(objects)) $(BUILDDIR)/main.o | $(BUILDDIR)
	g++ $(CXXFLAGS) -fPIC -o $@ $^

$(BUILDDIR)/main.o: main
	g++ $(CXXFLAGS) -fPIC -c -o $@ -x c++ main

$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	g++ $(CXXFLAGS) -fPIC -c -o $@ $<

$(BUILDDIR):
	mkdir $(BUILDDIR)

test: $(BUILDDIR)/testrunner
	$<
.PHONY: test

test_headers=$(wildcard $(TESTDIR)/*.h $(TESTDIR)/*.hpp)
$(BUILDDIR)/testrunner: $(LIB) $(test_headers)
	cxxtestgen --error-printer $(test_headers) | g++ $(CXXFLAGS) -l$(NAME) -x c++ -o $@ -

clean:
	rm -rf $(BUILDDIR)
.PHONY: clean


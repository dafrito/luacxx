NAME=tentacle
LIB=$(OUTDIR)/lib$(NAME).so

BUILDDIR = build
OUTDIR ?= $(BUILDDIR)
TESTDIR=tests

CXXFLAGS=-Wall -Werror -g -std=c++0x 
CXXFLAGS+= -L$(OUTDIR) -Wl,-R$(OUTDIR) 

all: $(LIB) $(APP)
.PHONY: all

objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
$(LIB): $(addprefix $(BUILDDIR)/, $(objects)) | $(BUILDDIR)
	g++ $(CXXFLAGS) -shared -fPIC -o $@ $<

$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	g++ $(CXXFLAGS) -c -o $@ $<

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


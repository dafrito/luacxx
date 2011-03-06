CXXFLAGS=-Wall -Werror -g -std=c++0x
BUILDDIR=build
NAME=lua-c++
LIB=$(BUILDDIR)/lib$(NAME).so
TESTDIR=tests

libs=lua

all: $(LIB)
.PHONY: all

objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
$(LIB): $(addprefix $(BUILDDIR)/, $(objects)) | $(BUILDDIR)
	g++ $(CXXFLAGS) -shared -fPIC -o $@ $(addprefix -l, $(libs)) $<

$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	g++ $(CXXFLAGS) -c -o $@ $(addprefix -l, $(libs)) $<

$(BUILDDIR):
	mkdir $(BUILDDIR)

test: $(BUILDDIR)/testrunner
	$<
.PHONY: test

test_headers=$(wildcard $(TESTDIR)/*.h $(TESTDIR)/*.hpp)
local_libs:=`pwd`/$(BUILDDIR)
$(BUILDDIR)/testrunner: $(LIB) $(test_headers)
	cxxtestgen --error-printer $(test_headers) | g++ $(CXXFLAGS) -L$(local_libs) -Wl,-R$(local_libs) $(addprefix -l, $(libs) $(NAME)) -x c++ -o $@ -

clean:
	rm -rf $(BUILDDIR)
.PHONY: clean


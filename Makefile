export OUTDIR := $(CURDIR)/artifact

all: | $(OUTDIR)
	$(MAKE) -C lua $@

clean:
	$(MAKE) -C lua $@
	rm -rf $(OUTDIR)

test: | $(OUTDIR)
	$(MAKE) -C lua $@

.PHONY: all clean test

$(OUTDIR):
	mkdir -p $(OUTDIR)

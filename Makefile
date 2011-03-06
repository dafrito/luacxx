export OUTDIR := $(CURDIR)/artifacts

clean: 
	$(MAKE) -C lua $@
	$(MAKE) -C tentacle $@
	$(MAKE) -C ctnt $@
	rm -rf $(OUTDIR)
.PHONY: clean

all test: | $(OUTDIR)
	$(MAKE) -C lua $@
	$(MAKE) -C tentacle $@
	$(MAKE) -C ctnt $@
.PHONY: all test

$(OUTDIR):
	mkdir -p $(OUTDIR)

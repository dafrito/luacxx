
all:
	$(MAKE) -C lua $@

clean:
	$(MAKE) -C lua $@

test:
	$(MAKE) -C lua $@

.PHONY: all clean test

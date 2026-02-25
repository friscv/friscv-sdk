.PHONY: all clean examples echo

all: examples

examples: echo

echo:
	$(MAKE) -C examples/echo

clean:
	$(MAKE) -C examples/echo clean

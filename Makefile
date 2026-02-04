PLATFORM ?= friscv

.PHONY: all clean examples echo

all: examples

examples: echo

echo:
	$(MAKE) -C examples/echo PLATFORM=$(PLATFORM)

clean:
	$(MAKE) -C examples/echo clean

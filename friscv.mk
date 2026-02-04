# friscv-sdk include file
# Include this in your application Makefile:
#   FRISCV_SDK := /path/to/friscv-sdk
#   include $(FRISCV_SDK)/friscv.mk
# See examples/

FRISCV_SDK ?= $(dir $(lastword $(MAKEFILE_LIST)))

# Platform selection: friscv (default) or raspi
PLATFORM ?= friscv

# SDK source files (platform-independent)
FRISCV_SRCS := $(FRISCV_SDK)/src/uart_protocol.c

# Include path
FRISCV_CFLAGS := -I$(FRISCV_SDK)/include

ifeq ($(PLATFORM),friscv)
    CROSS ?= riscv32-unknown-elf-
    CC := $(CROSS)gcc
    OBJCOPY := $(CROSS)objcopy
    OBJDUMP := $(CROSS)objdump
    SIZE := $(CROSS)size

    ARCH := rv32i
    ABI := ilp32

    FRISCV_CFLAGS += -march=$(ARCH) -mabi=$(ABI) -ffreestanding -fno-builtin -nostdlib -nostartfiles -Wall -Wextra -O3
    FRISCV_LDFLAGS := -T $(FRISCV_SDK)/startup/link.ld -nostdlib -nostartfiles -Wl,--gc-sections

    # Drivers
    FRISCV_SRCS += $(FRISCV_SDK)/drivers/friscv/uart.c
    FRISCV_SRCS += $(FRISCV_SDK)/drivers/friscv/leds.c

    # Startup code
    FRISCV_CRT0 := $(FRISCV_SDK)/startup/crt0.S

else ifeq ($(PLATFORM),raspi)
    CC := gcc
    FRISCV_CFLAGS += -Wall -Wextra -O3
    FRISCV_LDFLAGS :=

    # Drivers
    FRISCV_SRCS += $(FRISCV_SDK)/drivers/raspi/uart.c
    FRISCV_SRCS += $(FRISCV_SDK)/drivers/raspi/leds.c

    # No startup code needed for Linux
    FRISCV_CRT0 :=

else
    $(error Unknown PLATFORM: $(PLATFORM). Use 'friscv' or 'raspi')
endif

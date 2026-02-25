FRISCV_SDK := ../..
include $(FRISCV_SDK)/friscv.mk

BUILD_DIR := build
TARGET := $(BUILD_DIR)/echo

APP_SRCS := main.c
ALL_SRCS := $(FRISCV_CRT0) $(APP_SRCS) $(FRISCV_SRCS)

ELF := $(TARGET).elf
BIN := $(TARGET).bin
DISASM := $(TARGET).dis

.PHONY: all clean

all: $(BIN) $(DISASM)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(ELF): $(ALL_SRCS) | $(BUILD_DIR)
	$(CC) $(FRISCV_CFLAGS) $(FRISCV_LDFLAGS) -o $@ $(ALL_SRCS)
	$(SIZE) $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(DISASM): $(ELF)
	$(OBJDUMP) -d $< > $@

clean:
	rm -rf $(BUILD_DIR)

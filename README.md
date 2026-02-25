# FRISC-V SDK

A bare-metal Software Development Kit for RISC-V applications running on the FRISC-V platform, providing drivers and utilities for embedded development.

## Features

- **UART Driver** - Hardware abstraction for serial communication (blocking/non-blocking)
- **UART Protocol** - Packet-based messaging with command, length, and payload
- **Startup Code** - RISC-V initialization (stack setup, main entry)
- **Linker Script** - Memory layout configuration (511MB RAM at `0x80000000`)

## Project Structure

```sh
friscv-sdk/
├── drivers/
│   ├── friscv/       # FRISC-V hardware drivers
├── include/          # Public headers (uart.h, uart_protocol.h)
├── startup/          # crt0.S and link.ld for bare-metal
├── examples/echo/    # Example application
└── friscv.mk         # SDK build configuration
```

## Usage

1. Set `FRISCV_SDK` to the SDK path
2. Include `friscv.mk` in your Makefile
3. Build with `make`

**Example Makefile:**

```makefile
FRISCV_SDK := /path/to/friscv-sdk
APP := myapp
SRCS := main.c

include $(FRISCV_SDK)/friscv.mk
```

**Build:**

```bash
make
```
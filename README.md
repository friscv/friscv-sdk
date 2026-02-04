# FRISC-V SDK

A bare-metal SDK for RISC-V applications running on the FRISC-V SoC, providing drivers and utilities for embedded development.

## Features

- **UART Driver** - Hardware abstraction for serial communication (blocking/non-blocking)
- **UART Protocol** - Packet-based messaging with command, length, and payload
- **Startup Code** - RISC-V initialization (stack setup, main entry)
- **Linker Script** - Memory layout configuration (511MB RAM at 0x80000000)

## Project Structure

```sh
friscv-sdk/
├── drivers/
│   ├── friscv/       # FRISC-V hardware drivers
│   └── raspi/        # Raspberry Pi drivers (Linux)
├── include/          # Public headers (uart.h, uart_protocol.h)
├── startup/          # crt0.S and link.ld for bare-metal
├── examples/echo/    # Example application
└── friscv.mk         # SDK build configuration
```

## Platforms

| Platform | Description                  | Compiler                  |
|----------|------------------------------|---------------------------|
| `friscv` | Bare-metal RISC-V (default)  | `riscv32-unknown-elf-gcc` |
| `raspi`  | Raspberry Pi Linux (testing) | `gcc`                     |

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

**Build for different platforms:**

```sh
make                    # Build for FRISC-V (default)
make PLATFORM=raspi     # Build for Raspberry Pi
```

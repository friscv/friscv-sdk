.section .text.init
.global _start

.equ HALT_ADDR, 0x50000000

_start:
    la sp, _stack_top

    call main

    // Halt by writing to HALT_ADDR
    li t0, HALT_ADDR
    sw a0, 0(t0)

    // Hang if hardware halt fails
hang:
    j hang

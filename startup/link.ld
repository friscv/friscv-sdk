OUTPUT_ARCH( "riscv" )
ENTRY( _start )

MEMORY
{
    /* The first 1M of memory on the PYNQ-Z2 is reserved for OCM
       Only 511M of 512M is usable */
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 511M
}

SECTIONS
{
    .text :
    {
        *(.text.init)
        *(.text)
    } > RAM

    .data :
    {
        *(.data)
    } > RAM

    .bss :
    {
        *(.bss)
    } > RAM

    /* Place the stack at the top of RAM */
    _stack_top = ORIGIN(RAM) + LENGTH(RAM);
}

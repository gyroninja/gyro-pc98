OUTPUT_FORMAT(binary)
SECTIONS
{
    .text 0x0100: # com files start execution at 0x0100
    {
        crt0.o    # Make execution starts with the C runtime's entrypoint
        *(.text);
    }
    .data :
    {
        *(.data);
        *(.bss);
        *(.rodata);
    }
}

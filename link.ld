ENTRY(_start)

SECTIONS
{
    . = 0x80;

    .text : {
        *(.text*)
        . = ALIGN(4);
    }

    .rodata : {
        *(.rodata*)
        . = ALIGN(4);
    }

    .data : {
        *(.data)
        . = ALIGN(4);
    }

    .bss : {
        *(.bss)
        *(COMMON)
        . = ALIGN(4);
    }
}

SECTIONS {
    . = 0x100;
    .text : {
        *(.text*)
    }
    .data : {
        *(.data*)
        *(.rodata*)
    }
    .bss : {
        *(.bss*)
        *(COMMON)
    }
}

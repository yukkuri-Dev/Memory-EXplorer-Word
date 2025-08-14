SECTIONS
{
    . = 0x100; /* 実行開始アドレスを適宜指定 */
    .text : { *(.text) }
    .rodata : { *(.rodata*) }
    .data : { *(.data) }
    .bss : { *(.bss) *(COMMON) }
}

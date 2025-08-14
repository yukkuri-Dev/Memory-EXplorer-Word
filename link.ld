SECTIONS
{
    /* 開始アドレス（例: 0x80） */
    . = 0x80;

    /* すべてのコードと定数データ */
    .text : {
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    }

    /* すべての .data をまとめる */
    .data : {
        *(.data)
        *(.data.*)
        . = ALIGN(4);
    }

    /* BSS もまとめる */
    .bss : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
    }
}

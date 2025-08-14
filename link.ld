ENTRY(_start) /* 必要ならエントリを定義 */

SECTIONS
{
    . = 0x80; /* TEXTの開始アドレス。exword環境だと0x80スタートが多い */

    .text : {
        *(.text*)       /* すべての.textを結合 */
        *(.rodata*)     /* 読み取り専用データもTEXTに入れる場合 */
        . = ALIGN(4);   /* アラインメント調整 */
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
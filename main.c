#include <graphics/text.h>
#include <sh4a/input/keypad.h>
#include <syscalls/syscalls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void *lcdc_get_vram_address(void);
extern void lcdc_get_dimensions(uint16_t *width, uint16_t *height);
extern void lcdc_copy_vram(void);

void blink_screen(int times, int interval_ms,int selector) {
    uint16_t width, height;
    uint16_t *vram = (uint16_t *)lcdc_get_vram_address();
    lcdc_get_dimensions(&width, &height);
    int total_pixels = width * height;

    for (int i = 0; i < times; ++i) {
		if (selector==0);
			for (int j = 0; j < total_pixels; ++j) vram[j] = 0xFFFF;
        	lcdc_copy_vram();
		if (selector==1);
        	for (int j = 0; j < total_pixels; ++j) vram[j] = 0x0000;
        	lcdc_copy_vram();
    }
}

void main(void) {
    while(1) {
		if (get_key_pressed(KEY_POWER))
			blink_screen(10,200,0);
		if (get_key_pressed(KEY_ENTER))
			software_reset();
			
	}
}

void software_reset(void) {
    // EXPEVT: Manual Reset コード
    *(volatile unsigned int *)0xFF000024 = 0x00000020;

    // 割り込みベクタベースリセット（VBR）
    __asm__ volatile (
        "mov.l  #0x00000000, r0\n\t"
        "ldc    r0, vbr\n\t"
    );

    // ステータスレジスタ設定 (例: MD=1, RB=1, BL=1, IMASK=1111)
    __asm__ volatile (
        "mov.l  #0x500000F0, r0\n\t"  // 適切なSR初期値
        "ldc    r0, sr\n\t"
    );

    // プログラムカウンタをリセットベクタへジャンプ
    void (*reset_vector)(void) = (void *)0xA0000000;
    reset_vector();

    while (1); // 念のためループ（戻ってくるはずがない）
}

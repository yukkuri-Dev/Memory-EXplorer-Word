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


void main(void);

void _start(void) {
    // Set stack pointer using inline assembly.
    __asm__ volatile (
        "mov.l .L_stack_addr, r15\n\t"
        "bra .L_after_stack_init\n\t"
        ".align 2\n\t"
        ".L_stack_addr: .long 0x8000\n\t"
        ".L_after_stack_init:"
    );

    // Call main
    main();

    // If main returns, hang
    while(1);
}

void main(void) {
    while(1) {
		if (get_key_pressed(KEY_POWER))
			blink_screen(10,200,0);
		if (get_key_pressed(KEY_ENTER))
			blink_screen(10,200,1);
	}
}
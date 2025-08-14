#include <graphics/text.h>
#include <sh4a/input/keypad.h>
#include <syscalls/syscalls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>





extern void *lcdc_get_vram_address(void);
extern void lcdc_get_dimensions(uint16_t *width, uint16_t *height);
extern void lcdc_copy_vram(void);

void blink_screen(int times, int interval_ms) {
    uint16_t width, height;
    uint16_t *vram = (uint16_t *)lcdc_get_vram_address();
    lcdc_get_dimensions(&width, &height);
    int total_pixels = width * height;

    for (int i = 0; i < times; ++i) {
        for (int j = 0; j < total_pixels; ++j) vram[j] = 0xFFFF;
        lcdc_copy_vram();
		
        for (int j = 0; j < total_pixels; ++j) vram[j] = 0x0000;
        lcdc_copy_vram();

    }
}


void main(void) {
    	while(1) {
		if (get_key_pressed(KEY_POWER))
			blink_screen(10,200);
			return 0;
	}
}
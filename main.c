#include <graphics/text.h>
#include <sh4a/input/keypad.h>
#include <syscalls/syscalls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define stack pointer address in a C variable.
// The compiler will place this in the .rodata section.
const unsigned int stack_address = 0x8000;

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
void __start(void);

// Create a global symbol alias named '_start' for our C function '__start'.
__asm__(".global _start\n.set _start, ___start");

void __start(void) {
    // Set stack pointer r15 to the value of stack_address.
    // %0 will be replaced by the address of the 'stack_address' variable.
    // We load this address into r0, then load the value at that address into r15.
    __asm__ volatile (
        "mov.l %0, r0\n\t"
        "mov.l @r0, r15"
        : : "r" (&stack_address) : "r0"
    );

    main();

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

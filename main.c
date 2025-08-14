#include <graphics/text.h>
#include <sh4a/input/keypad.h>
#include <syscalls/syscalls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void) {
    	while(1) {
		if (get_key_pressed(KEY_POWER))
			exit(-2);
	}
}
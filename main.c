#include <graphics/text.h>
#include <sh4a/input/keypad.h>
#include <syscalls/syscalls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rc/rc.h>

static char *media[2] = {
	"\\\\drv0\\",
	"\\\\crd0\\"
};

void main(void) {
	static char *sramfile = NULL;

	char *buf;
	char id[10];
	unsigned long drv;
	sys_dict_info(&drv,id);
	buf = malloc(50);
	sprintf(buf, "%s:%s%s\\_USER\\", media[drv], media[drv], id);
	rc_setvar("rcpath", 1,buf);
	sprintf(buf, "%sROMS\\", media[drv]);
	rc_setvar("savedir", 1, buf);
	rc_setvar("romdir", 1, buf);

    unsigned char data[26] = {
        0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x20, 0x57, 0x4F,
        0x52, 0x4C, 0x44, 0x0D, 0x0A, 0x50, 0x4F, 0x43,
        0x20, 0x49, 0x53, 0x20, 0x57, 0x4F, 0x52, 0x4B,
        0x53, 0x21
    };




	sramfile = "test.txt";

	FILE *f = fopen(sramfile,"wb");
	size_t written = fwrite(data,1,sizeof(data),f);
	fclose(f);
    while(1) {
	}
}

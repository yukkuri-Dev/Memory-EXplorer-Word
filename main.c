#include <syscalls/syscalls.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    unsigned char data[26] = {
        0x48,0x45,0x4C,0x4C,0x4F,0x20,0x57,0x4F,
        0x52,0x4C,0x44,0x0D,0x0A,0x50,0x4F,0x43,
        0x20,0x49,0x53,0x20,0x57,0x4F,0x52,0x4B,
        0x53,0x21
    };

    // 保存先パスを自分で作る
    char *filename = malloc(128);
    if (!filename) return 1;

    // 例: drv0 直下に保存
    strcpy(filename, "\\\\drv0\\poop.txt");

    // ファイル作成 (WRITE モード)
    int fd = sys_create(filename, FILE_WR);
    if (fd < 0) {
        free(filename);
        return 1;
    }

    // 書き込み
    sys_write(fd, data, sizeof(data));

    // ファイルを閉じる
    sys_close(fd);

    free(filename);

    while(1) {} // 終了しない

    return 0;
}

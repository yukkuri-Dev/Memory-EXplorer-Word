#include <syscalls/syscalls.h>

int main(void) {
    unsigned char data[26] = {
        0x48,0x45,0x4C,0x4C,0x4F,0x20,0x57,0x4F,
        0x52,0x4C,0x44,0x0D,0x0A,0x50,0x4F,0x43,
        0x20,0x49,0x53,0x20,0x57,0x4F,0x52,0x4B,
        0x53,0x21
    };

    // 固定バッファに直接パスを書き込む
    char filename[64] = "\\\\drv0\\poop.txt";

    // ファイル作成
    int fd = sys_create(filename, FILE_WR);
    if (fd < 0) return 1;

    // 書き込み
    sys_write(fd, data, sizeof(data));

    // 閉じる
    sys_close(fd);

    while(1) {}

    return 0;
}

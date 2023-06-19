#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
    int fd;
    char buffer[256];

    // 創建命名管道
    mkfifo(FIFO_NAME, 0666);

    // 打開命名管道進行讀取
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 從命名管道讀取數據
    ssize_t nbytes = read(fd, buffer, sizeof(buffer));
    if (nbytes == -1) {
        perror("read");
        return 1;
    }

    printf("從命名管道讀取到的數據：%s\n", buffer);

    // 關閉命名管道
    close(fd);

    // 移除命名管道
    unlink(FIFO_NAME);

    return 0;
}

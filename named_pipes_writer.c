#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/myfifo"

int main() {
    int fd;
    char message[] = "Hello, named pipe!";

    // 打開命名管道進行寫入
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 將消息寫入命名管道
    ssize_t nbytes = write(fd, message, sizeof(message));
    if (nbytes == -1) {
        perror("write");
        return 1;
    }

    // 關閉命名管道
    close(fd);

    return 0;
}

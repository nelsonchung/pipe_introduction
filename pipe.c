#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char message[] = "Hello, pipe!";

    // 創建管道
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // 創建子進程
    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // 子進程（讀取者）
        close(pipefd[1]);  // 關閉寫端

        char buffer[256];
        ssize_t nbytes;

        // 從管道讀取數據
        nbytes = read(pipefd[0], buffer, sizeof(buffer));
        if (nbytes == -1) {
            perror("read");
            return 1;
        }

        printf("子進程收到消息： %s\n", buffer);

        close(pipefd[0]);  // 關閉讀端

    } else {
        // 父進程（寫入者）
        close(pipefd[0]);  // 關閉讀端

        // 將消息寫入管道
        ssize_t nbytes = write(pipefd[1], message, sizeof(message));
        if (nbytes == -1) {
            perror("write");
            return 1;
        }

        close(pipefd[1]);  // 關閉寫端
    }

    return 0;
}

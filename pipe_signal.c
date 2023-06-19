#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// 信號處理函數
void signal_handler(int signum) {
    switch (signum) {
        case SIGINT:
            printf("接收到中斷信號(SIGINT)\n");
            // 在此處理SIGINT信號的相應操作
            // ...
            break;
        case SIGTERM:
            printf("接收到終止信號(SIGTERM)\n");
            // 在此處理SIGTERM信號的相應操作
            // ...
            break;
        case SIGUSR1:
            printf("接收到用戶定義信號(SIGUSR1)\n");
            // 在此處理SIGUSR1信號的相應操作
            // ...
            break;
        default:
            printf("接收到未知信號：%d\n", signum);
            break;
    }
}

int main() {
    // 註冊信號處理函數
    signal(SIGINT, signal_handler);  // Ctrl+C 中斷信號
    signal(SIGTERM, signal_handler); // 終止信號
    signal(SIGUSR1, signal_handler); // 用戶定義信號

    printf("請按 Ctrl+C 結束程式...\n");

    // 進入無限迴圈，等待信號
    while (1) {
        // 進程執行正常操作
        sleep(1);
    }

    return 0;
}

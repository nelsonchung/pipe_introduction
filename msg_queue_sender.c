#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSG_SIZE 256

// 訊息結構
struct message {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    key_t key;
    int msqid;
    struct message msg;

    // 生成一個唯一的key
    key = ftok(".", 'M');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // 創建訊息佇列
    msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    // 設置訊息類型
    msg.mtype = 1;

    // 設置訊息內容
    strncpy(msg.mtext, "Hello, message queue!", MSG_SIZE);

    // 發送訊息
    if (msgsnd(msqid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    return 0;
}

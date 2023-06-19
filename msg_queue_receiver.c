#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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

    // 獲取訊息佇列
    msqid = msgget(key, 0666);
    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    // 接收訊息
    if (msgrcv(msqid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    // 顯示接收到的訊息
    printf("接收到的訊息：%s\n", msg.mtext);

    // 刪除訊息佇列
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return 1;
    }

    return 0;
}

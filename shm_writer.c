#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *shmaddr;
    char message[] = "Hello, shared memory!";

    // 生成一個唯一的key
    key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // 創建共享內存
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // 附加共享內存
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
        perror("shmat");
        return 1;
    }

    // 寫入數據到共享內存
    strncpy(shmaddr, message, SHM_SIZE);

    // 分離共享內存
    shmdt(shmaddr);

    return 0;
}

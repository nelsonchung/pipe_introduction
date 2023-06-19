#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *shmaddr;
    char buffer[SHM_SIZE];

    // 生成一個唯一的key
    key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // 獲取共享內存
    shmid = shmget(key, SHM_SIZE, 0666);
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

    // 從共享內存讀取數據
    strncpy(buffer, shmaddr, SHM_SIZE);
    printf("從共享內存讀取到的數據：%s\n", buffer);

    // 分離共享內存
    shmdt(shmaddr);

    return 0;
}

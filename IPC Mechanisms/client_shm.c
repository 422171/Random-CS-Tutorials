#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

#define MAX 100

void main() {
    key_t key = ftok("dataFile", 'B');
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *data = (char*)shmat(shmid, (void*)0, 0);
    printf("Enter data: ");
    fgets(data, 50, stdin);
    printf("Data written in memory: %s\n",data);
    shmdt(data);
}
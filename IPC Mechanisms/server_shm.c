#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

#define MAX 100

int main() {
    key_t key = ftok("dataFile", 'B');
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *data = (char*)shmat(shmid, (void*)0, 0);
    
    printf("Recieved data: %s", data);
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
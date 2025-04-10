#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>

#define MAX 100
typedef struct shared_data{
    int req_ready;
    int res_ready;
    char data[MAX];
} shared_data;

int main() {
    key_t key = ftok("dataFile", 'B');
    int shmid = shmget(key, sizeof(shared_data), 0666 | IPC_CREAT);
    shared_data *shm_data = (shared_data*)shmat(shmid, (void*)0, 0);
    while (shm_data->req_ready != 1)
    {
        sleep(1);
    }
    
    printf("Request received: %s", shm_data->data);
    printf("Enter response: ");
    fgets(shm_data->data, MAX, stdin);
    shm_data->res_ready = 1;
    shmdt(shm_data);
    // shmctl(shmid, IPC_RMID, NULL);
    printf("\n");
    return 0;
}

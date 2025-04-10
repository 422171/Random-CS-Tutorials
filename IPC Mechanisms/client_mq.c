#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#define MAX 100

struct msg_buffer{
    long msg_type;
    char msg_data[MAX];
}message;

int main() {
    key_t key;
    int msg_id;
    key = ftok("dataFile", 'A');
    msg_id = msgget(key, 0666 | IPC_CREAT);

    message.msg_type = 1;
    printf("Enter message: ");
    fgets(message.msg_data, MAX, stdin);
    message.msg_data[strcspn(message.msg_data, "\n")] = '\0';
    msgsnd(msg_id, &message, sizeof(message), 0); //flag=0 - default behavior - block if full - IPC_NOWAIT
    // printf("Message \"%s\" is sent \n", message.msg_data);

    msgrcv(msg_id, &message, sizeof(message), 2, 0); 
    printf("Data received: %s \n", message.msg_data);
    msgctl(msg_id, IPC_RMID, NULL);
    return 0;
}
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#define MAX 100

struct msg_buffer{
    long msg_type;
    char msg_data[MAX];
}message;

void getData(char* query);

int main() {
    key_t key;
    int msg_id;
    key = ftok("dataFile", 'A');
    msg_id = msgget(key, 0666 | IPC_CREAT);

    msgrcv(msg_id, &message, sizeof(message), 1, 0); //flag=0 - default behavior - block if full - IPC_NOWAIT
    // msgtyp = 1 - receive message of type 1 ; message.msg_type set to 1 in sender_mq.c
    // printf("Request received: %s \n", message.msg_data); //included in getData()
    //msgctl(msg_id, IPC_RMID, NULL); //if no response is to be sent and close the connection
    getData(message.msg_data);
    msgsnd(msg_id, &message, sizeof(message), 0);
    return 0;
}

void getData(char* query){
    printf("Request received: %s \n", query);
    message.msg_type = 2;
    printf("Enter response: ");
    fgets(message.msg_data, MAX, stdin);
    message.msg_data[strcspn(message.msg_data, "\n")] = '\0';
}
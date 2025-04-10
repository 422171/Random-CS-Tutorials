#include<stdio.h>
#include<string.h> //strlen
#include<unistd.h> //posix functions - read, write
#include<fcntl.h> //file control - open
#include<sys/types.h> //mkfifo
#include<sys/stat.h> //mkfifo
int main() {
    int res = mkfifo("/tmp/setsuko", 0777);
    char *fifo_file = "/tmp/setsuko";
    char receive[100], send[100];
    int fd;
    while(1){
        printf("You: ");
        fd = open(fifo_file, O_WRONLY);
        fgets(send, 100, stdin);
        write(fd, send, strlen(send)+1);
        close(fd);

        fd = open(fifo_file, O_RDONLY);
        read(fd, receive, sizeof(receive));
        receive[strcspn(receive,"\n")] = '\0';
        printf("user2: %s\n", receive);
        close(fd);
    }
    return 0;
}
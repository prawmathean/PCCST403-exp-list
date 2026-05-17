#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <ctype.h>
#include <sys/wait.h>

/* IPC Demos: Pipes, Message Queues, and Shared Memory */

// 1. Pipes Demo
void pipe_demo() {
    int fd[2];
    char msg[] = "Hello from Pipe!";
    char buffer[100];
    pipe(fd);
    if (fork() == 0) {
        close(fd[0]);
        write(fd[1], msg, strlen(msg) + 1);
        exit(0);
    } else {
        close(fd[1]);
        read(fd[0], buffer, 100);
        printf("Pipe Received: %s\n", buffer);
        wait(NULL);
    }
}

// 2. Message Queue (Palindrome)
struct msg_buf {
    long msg_type;
    char text[100];
};

void msg_queue_demo() {
    key_t key = ftok("prog", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg_buf message;

    if (fork() == 0) {
        msgrcv(msgid, &message, sizeof(message.text), 1, 0);
        int len = strlen(message.text), pal = 1;
        for (int i = 0; i < len/2; i++)
            if (message.text[i] != message.text[len-i-1]) pal = 0;
        printf("MQ Received: %s -> %s\n", message.text, pal ? "Palindrome" : "Not Palindrome");
        msgctl(msgid, IPC_RMID, NULL);
        exit(0);
    } else {
        message.msg_type = 1;
        strcpy(message.text, "madam");
        msgsnd(msgid, &message, sizeof(message.text), 0);
        wait(NULL);
    }
}

// 3. Shared Memory (Case Flip)
void shm_demo() {
    key_t key = ftok("shmfile", 66);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    if (fork() == 0) {
        sleep(1); // wait for parent to write
        for(int i=0; str[i]; i++) {
            if (isupper(str[i])) str[i] = tolower(str[i]);
            else if (islower(str[i])) str[i] = toupper(str[i]);
        }
        shmdt(str);
        exit(0);
    } else {
        strcpy(str, "Hello World");
        wait(NULL);
        printf("SHM Result: %s\n", str);
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    }
}

int main() {
    printf("--- IPC Mechanisms Lab ---\n\n");
    printf("1. Running Pipe Demo...\n"); pipe_demo();
    printf("\n2. Running Msg Queue (Palindrome) Demo...\n"); msg_queue_demo();
    printf("\n3. Running Shared Memory (Case Flip) Demo...\n"); shm_demo();
    return 0;
}

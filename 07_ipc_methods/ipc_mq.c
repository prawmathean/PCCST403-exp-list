#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (fork() == 0) {
        // Child Process (P2)
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("P2: Received string: %s. Reversing...\n", message.msg_text);
        
        int n = strlen(message.msg_text);
        for (int i = 0; i < n / 2; i++) {
            char temp = message.msg_text[i];
            message.msg_text[i] = message.msg_text[n - i - 1];
            message.msg_text[n - i - 1] = temp;
        }
        
        message.msg_type = 2; // Type 2 for response
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        exit(0);
    } else {
        // Parent Process (P1)
        printf("P1: Enter a string to check if it's a palindrome: ");
        scanf("%s", message.msg_text);
        
        char original[100];
        strcpy(original, message.msg_text);
        
        message.msg_type = 1;
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        
        // Wait for response from P2
        msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0);
        printf("P1: Received reversed string: %s\n", message.msg_text);
        
        if (strcmp(original, message.msg_text) == 0) {
            printf("Result: It is a Palindrome!\n");
        } else {
            printf("Result: It is NOT a Palindrome.\n");
        }
        
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL); // Destroy the queue
    }

    return 0;
}

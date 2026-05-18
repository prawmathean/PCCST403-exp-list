#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    if (fork() == 0) {
        // Child Process (P2)
        // Simple synchronization: wait for parent to write
        sleep(1); 
        
        // At this point, str contains "s1 s2 s3"
        printf("P2: Read from shared memory: %s\n", str);
        
        // Flip the case
        for (int i = 0; str[i] != '\0'; i++) {
            if (islower(str[i])) str[i] = toupper(str[i]);
            else if (isupper(str[i])) str[i] = tolower(str[i]);
        }
        
        shmdt(str);
        exit(0);
    } else {
        // Parent Process (P1)
        char s1[30], s2[30], s3[30];
        printf("P1: Enter three strings: ");
        scanf("%s %s %s", s1, s2, s3);
        
        sprintf(str, "%s %s %s", s1, s2, s3);
        printf("P1: Wrote to shared memory. Waiting for P2...\n");
        
        wait(NULL);
        
        printf("P1: Result after P2's processing: %s\n", str);
        
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
